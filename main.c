#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "AI.h"
#include "constants.h"
#include "printing.h"

void initialize_board(int board[5][6]);

void game_manager(int board[5][6], int player, int use_ai, char message[]);

int ask_for_move(int player);

int detect_game_ending(int board[5][6]);

void main_menu(char *message, int color);

void start_game(int use_ai);

void flush(char c);

int main() {
    /*Set time as seed*/
    srand(time(NULL));
    /*opening the main menu*/
    main_menu("", 0);
    return 0;
}

/**
 * Display the main menu of the game
 * @param message The message will be displayed at the bottom of the menu. Place important game information there.
 * @param color The color of the message (Either PLAYER (RED), AI (YELLOW), or 0 (white))
 */
void main_menu(char *message, int color) {
    char c;

    /*Print the head of the main menu*/
    print_menu_header();

    /*Display message if given*/
    if (message[0] != 0) {
        print_color(color);
        printf("\n%s\n", message);
        print_color(0);
    }

    printf("\n");

    /*Getting user input*/
    c = getchar();

    /*Handling empty input or two char input*/
    if (c == '\n' || getchar() != '\n') {
        main_menu("Bitte geben Sie wählen Sie einen validen Wert ein...", 0);
        return;
    }

    /*Handle one char inputs*/
    switch (c) {
        case '1':
            start_game(1);
            break;
        case '2':
            start_game(0);
            break;
        case '3':
            exit(0);
        default:
            main_menu("Bitte geben Sie wählen Sie einen validen Wert ein...", 0);
    }
}

/**
 * Starts the game
 * @param use_ai true if the computer should be the second player
 */
void start_game(int use_ai) {
    int board[5][6];
    int player = rand() % 2 == 1 ? AI : PLAYER;
    initialize_board(board);
    print_board(board);
    game_manager(board, player, use_ai,0);
}

/**
 * The GameManager is responsible for handling all the necessary steps to run the game (e.g. triggering move calculation, triggering rerendering, etc).
 * It's called recursively
 * @param board the current game board
 * @param player the current player (Either PLAYER or AI)
 * @param use_ai true if the computer is the second player
 */
void game_manager(int board[5][6], int player, int use_ai, char message[]) {
    int position;

    if(message)
        printf("%s", message);

    /*Ask the player for a move if it's the first players turn or if it's a two player game. Calculate AI move otherwise*/
    if (player == PLAYER || !use_ai)
        position = ask_for_move(player);
    else if (player == AI)
        position = calc_move(board);
    else exit(1);

    if (position >= 0) {
        insert_stone(board, position, player);
        print_board(board);
        //const int gameEnding = is_winning_move(board, position);
        const int gameEnding = detect_game_ending(board);
        if (gameEnding > -2) {
            switch (gameEnding) {
                case 0:
                    main_menu("Das Spiel ist unentschieden zu Ende gegangen!", gameEnding);
                    break;
                case AI:
                    if (use_ai)
                        main_menu("AI hat gewonnen!!!", gameEnding);
                    else
                        main_menu("Spieler 2 hat gewonnen!!!", gameEnding);
                    break;
                case PLAYER:
                    if (use_ai)
                        main_menu("Spieler hat gewonnen!!!", gameEnding);
                    else
                        main_menu("Spieler 1 hat gewonnen!!!", gameEnding);
                    break;
                default:
                    main_menu("Es ist ein Fehler aufgetreten", 0);
            }
            return;
        }
        game_manager(board, player * -1, use_ai,0);
    } else
        game_manager(board, player, use_ai, "Bitte wählen Sie eine der Spalten von 1-7. ");
}

/**
 * Detects if the game is finished
 * @param board of the game
 * @return -2 if the game isn't finished yet, -1 if Player one has won the game, 0 if draw, 1 if second player won the match
 */
int detect_game_ending(int board[5][6]) {
    int row, column, count;

    /*Detect horizontal 4 in a row*/
    for (row = 0; row < 6; ++row) {
        count = 0;
        for (column = 0; column < 7; ++column) {
            if (board[row][column] == 0)
                count = 0;
            else if (board[row][column] == 1) {
                if (count > 0)
                    count++;
                else
                    count = 1;
            } else if (board[row][column] == -1) {
                if (count < 0)
                    count--;
                else
                    count = -1;
            }
            if (count == 4)
                return 1;
            if (count == -4)
                return -1;
        }
    }

    /*Detect vertical 4 in a row*/
    for (column = 0; column < 7; ++column) {
        count = 0;
        for (row = 0; row < 6; ++row) {
            if (board[row][column] == 0)
                count = 0;
            else if (board[row][column] == 1) {
                if (count > 0)
                    count++;
                else
                    count = 1;
            } else if (board[row][column] == -1) {
                if (count < 0)
                    count--;
                else
                    count = -1;
            }
            if (count == 4)
                return 1;
            if (count == -4)
                return -1;
        }
    }

    /*Diagonal 4 in a row left to right*/
    for (row = 0; row < 3; ++row) {
        for (column = 0; column < 4; ++column) {
            int current = board[row][column];
            if (current != 0 && current == board[row + 1][column + 1] && current == board[row + 2][column + 2] &&
                current == board[row + 3][column + 3])
                return current;
        }
    }

    /*Diagonal 4 in a row right to left*/
    for (row = 0; row < 3; ++row) {
        for (column = 6; column > 2; --column) {
            int current = board[row][column];
            if (current != 0 && current == board[row - 1][column - 1] && current == board[row - 2][column - 2] &&
                current == board[row - 3][column - 3])
                return current;
        }
    }

    int result = 0;
    for (row = 0; row < 6; ++row)
        for (column = 0; column < 7; ++column)
            if (board[row][column] == 0) {
                result = -2;
                break;
            }

    return result;
}

int ask_for_move(int player) {
    printf("Werfe Stein (");
    print_color(player);
    printf("o");
    print_color(0);
    printf(") in Spalte: ");
    char c = getchar();
    flush(c);
    if (c >= '1' && c <= '7')
        return c - '1';
    return -1;
}

void initialize_board(int board[5][6]) {
    int i, j;
    for (i = 0; i < 6; ++i)
        for (j = 0; j < 7; ++j)
            board[i][j] = 0;
}


void flush(char c) {
    while (c != '\n')
        c = getchar();
}