/*
 * Ata Berke Yargıç - 2638328
 * CNG 140 Assignment-2 (Circle Game)
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 10
#define PLAYER 'P'
#define COMPUTER 'C'


// Function prototypes.
int stepPlayer(char [BOARD_SIZE][BOARD_SIZE], int, int, int, int, int, int);

int stepComputer(char [BOARD_SIZE][BOARD_SIZE], int, int, int, int, int, int);

int move(char [BOARD_SIZE][BOARD_SIZE], int, int, int, int, int, int, char);

int checkTrapIndex(int, int);

void generateTrapIndex(int *, int *);

void generateTrapValues(int *, int *);

void displayBoard(char [BOARD_SIZE][BOARD_SIZE], int, int);

int rollDice(void);

int checkIsOnTrap(int, int, int, int, int);


int main() {
    int pointP = 0, pointC = 0;
    int row = BOARD_SIZE, col = BOARD_SIZE; // Dimensions of the game board.
    int dice1, dice2;
    int quit = 0; // Default value is 0, if user don't want to play again it is 1.
    int *c_trap_row, *c_trap_col; // Row and col values for computer trap index.
    int p_trap[2], c_trap[2], p_trap_val, c_trap_val; /* player trap index (row col),
                                                  * computer trap index (row col),
                                                  * player's trap val.
                                                  * computer's trap val.
                                                  */

    char p_board[BOARD_SIZE][BOARD_SIZE]; // Player's board.
    char c_board[BOARD_SIZE][BOARD_SIZE]; // Computer's board.
    char y_n; // Answer of the Y/N question at the end.

    c_trap_row = &c_trap[0];
    c_trap_col = &c_trap[1];

    printf("\nWelcome to the Circle Game! :)");
    printf("\nLet's get started!\n");

    while (quit == 0) {
        // Continue to play until user don't want to play anymore.
        srand(time(NULL)); // Set randomness seed of the dice according to the time.

        int start = 2; // Player starts if 0, computer starts if 1, default = 2;
        int is_over = 0; // Default value is 0, when one of the players won it is 1.
        int p_win = 0, c_win = 0; // Variable to determine if player and user completed a circle.

        for (int i = 0; i < row; i++) {
            // Reset game boards.
            for (int j = 0; j < col; j++) {
                p_board[i][j] = ' ';
                c_board[i][j] = ' ';
            }
        }

        p_board[0][0] = 'P'; // Starting point for player.
        c_board[9][9] = 'C'; // Starting point for computer.

        generateTrapIndex(c_trap_row, c_trap_col); // Generate trap index for computer.
        generateTrapValues(&c_trap_val, &p_trap_val); // Generate trap values randomly for all players.
        c_trap[0] = *c_trap_row;
        c_trap[1] = *c_trap_col;

        printf("\n----Player----");
        int a = 0; // It will be 1 when user enters a valid trap index.
        while (a == 0) {
            // Get the trap index from the user until user enters valid input.
            printf("\nEnter trap index (row col):");
            scanf("%d %d", &p_trap[0], &p_trap[1]);
            fflush(stdin);

            a = checkTrapIndex(p_trap[0], p_trap[1]); // Check if index is valid.
        }
        printf("Generated trap value: %d", p_trap_val);

        printf("\n----Computer----");
        printf("\nGenerated trap index (row col): %d %d", c_trap[0], c_trap[1]);
        printf("\nGenerated trap value: %d", c_trap_val);

        while (start == 2) {
            // Roll the dice until someone rolls bigger.
            dice1 = rollDice();
            dice2 = rollDice();
            printf("\n\nI have rolled the dice and got %d!", dice2);
            printf("\nI have rolled the dice for you and you got %d!", dice1);

            if (dice1 > dice2)
                start = 0; // Player starts.
            else if (dice2 > dice1)
                start = 1; // Computer starts.
            else
                printf("\n\nOur dice are equal, I roll the dice again.");
        }

        // Display initial boards at the beginning.
        printf("\n\n----Initial boards----");
        printf("\n           Player Board");
        displayBoard(p_board, row, col); // Display player's board.
        printf("\n          Computer Board");
        displayBoard(c_board, row, col); // Display computer's board.

        int round = 1;
        switch (start) {
            case 0: // Player starts.
                while (is_over == 0) {
                    // Play until someone completes the circle.
                    printf("\n----Round %d----", round);

                    dice1 = rollDice(); // Roll the dice for Player.
                    printf("\nI have rolled the dice for you and you got %d!", dice1);

                    // Player's turn.
                    p_win = stepPlayer(p_board, row, col,
                                       dice1, p_trap[0],
                                       p_trap[1], p_trap_val);
                    if (p_win == 1) {
                        is_over = 1;
                    }

                    dice2 = rollDice(); // Roll the dice for Computer.
                    printf("\nI have rolled the dice and got %d!", dice2);

                    // Computer's turn.
                    c_win = stepComputer(c_board, row, col,
                                         dice2, c_trap[0],
                                         c_trap[1], c_trap_val);
                    if (c_win == 1) {
                        is_over = 1;
                    }


                    printf("\n\n           Player Board");
                    displayBoard(p_board, row, col); // Display player's board.

                    printf("\n          Computer Board");
                    displayBoard(c_board, row, col); // Display computer's board.

                    round++;
                }
                break;
            case 1: // Computer starts:
                while (is_over == 0) {
                    // Play until someone completes the circle.
                    printf("\n----Round %d----", round);

                    dice1 = rollDice(); // Roll the dice for Computer.
                    printf("\nI have rolled the dice and got %d!", dice1);

                    // Computer's turn.
                    c_win = stepComputer(c_board, row, col,
                                         dice1, c_trap[0],
                                         c_trap[1], c_trap_val);
                    if (c_win == 1) {
                        is_over = 1;
                    }

                    dice2 = rollDice(); // Roll the dice for Player.
                    printf("\nI have rolled the dice for you and you got %d!", dice2);

                    // Player's turn.
                    p_win = stepPlayer(p_board, row, col,
                                       dice2, p_trap[0],
                                       p_trap[1], p_trap_val);
                    if (p_win == 1) {
                        is_over = 1;
                    }


                    printf("\n\n           Player Board");
                    displayBoard(p_board, row, col); // Display player's board.

                    printf("\n          Computer Board");
                    displayBoard(c_board, row, col); // Display computer's board.

                    round++;
                }
                break;
        }

        printf("\n----END----");
        if (p_win == 1 && c_win == 1) // Tie.
            printf("\nTie!!!");
        else if (c_win == 1) {
            // Computer won.
            printf("\nI won!!!");
            pointC++;
        } else if (p_win == 1) {
            // Player won.
            printf("\nYou won!!!");
            pointP++;
        }

        //Print overall score.
        printf("\n\n-----Score Board-----\nPlayer = %d\nComputer = %d",pointP, pointC);

        // Ask if player wants to play again.
        printf("\n\nWould you like to play again (Y/N)?");
        scanf(" %c", &y_n);
        fflush(stdin);

        if (y_n == 'Y' || y_n == 'y')
            quit = 0;
        else if (y_n == 'N' || y_n == 'n')
            quit = 1;
    }

    return 0;
}


//Function to move player. If one circle completed return 1, else return 0.
int stepPlayer(char board[BOARD_SIZE][BOARD_SIZE], int row, int col, int step, int t_row, int t_col, int trap_val) {
    /* To make a move, the sides of the game board are first scanned to find the current position.
     * Then check whether the move is landing on the trap index. If the move ends at the trap index,
     * the number of steps is recalculated according to the trap value (new step = step - trap value).
     * If the new step count is 0 or less than 0, no move is made. If it is greater than 0,
     * move clockwise along the sides until the number of remaining step is 0.
     */

    int is_trap; // Default value is 0, it will be 1 if movement ended on a trap.
    int old_step; // Save old step value to print it after calculated new step val.
    int is_empty = 0; // Default value is 0, it will be 1 when the first empty index around the board is determined.
    int dir; // Direction value for movement. (Right = 0, Down = 1, Left = 2, Up = 3)
    int p_row, p_col; // Row and column data for the position on the board.

    // Scan the top side for the position.
    for (int i = 0; i <= (col - 1); i++) {
        if (board[0][i] != PLAYER && is_empty == 0) {
            p_row = 0;
            p_col = i - 1;
            is_empty = 1;
            dir = 0; // Set direction.
        }
    }

    // Scan the right side for the position .
    for (int i = 0; i <= (row - 1); i++) {
        if (board[i][9] != PLAYER && is_empty == 0) {
            p_row = i - 1;
            p_col = 9;
            is_empty = 1;
            dir = 1; // Set direction.
        }
    }


    // Scan the bottom side for the position.
    for (int i = (col - 1); i >= 0; i--) {
        if (board[9][i] != PLAYER && is_empty == 0) {
            p_row = 9;
            p_col = i + 1;
            is_empty = 1;
            dir = 2; // Set direction.
        }
    }


    // Scan the left side for the position.
    for (int i = (row - 1); i >= 0; i--) {
        if (board[i][0] != PLAYER && is_empty == 0) {
            p_row = i + 1;
            p_col = 0;
            is_empty = 1;
            dir = 3; // Set direction.
        }
    }

    if (is_empty == 0) {
        // If is_empty = 0, that means player is on (1,0).
        p_row = 1;
        p_col = 0;
        dir = 3;
    }


    // Check trap. If landed on the trap, calculate step and check again.
    is_trap = checkIsOnTrap(step, p_row, p_col, t_row, t_col);
    if (is_trap == 1) {
        old_step = step;
        step = step - trap_val;

        if (step < 0)
            step = 0;

        printf("\nTrapped at index %d %d! %d forward - %d backward = %d step.",
               t_row, t_col, old_step, trap_val, step);
    }


    // Move the player. If circle completed, return 1. Else 0.
    return move(board, dir, step, row, col, p_row, p_col, PLAYER);
}


//Function to move computer. If one circle completed return 1, else return 0.
int stepComputer(char board[BOARD_SIZE][BOARD_SIZE], int row, int col, int step, int t_row, int t_col, int trap_val) {
    /* To make a move, the sides of the game board are first scanned to find the current position.
     * Then check whether the move is landing on the trap index. If the move ends at the trap index,
     * the number of steps is recalculated according to the trap value (new step = step - trap value).
     * If the new step count is 0 or less than 0, no move is made. If it is greater than 0,
     * move clockwise along the sides until the number of remaining step is 0.
     */

    int is_trap;      // Default value is 0, it will be 1 if movement ended on a trap.
    int old_step;
    int is_empty = 0; // Default value is 0, it will be 1 when the first empty index around the board is determined.
    int dir;          // Direction value for movement. (Right = 0, Down = 1, Left = 2, Up = 3)
    int p_row, p_col; // Row and column data for the position on the board.

    // Scan the bottom side for the position.
    for (int i = 9; i > 0; i--) {
        if (board[9][i] != COMPUTER && is_empty == 0) {
            p_row = 9;
            p_col = i + 1;
            is_empty = 1;
            dir = 2;
        }
    }

    // Scan the left side for the position.
    for (int i = (row - 1); i >= 0; i--) {
        if (board[i][0] != COMPUTER && is_empty == 0) {
            p_row = i + 1;
            p_col = 0;
            is_empty = 1;
            dir = 3;
        }
    }

    // Scan the top side for the position.
    for (int i = 0; i <= (col - 1); i++) {
        if (board[0][i] != COMPUTER && is_empty == 0) {
            p_row = 0;
            p_col = i - 1;
            is_empty = 1;
            dir = 0;
        }
    }

    // Scan the right side for the position.
    for (int i = 0; i <= (row - 1); i++) {
        if (board[i][9] != COMPUTER && is_empty == 0) {
            p_row = i - 1;
            p_col = 9;
            is_empty = 1;
            dir = 1;
        }
    }

    if (is_empty == 0) {
        // If is_empty = 0, that means computer is on (8,9).
        p_row = 8;
        p_col = 9;
        dir = 1;
    }


    // Check trap. If landed on the trap, calculate step and check again.
    is_trap = checkIsOnTrap(step, p_row, p_col, t_row, t_col);
    if (is_trap == 1) {
        old_step = step;
        step = step - trap_val;

        if (step < 0)
            step = 0;

        printf("\nTrapped at index %d %d! %d forward - %d backward = %d step.",
               t_row, t_col, old_step, trap_val, step);
    }

    // Move the computer. If circle completed, return 1. Else 0.
    return move(board, dir, step, row, col, p_row, p_col, COMPUTER);
}


// Move according to the direction value.
int move(char board[BOARD_SIZE][BOARD_SIZE], int dir, int step, int row, int col, int p_row, int p_col, char player) {
    // Move clockwise along the sides until the number of remaining step is 0. If circle completed, return 1. Else 0.

    switch (dir) {
        case 0: // Move to the right. If necessary down.
            for (int i = 0; i < (col - 1); i++) {
                if (step > 0 && p_col < col - 1) {
                    step--;
                    p_col++;
                    board[0][p_col] = player;
                }
            }
            for (int i = 0; i < (row - 1); i++) {
                if (step > 0 && p_row < row - 1) {
                    step--;
                    p_row++;
                    board[p_row][9] = player;
                }
            }
            break;
        case 1: // Move to the down.
            for (int i = 0; i < (row - 1); i++) {
                if (step > 0 && p_row < row - 1) {
                    step--;
                    p_row++;
                    board[p_row][9] = player;
                    if (p_row == 9 && player == 'C')
                        return 1;
                }
            }
            for (int i = (col - 1); i > 0; i--) {
                if (step > 0 && p_col > 0) {
                    step--;
                    p_col--;
                    board[9][p_col] = player;
                }
            }
            break;
        case 2: // Move to the left. If necessary up.
            for (int i = (col - 1); i > 0; i--) {
                if (step > 0 && p_col > 0) {
                    step--;
                    p_col--;
                    board[9][p_col] = player;
                }
            }
            for (int i = (row - 1); i > 0; i--) {
                if (step > 0 && p_row > 0) {
                    step--;
                    p_row--;
                    board[p_row][0] = player;
                }
            }
            break;
        case 3: // Move to the up. If necessary right.
            for (int i = (row - 1); i > 0; i--) {
                if (step > 0 && p_row > 0) {
                    step--;
                    p_row--;
                    board[p_row][0] = player;
                    if (p_row == 0 && player == 'P')
                        return 1;
                }
            }
            for (int i = 0; i < (col - 1); i++) {
                if (step > 0 && p_col < col - 1) {
                    step--;
                    p_col++;
                    board[0][p_col] = player;
                }
            }
    }

    return 0;
}


// Check if the index is placed around the board.
int checkTrapIndex(int row, int col) {
    // Return 1 if it is around the board, else return 0.

    if (row == 0 || row == 9) {
        if (col >= 0 && col <= 9)
            return 1;
        else
            printf("The trap index should be placed around the board.");
    } else if ((col == 0 || col == 9)) {
        if (row >= 0 && row <= 9)
            return 1;
        else
            printf("The trap index should be placed around the board.");
    } else
        printf("The trap index should be placed around the board.");

    return 0;
}


//Generate trap index around the board for computer randomly.
void generateTrapIndex(int *row, int *col) {
    *row = rand() % 10; // Randomly generate a number between 0 and 9.

    if (*row == 0 || *row == 9)
        *col = rand() % 10; // Randomly generate a number between 0 and 9.
    else {
        int correct = 0;
        while (correct == 0) {
            *col = rand() % 10; // Randomly generate a number between 0 and 9.
            if (9 - *col == 0 || 9 - *col == 9)
                correct = 1;
        }
    }
}


// Generate trap values for computer and player in range [1,5].
void generateTrapValues(int *c_trap_val, int *p_trap_val) {
    *c_trap_val = 1 + rand() % 5; // Randomly generate a number between 1 and 5.
    *p_trap_val = 1 + rand() % 5;
}


// Display the game board.
void displayBoard(char board[BOARD_SIZE][BOARD_SIZE], int row, int col) {
    printf("\n   0  1  2  3  4  5  6  7  8  9\n");
    for (int i = 0; i < row; i++) {
        printf("%d", i);
        for (int j = 0; j < col; j++) {
            printf("  %c", board[i][j]);
        }
        printf("\n");
    }
}


// Randomly generate a number between 1 and 6 for dice.
int rollDice(void) {
    return 1 + rand() % 6;
}


// Check if the move is on trap or not.
int checkIsOnTrap(int step, int p_row, int p_col, int t_row, int t_col) {
    int is_trap = 0; // Default is 0, if trapped it is 1.

    if (p_row == 0) {
        // Check move on top side.
        while (step > 0 && p_col < 9 && is_trap == 0) {
            p_col++;
            step--;
            if (p_row == t_row && p_col == t_col) {
                if (step == 0) {
                    is_trap = 1;
                }
            }
        }
    }
    if (p_col == 9 && is_trap == 0) {
        // Check move on right side.
        while (step > 0 && p_row < 9 && is_trap == 0) {
            p_row++;
            step--;
            if (p_row == t_row && p_col == t_col) {
                if (step == 0) {
                    is_trap = 1;
                }
            }
        }
    }
    if (p_row == 9 && is_trap == 0) {
        // Check move on bottom side.
        while (step > 0 && p_col > 0 && is_trap == 0) {
            p_col--;
            step--;
            if (p_row == t_row && p_col == t_col) {
                if (step == 0) {
                    is_trap = 1;
                }
            }
        }
    }
    if (p_col == 0 && is_trap == 0) {
        // Check move on left side.
        while (step > 0 && p_row > 0 && is_trap == 0) {
            p_row--;
            step--;
            if (p_row == t_row && p_col == t_col) {
                if (step == 0) {
                    is_trap = 1;
                }
            }
        }
    }
    if (p_row == 0 && is_trap == 0) {
        // Check move on top side.
        while (step > 0 && p_col < 9 && is_trap == 0) {
            p_col++;
            step--;
            if (p_row == t_row && p_col == t_col) {
                if (step == 0) {
                    is_trap = 1;
                }
            }
        }
    }
    if (p_col == 9 && is_trap == 0) {
        // Check move on right side.
        while (step > 0 && p_row < 9 && is_trap == 0) {
            p_row++;
            step--;
            if (p_row == t_row && p_col == t_col) {
                if (step == 0) {
                    is_trap = 1;
                }
            }
        }
    }

    return is_trap;
}
