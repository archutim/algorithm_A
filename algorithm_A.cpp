#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../include/algorithm.h"
#define WIN_THE_GAME 31
using namespace std;

/******************************************************
 * In your algorithm, you can just use the the funcitons
 * listed by TA to get the board information.(functions 
 * 1. ~ 4. are listed in next block)
 * 
 * The STL library functions is not allowed to use.
******************************************************/

/*************************************************************************
 * 1. int board.get_orbs_num(int row_index, int col_index)
 * 2. int board.get_capacity(int row_index, int col_index)
 * 3. char board.get_cell_color(int row_index, int col_index)
 * 4. void board.print_current_board(int row_index, int col_index, int round)
 * 
 * 1. The function that return the number of orbs in cell(row, col)
 * 2. The function that return the orb capacity of the cell(row, col)
 * 3. The function that return the color fo the cell(row, col)
 * 4. The function that print out the current board statement
*************************************************************************/
int priority_cal(Board board, Player player){
    Board next_board[ROW][COL];
    char color = player.get_color();
    int priority = 30;
    for(int i=0;i<ROW;i++)
        for(int j=0;j<COL;j++)
            next_board[i][j] = board;
    for(int i=0;i<ROW;i++){
        for(int j=0;j<COL;j++){
            if(board.get_cell_color(i, j) == color || board.get_cell_color(i, j) == 'w'){
                next_board[i][j].place_orb(i, j, &player);
                if(next_board[i][j].win_the_game(player))
                    priority--;
            }
        }
    }
    return priority;
}

void algorithm_A(Board board, Player player, int index[]){
    Board next_board[ROW][COL];
    int dst_row, dst_col, current_priority, max_priority=-1;
    Player* opponent;
    char color = player.get_color();
    char colorOpponent = 'v'; // virtual player
    for(int i=0;i<ROW;i++){
        for(int j=0;j<COL;j++){
            if(board.get_cell_color(i,j)!='w' && board.get_cell_color(i,j)!=color)
                colorOpponent = board.get_cell_color(i,j);
        }
    }
    opponent = new Player(colorOpponent); 
    for(int i=0;i<ROW;i++)
        for(int j=0;j<COL;j++)
            next_board[i][j] = board;

    for(int i=0;i<ROW;i++){
        for(int j=0;j<COL;j++){
            if(board.get_cell_color(i, j) == color || board.get_cell_color(i, j) == 'w'){
                next_board[i][j].place_orb(i, j, &player);
                if(next_board[i][j].win_the_game(player))
                    current_priority = WIN_THE_GAME;
                else
                    current_priority = priority_cal(next_board[i][j], *opponent);
                if(current_priority>max_priority){
                    dst_row = i;
                    dst_col = j;
                    max_priority = current_priority;
                }
            }
        }
    }
    index[0] = dst_row;
    index[1] = dst_col;
}