//
// Created by Tobias Kiehnlein on 16.12.19.
//

#include <stdio.h>
#include <stdlib.h>
#include "printing.h"

void clear_screen();

void print_navigation() {
    int i;
    clear_screen();
    for (i = 0; i < 7; i++)
        printf("  %i ", i + 1);
    printf("\n");
}

void print_board(int board[5][6]) {
    int i;
    print_navigation();
    print_divider(1);

    for (i = 5; i > -1; --i) {
        print_game_line(board[i], 0);
        if (i != 0) print_divider(0);
    }

    print_divider(-1);
}


/**
 * Prints a line for the game Field
 * @param position -1 if bottom, 0 if middle, 1 if top
 */
void print_divider(int position) {
    int i;
    switch (position) {
        case 1:
            printf("┏");
            break;
        case -1:
            printf("┗");
            break;
        default:
            printf("┣");
            break;
    }
    for (i = 0; i < 6; ++i) {
        printf("━━━");
        switch (position) {
            case 1:
                printf("┳");
                break;
            case -1:
                printf("┻");
                break;
            default:
                printf("╋");
                break;
        }
    }
    printf("━━━");
    switch (position) {
        case 1:
            printf("┓");
            break;
        case -1:
            printf("┛");
            break;
        default:
            printf("┫");
            break;
    }
    printf("\n");
}

void print_game_line(int *line, int legacy_printing) {
    int i;
    printf("┃");
    for (i = 0; i < 7; ++i) {
        if (!legacy_printing) {
            print_color(line[i]);
            line[i] == 0 ? printf("   ") : printf(" o ");
            print_color(0);
        } else {
            switch (line[i]) {
                case 1:
                    printf(" x ");
                    break;
                case -1:
                    printf(" o ");
                    break;
                default:
                    printf("   ");
            }
        }
        printf("┃");
    }
    printf("\n");
}

/**
 * prints the color
 * @param player -1 First player, 0 neutral, 1 Second Player
 */
void print_color(int player) {
    switch (player) {
        case 1:
            printf("\033[0;31m"); /*red*/
            break;
        case -1:
            printf("\033[0;33m");/*yellow*/
            break;
        default:
            printf("\033[0m");/*neutral*/
            break;
    }
}

void print_menu_header() {
    clear_screen();
    printf("\033[0;31m  _ _   \033[0;33m _       \033[0;31m       \033[0;33m                \n"
           "\033[0;31m | | |  \033[0;33m(_)_ _   \033[0;31m __ _  \033[0;33m _ _ _____ __ __\n"
           "\033[0;31m |_  _| \033[0;33m| | ' \\ \033[0;31m / _` |\033[0;33m | '_/ _ \\ V  V /\n"
           "\033[0;31m   |_|  \033[0;33m|_|_||_| \033[0;31m\\__,_|\033[0;33m |_| \\___/\\_/\\_/\n"
           "\033[0m by Miriam Leupold and Tobias Kiehnlein\n"
           "\n\n\033[0;33mSelect option:\n\n"
           "\t\033[0;33m(1)\033[0m Single player game\n"
           "\t\033[0;33m(2)\033[0m Two player game\n"
           "\t\033[0;33m(3)\033[0m Quit game\n");
}

void clear_screen() {
    system("@cls||clear");
}
