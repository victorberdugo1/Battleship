#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void Leer_Estadisticas();
void Edicion_Mar(int Mar[8][8], int coord[2], char orienta[2], int tam);
int Validad_Coordenada(int Mar[8][8], int coord[2], char orienta[2], int tam);
void Guardar_Resultados(int cant_dis1, int cant_dis2, int aciertos, int ganador);
void Modificar_Barcos();
void Iniciar_Juego();
void Ver_Flota(int Mar[8][8]);
void Mostrar_Mapa_Disparos(int Mar_Disparos[8][8]);
int Quedan_Barcos(int Mar[8][8]);

/*********************
  Funcion principal
 *********************/
int main()
{
	int elec = -1;  

	while (elec != 0)
	{
		printf("\n*** BIENVENIDO A HUNDIR LA FLOTA ***\
				\n====================================\
				\n******* MENU PRINCIPAL *******\
				\n==============================\
				\n[1] - Iniciar nueva partida\
				\n[2] - Modificar flota\
				\n[3] - Consultar estadisticas\
				\n[0] - Salir\n");
		printf("Elige opcion: ");
		if (scanf("%d", &elec) != 1)
		{
			printf("Entrada no válida. Por favor, introduce un número: ");
			while (getchar() != '\n'); 
		}
		else
		{

			switch (elec)
			{
				case 1:
					Iniciar_Juego();
					break;
				case 2:
					Modificar_Barcos();
					break;
				case 3:
					Leer_Estadisticas();
					break;
				case 0:
					printf("\nGracias por jugar!!\n");
					break;
				default:
					printf("Opcion incorrecta\n");
					break;
			}
		}
		if (elec != 0)
		{
			printf("\nPresiona una tecla para regresar al menu...\n");
			getchar(); 
			system("cls || clear"); 
		}
	}
	return (0);
}

int Barco_Destruido(int Mar[8][8], int coord[2], char orientacion, int tam)
{
    if (orientacion == 'H' || orientacion == 'h')
	{
        for (int i = 0; i < tam; i++)
		{
            if (Mar[coord[0]][coord[1] + i] != 0)
			{
                return 0;

			}
        }
    }
	else if (orientacion == 'V' || orientacion == 'v')
	{
        for (int i = 0; i < tam; i++)
		{
            if (Mar[coord[0] + i][coord[1]] != 0)
			{
                return 0;
            }
        }
    }
    return 1;
}

void Leer_Estadisticas()
{
	FILE *fp;
	int i = 0;
	char frase[40];
	int puntos[7] = {0}; 

	fp = fopen("estadisticas.txt", "r");
	if (fp == NULL)
	{
		printf("Error abriendo estadisticas.txt\n");
		exit(0);
	}
	printf("\nConsulta de estadisticas:\n");
	while (!feof(fp) && i < 7)
	{
		fscanf(fp, "%[A-Z: ] %d\n", frase, &puntos[i]);
		i++;
	}
	printf("\n\tEl record esta establecido en %d disparos.", puntos[0]);
	printf("\n\tEl jugador 1 ha ganado un total de %d partidas.", puntos[2]);
	printf("\n\tEl jugador 2 ha ganado un total de %d partidas.", puntos[4]);
	printf("\n\tHa habido un total de %d empates.", puntos[5]);
	printf("\n\tLa partida mas larga a constado de %d disparos.\n", puntos[6]);
	fclose(fp);
	getchar();
}

void Modificar_Barcos()
{
	struct flota {
		char nombre[40];
		int tam; 
	};

	FILE *fp;
	struct flota barco[5]; 
	char frase[40];
	char nombtemp[40];
	char pass[6];
	char resp[2];
	int sum, c = 0;

	fp = fopen("barq.txt", "r+");
	if (fp == NULL)
	{
		printf("Error abriendo barq.txt\n");
		exit(0);
	}
	printf("+++ Modificar flota +++\nPara acceder introduce la contraseña\n\t");
	scanf("%s", pass);
	if (strcmp(pass, "12345") == 0)
	{ 
		printf("\n\tCorrecto\n\t");
		while (fscanf(fp, "%[^,], %d\n", barco[c].nombre, &barco[c].tam) == 2 && c < 5)
			c++;
		for (int i = 0; i < c; i++)
		{
			printf("\n\nDatos del barco %d:\n\tNombre: %s\n\tTamaño: %d",
					i + 1, barco[i].nombre, barco[i].tam);
			printf("\n\nModificar datos? [S/N]: ");
			scanf("%s", resp);
			if (strcmp(resp, "SI") == 0 || strcmp(resp, "S") == 0 || 
					strcmp(resp, "si") == 0 || strcmp(resp, "s") == 0)
			{
				printf("\n\nIntroduce el nuevo nombre: ");
				do {
					scanf("%s", nombtemp);
					if (strlen(nombtemp) > 28)
						printf("\nEl nombre tiene demasiadas letras. Elige otro nombre:\n");
				}
				while (strlen(nombtemp) > 28);
				strcpy(barco[i].nombre, nombtemp); 
				printf("\n\nIntroduce el tamaño: ");
				sum = 9; 
				while (sum > 8 || sum < 1)
				{ 
					scanf("%s", nombtemp);
					sum = atoi(nombtemp);
					if (sum > 8 || sum < 1)
						printf("\nEl tamaño es superior a 8 o menor a 1. Elige otro tamaño:\n");
				}
				barco[i].tam = sum; 
			}
		}
		fseek(fp, 0, SEEK_SET); 
		for (int i = 0; i < c; i++)
			fprintf(fp, "%s, %d\n", barco[i].nombre, barco[i].tam); 
		printf("\n\tGrabado\n");
	}
	else
		printf("\n\tIncorrecto\n");
	getchar();
	fclose(fp); 
}

void Iniciar_Juego()
{
	int Mar1[8][8] = {0}; 
	int Mar2[8][8] = {0}; 
	int MarIn[8][8] = {0}; 
    int Mar_Disparos1[8][8] = {0};
	int Mar_Disparos2[8][8] = {0};

	struct flota {
		char nombre[40];
		int tam;
	} barco[9]; 

	FILE *fp = fopen("barq.txt", "r"); 
	char frase[40];
	char orientacion[2];
	char resp[2];
	int c = 0, totdisp = 0, aciertos = 0, cant_dis1 = 0, cant_dis2 = 0, resultado = 0;

	if (fp == NULL)
	{
		printf("Error abriendo barq.txt\n");
		exit(0); 
	}
	while (fscanf(fp, "%[^,], %d\n", frase, &barco[c].tam) == 2)
	{
		strcpy(barco[c].nombre, frase);
		c++;
	}
	printf("\nJUGADOR 1\n");
	for (int i = 0; i < 5; i++)
	{
		printf("\nIntroduce coordenadas del barco %s (tamaño %d):\
				\nfila(-Y) primero y luego columna(+X): ", barco[i].nombre, barco[i].tam);

		int coo[2];
		scanf("%d %d", &coo[0], &coo[1]);
		printf("Introduce orientacion [H - V]: ");
		scanf(" %c", &orientacion[0]);
		while (Validad_Coordenada(Mar1, coo, orientacion, barco[i].tam)) {
			printf("Coordenadas incorrectas. Intente de nuevo.\n");
			Ver_Flota(Mar1); 
			printf("\nIntroduce coordenadas del barco %s (tamaño %d): ", barco[i].nombre, barco[i].tam);
			scanf("%d %d", &coo[0], &coo[1]);
			printf("Introduce orientacion [H - V]: ");
			scanf(" %c", &orientacion[0]);
		}
		Edicion_Mar(Mar1, coo, orientacion, barco[i].tam);
		totdisp += barco[i].tam;
		Ver_Flota(Mar1); 
	}
	system("cls || clear"); 
	printf("\nJUGADOR 2\n");
	for (int i = 0; i < 5; i++) {
		printf("\nIntroduce coordenadas del barco %s (tamaño %d):\
				\nfila(-Y) primero y luego columna(+X): ", barco[i].nombre, barco[i].tam);
		int coo[2];
		scanf("%d %d", &coo[0], &coo[1]);
		printf("Introduce orientacion [H - V]: ");
		scanf(" %c", &orientacion[0]);


		while (Validad_Coordenada(Mar2, coo, orientacion, barco[i].tam)) {
			printf("Coordenadas incorrectas. Intente de nuevo.\n");
			Ver_Flota(Mar2); 
			printf("\nIntroduce coordenadas del barco %s (tamaño %d): ", barco[i].nombre, barco[i].tam);
			scanf("%d %d", &coo[0], &coo[1]);
			printf("Introduce orientacion [H - V]: ");
			scanf(" %c", &orientacion[0]);
		}
		Edicion_Mar(Mar2, coo, orientacion, barco[i].tam);
		totdisp += barco[i].tam;
		Ver_Flota(Mar2); 
	}
	fclose(fp); 
	system("cls || clear"); 

	while (totdisp > 0)
	{
		int coord[2];
		int valid_input = 0;

		printf("\n\nTurno del Jugador 1\n");

		while (!valid_input)
		{
			printf("Introduce coordenadas para atacar (fila columna): ");
			if (scanf("%d %d", &coord[0], &coord[1]) == 2 && coord[0] >= 0 
					&& coord[0] < 8 && coord[1] >= 0 && coord[1] < 8)
				valid_input = 1;
			else
			{
				printf("Entrada inválida. Por favor, introduce coordenadas numéricas entre 0 y 7.\n");
				while (getchar() != '\n');
			}
		}

		cant_dis1++;

		if (Mar2[coord[0]][coord[1]] == 1) {
			printf("¡Acierto!\n");
			Mar2[coord[0]][coord[1]] = 0;
			Mar_Disparos1[coord[0]][coord[1]] = 2;
			aciertos++;
			totdisp--;
			if (Barco_Destruido(Mar2, coord, orientacion[0], barco[cant_dis1 % 5].tam)) {
				printf("¡Has destruido completamente el barco %s!\n", barco[cant_dis1 % 5].nombre);
			}
		} else if (Mar_Disparos1[coord[0]][coord[1]] == 0) {
			printf("¡Fallaste!\n");
			Mar_Disparos1[coord[0]][coord[1]] = 1;
		} else {
			printf("Ya has disparado en esta posición. Intenta en otra la proxima vez.\n");
		}

		Mostrar_Mapa_Disparos(Mar_Disparos1);

		if (!Quedan_Barcos(Mar2))
		{
			printf("¡El Jugador 1 ha ganado!\n");
			resultado = 1;
			getchar();
			break;
		}

		printf("\nTurno del Jugador 2\n");

		valid_input = 0;

		while (!valid_input)
		{
			printf("Introduce coordenadas para atacar (fila columna): ");
			if (scanf("%d %d", &coord[0], &coord[1]) == 2 && coord[0] >= 0 
					&& coord[0] < 8 && coord[1] >= 0 && coord[1] < 8) 
				valid_input = 1;
			else
			{
				printf("Entrada inválida. Por favor, introduce coordenadas numéricas entre 0 y 7.\n");
				while (getchar() != '\n');
			}
		}

		cant_dis2++;

		if (Mar1[coord[0]][coord[1]] == 1) {
			printf("¡Acierto!\n");
			Mar1[coord[0]][coord[1]] = 0;
			Mar_Disparos2[coord[0]][coord[1]] = 2;
			aciertos++;
			totdisp--;
			if (Barco_Destruido(Mar1, coord, orientacion[0], barco[cant_dis2 % 5].tam)) {
				printf("¡Has destruido completamente el barco %s!\n", barco[cant_dis2 % 5].nombre);
			}
		} else if (Mar_Disparos2[coord[0]][coord[1]] == 0) {
			printf("¡Fallaste!\n");
			Mar_Disparos2[coord[0]][coord[1]] = 1;
		} else {
			printf("Ya has disparado en esta posición. Intenta en otra la proxima vez.\n");
		}

		Mostrar_Mapa_Disparos(Mar_Disparos2);

		if (!Quedan_Barcos(Mar1))
		{
			printf("¡El Jugador 2 ha ganado!\n");
			resultado = 2;
			getchar();
			break;
		}
	}

	Guardar_Resultados(cant_dis1, cant_dis2, aciertos, resultado);
}

int Quedan_Barcos(int Mar[8][8])
{
    for (int i = 0; i < 8; i++) 
	{
        for (int j = 0; j < 8; j++) 
		{
            if (Mar[i][j] == 1) 
			{
				return 1;
            }
        }
    }
    return 0;
}

void Edicion_Mar(int Mar[8][8], int coord[2], char orienta[2], int tam)
{
    char orientacion = orienta[0];
    for (int i = 0; i < tam; i++)
    {
        if (orientacion == 'H' || orientacion == 'h') 
            Mar[coord[0]][coord[1] + i] = 1; 
        else if (orientacion == 'V' || orientacion == 'v') 
            Mar[coord[0] + i][coord[1]] = 1; 
    }
}


int Validad_Coordenada(int Mar[8][8], int coord[2], char orienta[2], int tam)
{
	if (orienta[0] != 'H' && orienta[0] != 'h' && orienta[0] != 'V' && orienta[0] != 'v')
		return 1;
	if (orienta[0] == 'H' || orienta[0] == 'h')
	{
		if (coord[1] + tam > 8) return 1; 
		for (int i = 0; i < tam; i++)
			if (Mar[coord[0]][coord[1] + i] != 0) return 1; 
	}
	else if(orienta[0] == 'V' || orienta[0] == 'v')
	{
		if (coord[0] + tam > 8) return 1; 
		for (int i = 0; i < tam; i++)
			if (Mar[coord[0] + i][coord[1]] != 0) return 1; 
	}
	return 0; 
}

void Guardar_Resultados(int cant_dis1, int cant_dis2, int aciertos, int ganador)
{
   FILE *fp;
    int puntos[7] = {0};
    char frase[40];
    fp = fopen("estadisticas.txt", "r+");
    if (fp == NULL)
    {
        printf("Error abriendo estadisticas.txt\n");
        exit(0);
    }

    int i = 0;
    while (fscanf(fp, "%[A-Z: ] %d\n", frase, &puntos[i]) == 2)
    {
        i++;
    }

    if (aciertos < puntos[0] || puntos[0] == 0)
        puntos[0] = aciertos;
    
    // Guardar el ganador en el archivo de estadísticas
    if (ganador == 1) {
        puntos[2]++; // Incrementar contador de victorias del Jugador 1
    } else if (ganador == 2) {
        puntos[4]++; // Incrementar contador de victorias del Jugador 2
    }

    if (cant_dis1 + cant_dis2 > puntos[6])
        puntos[6] = cant_dis1 + cant_dis2;

    fseek(fp, 0, SEEK_SET);
    fprintf(fp, "RECORD: %d\nJUGADOR 1: %d\nJUGADOR 2: %d\nEMPATES: 0\nPARTIDA MAS LARGA: %d\n",
            puntos[0], puntos[2], puntos[4], puntos[6]);

    fclose(fp);
    printf("\n\tGrabado\n");
    //getchar();
}

void Ver_Flota(int Mar[8][8])
{
	printf("\n\t\t  [0|1|2|3|4|5|6|7|\n");
	for (int i = 0; i < 8; i++)
	{
		printf("\t\t[%d|", i); 
		for (int j = 0; j < 8; j++)
			printf("%d|", Mar[i][j]); 
		printf("\n");
	}
}

void Mostrar_Mapa_Disparos(int Mar_Disparos[8][8])
{
	printf("\n\t\t  [0|1|2|3|4|5|6|7|\n");
	for (int i = 0; i < 8; i++)
	{
		printf("\t\t[%d|", i); 
		for (int j = 0; j < 8; j++)
		{
            if (Mar_Disparos[i][j] == 0)
			{
                printf(" |");
            }
			else if (Mar_Disparos[i][j] == 1)
			{
                printf("X|");
            }
			else if (Mar_Disparos[i][j] == 2)
			{
                printf("O|");
            }
        }
        printf("\n");
    }
}

