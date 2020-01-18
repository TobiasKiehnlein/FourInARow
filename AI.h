//
// Created by Tobias Kiehnlein on 16.12.19.
//

#ifndef FOURINAROW_AI_H
#define FOURINAROW_AI_H

int calc_move(int board[5][6]);

int is_winning_move(int board[5][6], int move);

void insert_stone(int board[5][6], int position, int player);

#endif //FOURINAROW_AI_H
