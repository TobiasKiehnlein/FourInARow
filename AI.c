//
// Created by Tobias Kiehnlein on 16.12.19.
//

#include <stdlib.h>
#include "constants.h"

int column_available(int board[5][6], int column);

void insert_stone(int board[5][6], int position, int player);

int rate_board(int board[5][6]);

int calc_move(int board[5][6]) {
//    int boardCopy[5][6], i, j;
//    for (i = 0; i < 6; ++i)
//        for (j = 0; j < 7; ++j)
//            boardCopy[i][j] = board[i][j];
//
//    /*Check all available options recursively*/
//    for (i = 0; i < 7; ++i) {
//        if (column_available(boardCopy, i)) {
//            insert_stone(boardCopy, i, AI);
//            calc_move(boardCopy);
//        }
//    }
    return rand() % 7;
}

int column_available(int board[5][6], int column) {
    return !board[5][column];
}

void insert_stone(int board[5][6], int position, int player) {
    int row = 0;
    while (row < 6 && board[row][position] != 0)
        row++;
    if (row != 6)
        board[row][position] = player;
}

int rate_board(int board[5][6]) {
    return rand() * (rand() % 2 * -1);
}

/**
 * Checks whether given move wins the game
 * @param board The current game board containing the move
 * @param move The move that was made last
 * @return
 */
int is_winning_move(int board[5][6], int move) {
    int i, player, top_left, top, top_right, right, bottom_right, bottom, bottom_left, left;
    for (i = 5; i >= 0; --i)
        if (board[5 - i][move] != 0)
            break;

    player = board[i][move];

    /*Check around*/
    if (i != 5) {
        /*Check fields on top*/
        if (move != 0)
            top_left = board[i - 1][move - 1] == player;
        top = board[i - 1][move] == player;
        //if(move!=)
    }
}
