#include <iostream>
#include "Board.h"

using namespace std;

char const* get_entry_rep(MOVE entry) {
    //given an entry from the board, return a "string" representation
    char const* entry_rep;
    if (entry == MOVE::EMPTY) {
        entry_rep = "EMPTY";
    } else if (entry == MOVE::O_PIECE) {
        entry_rep = "O_PIECE";
    } else {
        entry_rep = "X_PIECE";
    }
    return entry_rep;
}

void print_board_rep_layout(MOVE* board_copy, int num_rows, int num_cols) {
    //given a board copy and layout size, print out a basic board layout
    for (int row_index = 0; row_index < num_rows; row_index++) {
        for (int col_index = 0; col_index < num_cols; col_index++) {
            int general_index = row_index * num_cols + col_index;
            MOVE indexed_value = *(board_copy + general_index);

            char const* value_rep = get_entry_rep(indexed_value);
            cout << value_rep  << " ";
        }
        cout << endl;
    }
}

void process_winner(WINNER winner) {
    switch (winner) {
    case WINNER::X_WINNER:
        cout << "x is the winner" << endl;
        break;
    case WINNER::O_WINNER:
        cout << "o is the winner" << endl;
        break;
    case WINNER::NONE:
        cout << "nobody is the winner" << endl;
        break;
    }
}



int main()
{
    //playing a game
    //
    //
    int input_rows = 3;
    int input_cols = 3;
    int win_size = 3;
    PLAYER first_player = PLAYER::O_PLAYER;
    Board board(input_rows, input_cols, win_size, first_player);
    board.process_move(0,0); //o's move
    board.process_move(1,0); //x's move

    try {
        board.process_move(0,0);
    } catch (InvalidMoveError e) {
        cout << "InvalidMoveError, " << e.get_error() << endl;
    }

    board.process_move(0,1); //o's move
    board.process_move(1,1); //x's move
    board.process_move(0,2);

    try {
        board.process_move(2,0);
    } catch (GameOverError e) {
        cout << "GameOverError, " << e.get_error() << endl;
    }

    //getting data from board object
    //
    //
    MOVE* copied = board.get_board_copy();
    int* layout = board.get_board_layout();
    int num_rows = *(layout + 0);
    int num_cols = *(layout + 1);
    int total_board_size = *(layout + 2);
    delete layout;
    print_board_rep_layout(copied, num_rows, num_cols);

    //checking winner
    //
    //
    WINNER winner = board.check_winner();
    process_winner(winner);

    return 0;
}

