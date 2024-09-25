# Battleship Game

## Introduction

This project aims to develop an application that encapsulates basic concepts like:

- Declaration and types of variables
- Conditional structures
- Loops
- Vectors, arrays, and strings
- Functions
- Pointers
- Structures
- Files

## Statement

The program simulates the traditional game **Battleship**. It will load information from the `barcos.txt` file, which should follow this format:

```NAME OF THE SHIP, SIZE```

Where:
- **NAME OF THE SHIP**: the name assigned to the ship (String).
- **SIZE**: the number of squares occupied by the ship on the board (Integer).

**Example**:
Aircraft Carrier, 5
Destroyer, 4
Corvette, 2
Frigate, 3
Submarine, 3

In this example, five different types of ships are defined. The program should specify the number of ships in the game and ensure that the `barq.txt` file contains exactly this number.

For reading this file, it is recommended to define a structure with the same fields as those defined in the file and declare a vector of this structured type (`struct barcos[maxBarcos]`) to gather information about all the ships. Remember that each data is separated by a comma and space, and there is a newline at the end of each line.

Additionally, there is initially a `estadisticas.txt` file with the following format:
```
RECORD: 4242
JUGADOR 1: 0
JUGADOR 2: 0
EMPATES: 0
PARTIDA MAS LARGA: 0
```
The file collects the game's statistics:
- The **record** keeps track of the minimum number of shots required for a player to win a game.
- **PLAYER 1** counts how many times Player 1 has won.
- **PLAYER 2** counts how many times Player 2 has won.
- **DRAWS** counts how many times there has been a draw (both players have used the same number of shots to eliminate the rival fleet).
- **LONGEST GAME** keeps track of the total shots taken by both players that took the longest to destroy the rival fleet.

## Main Menu

The program will display the following main menu:
```
[1] - Start new game
[2] - Modify fleet
[3] - View statistics
[0] - Exit
```
### Start New Game

Each player will have an 8x8 matrix where they will place their ships. Initially, this matrix will be initialized to 0 (water). Each position occupied by a ship will be identified with a 1.

The program will prompt each player to input the coordinates of each of their ships in the fleet. Player 1 will specify, ship by ship, the square where it starts and the orientation (horizontal or vertical). After finishing, Player 2 will do the same.

The program will check that the ships are correctly placed. To do this, it is recommended to create a function that checks each of the following cases:
- The input coordinates must be between 0 and 7.
- The orientation of the ships can only be horizontal or vertical.
- The ship being introduced does not exit the board.
- No attempt should be made to place a ship in occupied coordinates.

The function will return 0 if the coordinates of the ship are correct, and 1 if they are not.

If a ship is introduced incorrectly, an error message will be displayed.

At this point, the player can see the positions of their ships on the board.

### Start Game

Once both players have introduced their ships, the game begins. Player 1 will take turns until they destroy the entire enemy fleet. Next, it will be Player 2's turn.

The program should count how many effective shots each player has taken to see who wins. It is recommended to create a different matrix for each player in which to mark the positions where shots have been fired.

The player who shoots will visualize the shot matrix to know which squares have been shot at and whether they have hit an enemy ship or not. 

Once the fleet is destroyed, the following message will be displayed, and Player 2's turn will begin:

When both players have finished with their rival's ships, the results of the game will be shown. With the results obtained, statistics will need to be updated.

The program will return to the initial menu.

### Modify Fleet

From this option, the user can modify the ships of the game. Before this, they will need to identify themselves with a password of string type (e.g., "12345"). The program will display the information of each ship and ask the user if they want to change it.

The changes will be saved in the `barq.txt` file, which must maintain the previously specified format.

### Show Statistics

With this option, the `estadisticas.txt` file will be read, and the data will be displayed on the screen.

### Exit

With this option, the application ends with a message.
