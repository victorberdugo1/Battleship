#include<stdio.h>

#include<stdlib.h>

#include<time.h>


void Leer_Estadisticas();

int Edicion_Mar(int Mar[8][8],int coord[2],char orienta[2],int tam);

int Validad_Coordenada(int Mar[8][8],int coord[2],char orienta[2],int tam);

void Modificar_Barcos();

void Iniciar_Juego();

void Ver_Flota(int Mar[8][8]);

/*********************
  Funcion principal
 *********************/
void main()
{
    int elec;
    printf("*** BIENVENIDO A HUNDIR LA FLOTA ***\n====================================\n******* MENU PRINCIPAL *******\n==============================\n[1] - Iniciar nueva partida\n[2] - Modificar flota\n[3] - Consultar estadisticas\n[0] - Salir\n");
    //printf Menu Principal
    do
    {
        printf("Elige opcion: ");
        scanf("%d",&elec);//Puntero %d para opcion del usuario
        fflush(stdin);//limpia buffer
        if(elec==1)
        {
            Iniciar_Juego();
            system("cls");//Limpiamos pantalla;
            printf("*** BIENVENIDO A HUNDIR LA FLOTA ***\n====================================\n******* MENU PRINCIPAL *******\n==============================\n[1] - Iniciar nueva partida\n[2] - Modificar flota\n[3] - Consultar estadisticas\n[0] - Salir\n");
            elec=666;// repitamos Menu Principal;evitamos que se repita si elec es alpha
        }
        if(elec==2)
        {
            Modificar_Barcos();
            system("cls");//Limpiamos pantalla;
            printf("*** BIENVENIDO A HUNDIR LA FLOTA ***\n====================================\n******* MENU PRINCIPAL *******\n==============================\n[1] - Iniciar nueva partida\n[2] - Modificar flota\n[3] - Consultar estadisticas\n[0] - Salir\n");
            elec=666;// repitamos Menu Principal;evitamos que se repita si elec es alpha
        }
        if(elec==3)
        {
            Leer_Estadisticas();
            system("cls");//Limpiamos pantalla;
            printf("*** BIENVENIDO A HUNDIR LA FLOTA ***\n====================================\n******* MENU PRINCIPAL *******\n==============================\n[1] - Iniciar nueva partida\n[2] - Modificar flota\n[3] - Consultar estadisticas\n[0] - Salir\n");
            elec=666;//repitamos Menu Principal;evitamos que se repita si elec es alpha
        }

        if(elec<0 || elec>3 && elec!=666)
        {
        //si elec 666 no se pinta opcion incorrecta
        printf("Opcion incorrecta\n");
        }
        //si no es opcion del menu

        }
        while(elec!=0);

    if(elec==0)

    printf("\nGracias por jugar!!");

    getch();

}

void Leer_Estadisticas()
{
FILE *fp;
int i = 0;
fp = fopen("estadisticas.txt", "r");
char frase[40];
int puntos[6];
//vector para puntuaciones numericas
if(fp == NULL){
printf("Error abriendo estadisticas.txt\n");
exit(0);
}
printf("\nConsulta de estadisticas : ");
while(!feof(fp)){
fscanf(fp, "%[A-Z: ] %d \n", frase,&puntos[i]);
i++;
}
//de se guarda en vector puntos[6] los datos numericos diferentes de [A-Z: ]
printf("\n\tEl record esta establecido en %d ",  puntos[0]);
printf("disparos.\n\tEl jugador %d ",puntos[1]);
printf("ha ganado un total de %d ",puntos[2]);
printf("partidas.\n\tEl jugador %d ",puntos[3]);
printf("ha ganado un total de %d ",puntos[4]);
printf("partidas.\n\tHa habido un total de %d ",puntos[5]);
printf("empates.\n\tLa partida mas larga a constado de %d ",puntos[6]);
printf("disparos.\n\n\n\n\nPresiona una tecla para regresar el menu");
//se pinta texto de puntaciones
fclose(fp);
//cerramos archivo txt
getch();
}

void Modificar_Barcos()
{
struct flota
    {
    char nombre[40];
    int tam[6];
    } flota_de;
//estructura para la flota
FILE *fp;
//archivo para txt
struct flota barco[9];
//declaracion de estructura para 5 barcos con 1 nombre temporal para cada uno
char frase[40];
char nombtemp[40];
char pass[6];
char resp[2];
int sum;
int i,c=0;

fp = fopen("barq.txt", "r+");
//se carga .txt para lecutra y escritura
if(fp == NULL)
{
printf("Error abriendo barq.txt\n");
exit(0);
//si no pudo abrir el archivo error
}

printf("+++ Modificar flota +++\nPara acceder introduce la contrasenya\n\t");
scanf("%s", pass);
if(strcmp(pass, "12345") == 0)//verificamos contraseña
{
    printf("\n\tCorrecto\n\t");

    while(!feof(fp))
    {
        fscanf(fp,"%s ", &frase);
        strcpy(barco[c].nombre,frase);
        if(c%2!=0)
            strcpy(barco[c].tam,frase);
        c++;
    }//llenamos estruc con los datos del archivo
    printf("\n\nPresiona una tecla continuar");
    getch();
    system("cls");
    //limpiamos pantalla
    printf("+++ Modificar flota +++\n\n\n\n\nDatos del primer barco:\n\tNombre: %s\n\tTamanyo: ",barco[0].nombre);
    printf(barco[1].tam);
    printf("\n\nModifiar datos? [S/N]: ");
    scanf("%s", resp);
    //verificamos respuesta
    if(strcmp(resp, "SI") == 0 || strcmp(resp, "S") == 0 || strcmp(resp, "si") == 0 || strcmp(resp, "s") == 0 )
    {
        printf("\n\nIntroduce el nuevo nombre: ");
        strcpy(nombtemp,"123456789012345678901234567890");
        //inicializamos cadena nombretemporal para que entre en while
        while(strlen(nombtemp)>28)
        {
            scanf("%s", nombtemp);
            if(strlen(nombtemp)>=28)//texto si el nombre supera los 28 caracteres
                printf("\n\nEl nombre tiene demaciadas letras\n Elige otro nombre\n\nIntroduce el nuevo nombre: ");
        }
        strcpy(barco[1].nombre,nombtemp);//grabamos el nombre temporal en el struct[0]+1
        printf("\n\nIntroduce el tamanyo: ");
        sum = 9;//inicializamos sum mayor de 8 para que entre en el loop while
        while(sum>8 || sum<1)//loop de verificacion del valor introducido
        {
            scanf("%s", nombtemp);
            sum = atoi(nombtemp);
            if(sum>8|| sum<1)
                printf("\n\nEl tamanyo es superior a 8 o menor a 1\n Elige otro tamanyo que pueda colocarse dentro de mar \n\nIntroduce el tamanyo: ");
        }
        strcpy(barco[0].tam,nombtemp);//grabamos el tamaño en tipo caracter en struct[0]-1
    }
    else//si se pone un caracter diferente de "si" o "s" o "SI" o "S"
    {
        barco[0].nombre[strlen(barco[0].nombre)-1]='\0';//quitamos la coma para evitar que se repita al grabar
        strcpy(barco[1].nombre,barco[0].nombre);
        strcpy(barco[0].tam,barco[1].tam);
    }

    printf("\n\n\n\n\nDatos del segundo barco:\n\tNombre: %s\n\tTamanyo: ",barco[2].nombre);
    printf(barco[3].tam);
    printf("\n\nModifiar datos? [S/N]: ");
    scanf("%s", resp);
    if(strcmp(resp, "SI") == 0 || strcmp(resp, "S") == 0 || strcmp(resp, "si") == 0 || strcmp(resp, "s") == 0 )
    {
    printf("\n\nIntroduce el nuevo nombre: ");
    strcpy(nombtemp,"123456789012345678901234567890");
    //inicializamos cadena nombretemporal para que entre en while
    while(strlen(nombtemp)>28)
    {
        scanf("%s", nombtemp);
        if(strlen(nombtemp)>=28)//texto si el nombre supera los 28 caracteres
            printf("\n\nEl nombre tiene demaciadas letras\n Elige otro nombre\n\nIntroduce el nuevo nombre: ");
    }
    strcpy(barco[3].nombre,nombtemp);

    printf("\n\nIntroduce el tamanyo: ");
    sum = 9;//inicializamos sum mayor de 8 para que entre en el loop while
    while(sum>8 || sum<1)//loop de verificacion del valor introducido
    {
        scanf("%s", nombtemp);
        sum = atoi(nombtemp);
        if(sum>8|| sum<1)
            printf("\n\nEl tamanyo es superior a 8 o menor a 1\n Elige otro tamanyo que pueda colocarse dentro de mar \n\nIntroduce el tamanyo: ");
    }
    strcpy(barco[2].tam,nombtemp);
    }
    else
    {
        barco[2].nombre[strlen(barco[2].nombre)-1]='\0';//quitamos la coma para evitar que se repita al grabar
        strcpy(barco[3].nombre,barco[2].nombre);
        strcpy(barco[2].tam,barco[3].tam);
    }

    printf("\n\n\n\n\nDatos del tercer barco:\n\tNombre: %s\n\tTamanyo: ",barco[4].nombre);
    printf(barco[5].tam);
    printf("\n\nModifiar datos? [S/N]: ");
    scanf("%s", resp);
    if(strcmp(resp, "SI") == 0 || strcmp(resp, "S") == 0 || strcmp(resp, "si") == 0 || strcmp(resp, "s") == 0 )
    {
    printf("\n\nIntroduce el nuevo nombre: ");
    strcpy(nombtemp,"123456789012345678901234567890");
        //inicializamos cadena nombretemporal para que entre en while
        while(strlen(nombtemp)>28)
        {
            scanf("%s", nombtemp);
            if(strlen(nombtemp)>=28)//texto si el nombre supera los 28 caracteres
                printf("\n\nEl nombre tiene demaciadas letras\n Elige otro nombre\n\nIntroduce el nuevo nombre: ");
        }
    strcpy(barco[5].nombre,nombtemp);

    printf("\n\nIntroduce el tamanyo: ");

    sum = 9;//inicializamos sum mayor de 8 para que entre en el loop while
    while(sum>8 || sum<1)//loop de verificacion del valor introducido
    {
        scanf("%s", nombtemp);
        sum = atoi(nombtemp);
        if(sum>8|| sum<1)
            printf("\n\nEl tamanyo es superior a 8 o menor a 1\n Elige otro tamanyo que pueda colocarse dentro de mar \n\nIntroduce el tamanyo: ");
    }
    strcpy(barco[4].tam,nombtemp);
    }
    else
    {
        barco[4].nombre[strlen(barco[4].nombre)-1]='\0';//quitamos la coma para evitar que se repita al grabar
        strcpy(barco[5].nombre,barco[4].nombre);
        strcpy(barco[4].tam,barco[5].tam);
    }
    printf("\n\n\n\n\nDatos del cuarto barco:\n\tNombre: %s\n\tTamanyo: ",barco[6].nombre);
    printf(barco[7].tam);
    printf("\n\nModifiar datos? [S/N]: ");
    scanf("%s", resp);
    if(strcmp(resp, "SI") == 0 || strcmp(resp, "S") == 0 || strcmp(resp, "si") == 0 || strcmp(resp, "s") == 0 )
    {
    printf("\n\nIntroduce el nuevo nombre: ");
    strcpy(nombtemp,"123456789012345678901234567890");
        //inicializamos cadena nombretemporal para que entre en while
    while(strlen(nombtemp)>28)
    {
        scanf("%s", nombtemp);
        if(strlen(nombtemp)>=28)//texto si el nombre supera los 28 caracteres
        printf("\n\nEl nombre tiene demaciadas letras\n Elige otro nombre\n\nIntroduce el nuevo nombre: ");
    }

    strcpy(barco[7].nombre,nombtemp);

    printf("\n\nIntroduce el tamanyo: ");

    sum = 9;//inicializamos sum mayor de 8 para que entre en el loop while
    while(sum>8 || sum<1)//loop de verificacion del valor introducido
    {
        scanf("%s", nombtemp);
        sum = atoi(nombtemp);
        if(sum>8|| sum<1)
            printf("\n\nEl tamanyo es superior a 8 o menor a 1\n Elige otro tamanyo que pueda colocarse dentro de mar \n\nIntroduce el tamanyo: ");
    }
    strcpy(barco[6].tam,nombtemp);
    }
    else
    {
        barco[6].nombre[strlen(barco[6].nombre)-1]='\0';//quitamos la coma para evitar que se repita al grabar
        strcpy(barco[7].nombre,barco[6].nombre);
        strcpy(barco[6].tam,barco[7].tam);
    }
    printf("\n\n\n\n\nDatos del quinto barco:\n\tNombre: %s\n\tTamanyo: ",barco[8].nombre);
    printf(barco[9].tam);
    printf("\n\nModifiar datos? [S/N]: ");
    scanf("%s", resp);
    if(strcmp(resp, "SI") == 0 || strcmp(resp, "S") == 0 || strcmp(resp, "si") == 0 || strcmp(resp, "s") == 0 )
    {
    printf("\n\nIntroduce el nuevo nombre: ");
    strcpy(nombtemp,"123456789012345678901234567890");
        //inicializamos cadena nombretemporal para que entre en while
        while(strlen(nombtemp)>28)
        {
            scanf("%s", nombtemp);
            if(strlen(nombtemp)>=28)//texto si el nombre supera los 28 caracteres
                printf("\n\nEl nombre tiene demaciadas letras\n Elige otro nombre\n\nIntroduce el nuevo nombre: ");
        }

    strcpy(barco[9].nombre,nombtemp);

    printf("\n\nIntroduce el tamanyo: ");
    nombtemp[strlen(nombtemp)-strlen(nombtemp)]='\0';
    sum = 9;//inicializamos sum mayor de 8 para que entre en el loop while
    while(sum>8 || sum<1)//loop de verificacion del valor introducido
    {
        scanf("%s", nombtemp);
        sum = atoi(nombtemp);
        if(sum>8|| sum<1)
            printf("\n\nEl tamanyo es superior a 8 o menor a 1\n Elige otro tamanyo que pueda colocarse dentro de mar \n\nIntroduce el tamanyo: ");
    }
    strcpy(barco[8].tam,nombtemp);

    }
    else
    {
    barco[8].nombre[strlen(barco[8].nombre)-1]='\0';//quitamos la coma para evitar que se repita al grabar
    strcpy(barco[9].nombre,barco[8].nombre);
    strcpy(barco[8].tam,barco[9].tam);
    }
    fseek(fp,0,0);//moverse al inicio del archivo
    fflush(fp);
    fprintf(fp, "%s, %s\n%s, %s\n%s, %s\n%s, %s\n%s, %s\n"+'\0', barco[1].nombre,barco[0].tam,barco[3].nombre,barco[2].tam,barco[5].nombre,barco[4].tam,barco[7].nombre,barco[6].tam,barco[9].nombre,barco[8].tam);
    //grabamos archivo
    printf("\n\tGrabado");
    //getch();
}
else
    printf("\n\tIncorrecto");

fclose(fp);//cerramos archivo
}

void Iniciar_Juego()
{
int Mar1[8][8] = //matriz mar Jugador1
{
    { 0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0 }
};
//inicilizar matriz
int Mar2[8][8] = //matriz mar Jugador2
{
    { 0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0 }
};
//inicilizar matriz 2
int MarIn[8][8] = //matriz mar juego
{
    { 0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0 }
};
struct flota
    {
    char nombre[40];
    int tam[6];
    } flota_de;
//estructura para la flota
FILE *fp;
//archivo para txt
struct flota barco[9];
//declaracion de estructura para 5 barcos
fp = fopen("barq.txt", "r");
//se carga .txt para lectura
char frase[40];
char orientacion[2];
char resp[2];
int c=0;
int i;
int coo[2];
int totdisp=0,aciertos=0,cant_dis1=0,cant_dis2=0;
int puntos[6];
int empate=0;
//vector para puntuaciones numericas
if(fp == NULL)
{
printf("Error abriendo barq.txt\n");
exit(0);
//si no pudo abrir el archivo error
}
printf("+++ Iniciar nueva partida +++\n\n\t");

while(!feof(fp))
{
fscanf(fp,"%s ", &frase);
strcpy(barco[c].nombre,frase);
if(c%2!=0)
strcpy(barco[c].tam,frase);
c++;
}//llenamos estruc
//flota jugador 1
for(i=0;i<5;i++)
{
    if(barco[0+i+i].nombre[strlen(barco[0+i+i].nombre)-1]==',')
        barco[0+i+i].nombre[strlen(barco[0+i+i].nombre)-1]='\0';//se quita la coma
    printf("\nJUGADOR 1\n\nIntroduce coordenadas %s: ",barco[0+i+i].nombre);
    scanf("%i %i", &coo[0], &coo[1]);//se introducen las coordenadas
    printf("Intro orientacion [H - V]: ");
    scanf("%s",&orientacion);
    if(Validad_Coordenada(Mar1,coo,orientacion,barco[1+i+i].tam)!=0)
    {
        printf("\nCoordenadas incorrectas. Tenga en cuenta los siguientes requisitos:\n- Las coordenadas tienes que estar comprendidas entre 0 y 7.\n- La orientacion puede ser horizontal (H) o vertical (V).\n- El barco no se sale del campo de btalla.\n- No hay otro barco en las coordenadas.\nDesea ver la disposicion de su flota [S/N] ");
        scanf("%s", resp);
        if(strcmp(resp, "SI") == 0 || strcmp(resp, "S") == 0 || strcmp(resp, "si") == 0 || strcmp(resp, "s") == 0 )
            Ver_Flota(Mar1);
        i--;
    }
    else
    {
        totdisp=totdisp+atoi(barco[1+i+i].tam);//guardamos variable de cantidad barcos
        Edicion_Mar(Mar1,coo,orientacion,barco[1+i+i].tam);
        Ver_Flota(Mar1);
    }
}
//flota jugador 2
for(i=0;i<5;i++)
{
    if(barco[0+i+i].nombre[strlen(barco[0+i+i].nombre)-1]==',')
        barco[0+i+i].nombre[strlen(barco[0+i+i].nombre)-1]='\0';//se quita la coma
    printf("\nJUGADOR 2\n\nIntroduce coordenadas %s: ",barco[0+i+i].nombre);
    scanf("%i %i", &coo[0], &coo[1]);//se introducen las coordenadas
    printf("Intro orientacion [H - V]: ");
    scanf("%s",&orientacion);
    if(Validad_Coordenada(Mar2,coo,orientacion,barco[1+i+i].tam)!=0)
    {
        printf("\nCoordenadas incorrectas. Tenga en cuenta los siguientes requisitos:\n- Las coordenadas tienes que estar comprendidas entre 0 y 7.\n- La orientacion puede ser horizontal (H) o vertical (V).\n- El barco no se sale del campo de btalla.\n- No hay otro barco en las coordenadas.\nDesea ver la disposicion de su flota [S/N] ");
        scanf("%s", resp);
        if(strcmp(resp, "SI") == 0 || strcmp(resp, "S") == 0 || strcmp(resp, "si") == 0 || strcmp(resp, "s") == 0 )
            Ver_Flota(Mar2);
        i--;
    }
    else
    {
        Edicion_Mar(Mar2,coo,orientacion,barco[1+i+i].tam);
        Ver_Flota(Mar2);
    }
}
fclose(fp);
printf("\nListos jugadores \n\tTurno del Jugador 1");
getch();
system("cls");
coo[0]=-1;
coo[1]=-1;
while(aciertos<totdisp)
{
    printf("\n\t\t  JUGADOR 1\n\n");
    Ver_Flota(MarIn);
    printf("Introducir coordenadas del disparo: ");
    scanf("%i %i", &coo[0], &coo[1]);//se introducen las coordenadas
        if(coo[0]>7 || coo[0]<0 || coo[1]>8 || coo[1]<0)
        {//verificacion del valor introducido
            system("cls");
            printf("\n\t\t  JUGADOR 1\n\n");
            Ver_Flota(MarIn);
            printf("Error en las coordenadas no pueden ser ni superior a 7 tampoco menor a 0\n Elige otra coordenada: ");
        }
    if(Mar2[coo[0]][coo[1]]==1)
    {
        MarIn[coo[0]][coo[1]]=1;
        aciertos++;
        cant_dis1++;
    }
    if(Mar2[coo[0]][coo[1]]==0)
    {
        MarIn[coo[0]][coo[1]]=2;
        cant_dis1++;
    }

    coo[0]=-1;
    coo[1]=-1;
    system("cls");
}//bucle para juego jugador 1

    printf("\n\n\n\n\n\n\n\n\n\n\t\tHa destruido la flota del contrincante con %i disparos",cant_dis1);
    getch();
    system("cls");
    aciertos=0;
    for(i=0;i<=7;i++)
        for(c=0;c<=7;c++)
            MarIn[i][c] = 0;

    printf("\n\n\n\n\n\n\n\n\n\n\t\tListos jugadores \n\n\n\n\n\n\n\n\n\n\t\t\tTurno del Jugador 2");
    getch();
    system("cls");
    coo[0]=-1;
    coo[1]=-1;
while(aciertos<totdisp)
{
    printf("\n\t\t  JUGADOR 2\n\n");
    Ver_Flota(MarIn);
    printf("Introducir coordenadas del disparo: ");
    scanf("%i %i", &coo[0], &coo[1]);//se introducen las coordenadas
        if(coo[0]>7 || coo[0]<0 || coo[1]>8 || coo[1]<0)
        {//verificacion del valor introducido
            system("cls");
            printf("\n\t\t  JUGADOR 2\n\n");
            Ver_Flota(MarIn);
            printf("Error en las coordenadas no pueden ser ni superior a 7 tampoco menor a 0\n Elige otra coordenada: ");
        }
    if(Mar1[coo[0]][coo[1]]==1)
    {
        MarIn[coo[0]][coo[1]]=1;
        aciertos++;
        cant_dis2++;
    }
    if(Mar1[coo[0]][coo[1]]==0)
    {
        MarIn[coo[0]][coo[1]]=2;
        cant_dis2++;
    }

    coo[0]=-1;
    coo[1]=-1;
    system("cls");
}
    printf("\n\n\n\n\n\n\n\n\n\n\t\tHa destruido la flota del contrincante con %i disparos",cant_dis2);
    getch();
    system("cls");
    if(cant_dis1<cant_dis2)
    {
        aciertos=cant_dis1;
        printf("\n\n\n\n\n\n\n\n\n\n\t\tGANADOR: JUGADOR 1\n\t\t==================\n\t\tResultados\n\t\tJugador 1: %d disparos\n\t\tJugador 2: %d disparos",cant_dis1,cant_dis2);
    }

    if(cant_dis2<cant_dis1)
    {
        aciertos=cant_dis2;
        printf("\n\n\n\n\n\n\n\n\n\n\t\tGANADOR: JUGADOR 2\n\t\t==================\n\t\tResultados\n\t\tJugador 1: %d disparos\n\t\tJugador 2: %d disparos",cant_dis1,cant_dis2);
    }
    if(cant_dis2==cant_dis1)
       {
           empate=1;
           printf("\n\n\n\n\n\n\n\n\n\n\t\tJUEGO EMPATADO\n\t\t==============\n\t\tResultados\n\t\tJugador 1: %d disparos\n\t\tJugador 2: %d disparos",cant_dis1,cant_dis2);

       }
       getch();
    //textos de resultados

    i = 0;
    fp = fopen("estadisticas.txt", "r+");

    if(fp == NULL){
    printf("Error abriendo estadisticas.txt\n");
    exit(0);
    }

    while(!feof(fp)){
    fscanf(fp, "%[A-Z: ] %d \n", frase,&puntos[i]);
    i++;
    }

    if(aciertos<puntos[0])
            puntos[0]=aciertos;
    if(aciertos==cant_dis1&&empate==0)
            puntos[2]++;
    if(aciertos==cant_dis2&&empate==0)
            puntos[4]++;
    if(empate==1)
            puntos[5]++;
    if(cant_dis1+cant_dis2>puntos[6])
        puntos[6]=cant_dis1+cant_dis2;

    fseek(fp,0,0);//moverse al inicio del archivo
    fflush(fp);
    fprintf(fp, "RECORD: %d\nJUGADOR 1: %d\nJUGADOR 2:  %d\nEMPATES: %d\nPARTIDA MAS LARGA: %d\n"+'\0', puntos[0],puntos[2],puntos[4],puntos[5],puntos[6]);
    //grabamos archivo
    printf("\n\tGrabado");
    fclose(fp);


}

int Validad_Coordenada(int Mar[8][8],int coord[2],char orienta[2],int tam)
{
    int sum,i;

    sum = atoi(tam);

    if(coord[0]<0||coord[0]>7||coord[1]<0||coord[1]>7)
    {
    return 1;
    }
    if(strcmp(orienta, "h") != 0 && strcmp(orienta, "v") != 0 && strcmp(orienta, "H") != 0 && strcmp(orienta, "V") != 0 )//orienta=="h"||orienta=="v"||orienta=="H"||orienta=="V")
    {
    return 1;
    }
    else
    {
    if(strcmp(orienta, "h") == 0 || strcmp(orienta, "H") == 0)
    {
        if(sum+coord[1]>8)
            return 1;
        for(i=0;i<sum;i++)
            if(Mar[coord[0]][coord[1]+i]==1)
                return 1;
    }
    if(strcmp(orienta, "v") == 0 || strcmp(orienta, "V") == 0)
    {
        if(sum+coord[0]>8)
            return 1;
        for(i=0;i<sum;i++)
            if(Mar[coord[0]+i][coord[1]]==1)
                return 1;
    }
    }
    //reviza si los datos usuario
    return 0;

}

void Ver_Flota(int Mar[8][8])
{
printf("\n\t\t  [0|1|2|3|4|5|6|7|\n\t\t  [---------------|\n\t\t0 [");
printf("%d|%d|%d|%d|%d|%d|%d|%d|\n\t\t1 [",Mar[0][0],Mar[0][1],Mar[0][2],Mar[0][3],Mar[0][4],Mar[0][5],Mar[0][6],Mar[0][7]);
printf("%d|%d|%d|%d|%d|%d|%d|%d|\n\t\t2 [",Mar[1][0],Mar[1][1],Mar[1][2],Mar[1][3],Mar[1][4],Mar[1][5],Mar[1][6],Mar[1][7]);
printf("%d|%d|%d|%d|%d|%d|%d|%d|\n\t\t3 [",Mar[2][0],Mar[2][1],Mar[2][2],Mar[2][3],Mar[2][4],Mar[2][5],Mar[2][6],Mar[2][7]);
printf("%d|%d|%d|%d|%d|%d|%d|%d|\n\t\t4 [",Mar[3][0],Mar[3][1],Mar[3][2],Mar[3][3],Mar[3][4],Mar[3][5],Mar[3][6],Mar[3][7]);
printf("%d|%d|%d|%d|%d|%d|%d|%d|\n\t\t5 [",Mar[4][0],Mar[4][1],Mar[4][2],Mar[4][3],Mar[4][4],Mar[4][5],Mar[4][6],Mar[4][7]);
printf("%d|%d|%d|%d|%d|%d|%d|%d|\n\t\t6 [",Mar[5][0],Mar[5][1],Mar[5][2],Mar[5][3],Mar[5][4],Mar[5][5],Mar[5][6],Mar[5][7]);
printf("%d|%d|%d|%d|%d|%d|%d|%d|\n\t\t7 [",Mar[6][0],Mar[6][1],Mar[6][2],Mar[6][3],Mar[6][4],Mar[6][5],Mar[6][6],Mar[6][7]);
printf("%d|%d|%d|%d|%d|%d|%d|%d|\n",Mar[7][0],Mar[7][1],Mar[7][2],Mar[7][3],Mar[7][4],Mar[7][5],Mar[7][6],Mar[7][7]);

}

int Edicion_Mar(int Mar[8][8],int coord[2],char orienta[2],int tam)
{
int i;
int sum;
sum=tam;
sum = atoi(tam);
//comvertimos tam to int
for(i=0;i<sum;i++)
{

    if(strcmp(orienta, "h") == 0 ||strcmp(orienta, "H") == 0)
    {

        Mar[coord[0]][coord[1]+i]=1;
    }
    if(strcmp(orienta, "v") == 0 ||strcmp(orienta, "V") == 0)
    {
        Mar[coord[0]+i][coord[1]]=1;
    }
}
return Mar;
}
