#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include <stdio.h>
using namespace std;

enum MOVE {
    EMPTY,
    X_PIECE,
    O_PIECE
};

enum PLAYER {
    X_PLAYER,
    O_PLAYER
};

enum WINNER {
    NONE,
    X_WINNER,
    O_WINNER
};

const int BOARD_SIZE = 9;

class InvalidMoveError {
private:
    char const* error_message;

public:
    InvalidMoveError(char const* error_msg): error_message(error_msg) {}

    char const* get_error() {
        return error_message;
    }
};

class GameOverError {
private:
    char const* error_message;

public:
    GameOverError(char const* error_msg): error_message(error_msg) {}

    char const* get_error() {
        return error_message;
    }
};

class Board {
private:
    MOVE* board_grid;
    PLAYER current_player;
    int win_size;
    int total_board_size;
    int num_rows;
    int num_cols;

    void initialize_empty_board() {
        //knowing the total board size, initialize a 1-D board array
        board_grid = new MOVE[total_board_size];
        for (int i = 0; i < total_board_size; i++) {
            *(board_grid + i) = MOVE::EMPTY;
        }
    }

    void place_indexed_move(MOVE move_input, int board_index) {
        //using a board_index that's based on a board represented by a single_dimensional array, attempt to place a move
        if (board_index < 0 || board_index >= total_board_size) {
            cout << "Raising InvalidMoveError, with board index " << board_index << endl;
            throw InvalidMoveError("Board::place_move, the board index is out of range");
        } else if (*(board_grid + board_index) != MOVE::EMPTY) {
            throw InvalidMoveError("Board::place_move, the board index already has a move placed in it");
        } else {
            *(board_grid + board_index) = move_input;
        }
    };

    int get_move_index(int row_index, int col_index) {
        //using a zero-based row index and col index, return an index that would correspond with a single-dimensional list
        //so for ex. with row size of 3 and col size of 3
        //0 1 2
        //3 4 5
        //6 7 8
        //if I wanted the second row, first column, row_index = 1, col_index = 0, returns  3
        return row_index*num_cols + col_index;
    }

    void change_turn() {
        //switch player turns
        if (current_player == PLAYER::X_PLAYER) {
            current_player = PLAYER::O_PLAYER;
        } else {
            current_player = PLAYER::X_PLAYER;
        }
    }

    MOVE get_current_move() {
        //based on the current player, get corresponding MOVE to put into the board
        if (current_player == PLAYER::X_PLAYER) {
            return MOVE::X_PIECE;
        } else {
            return MOVE::O_PIECE;
        }
    }

    WINNER get_winner_from_move(MOVE move_entry) {
        //given a move, return winning, assuming someone won
        if (move_entry == MOVE::X_PIECE) {
            return WINNER::X_WINNER;
        } else {
            return WINNER::O_WINNER;
        }
    }

    void place_row_col_move(MOVE move_input, int row_index, int col_index) {
        //using a zero-based row_index and col_index, attempt to place a move
        int move_index = get_move_index(row_index, col_index);
        place_indexed_move(move_input, move_index);
    }

    WINNER check_horizontal_winner() {
        //scan, from left to right, then top to bottom, for a winner that's a horizontal row of entries
        if (win_size > num_cols) { //if the size of the winning row is greater than the number of columns, then there's no way for a win here
                //however, there could be a win in the vertical direction, depending if the board is oddly shaped
                //so return a no winner for now
            return WINNER::NONE;
        }

        int max_col_start = num_cols - win_size;
        for (int row_index = 0; row_index < num_rows; row_index++) {
            for (int col_index = 0; col_index <= max_col_start; col_index++) {
                int entry_index = get_move_index(row_index, col_index);
                MOVE entry_of_interest = board_grid[entry_index];

                if (entry_of_interest != MOVE::EMPTY) {
                    int same_count = 1;
                    while (same_count < win_size) {
                        entry_index += 1;
                        if (board_grid[entry_index] == entry_of_interest) {
                            same_count += 1;
                        } else {
                            break;
                        }
                    }

                    if (same_count == win_size) {
                        return get_winner_from_move(entry_of_interest);
                    }
                }
            }
        }
        return WINNER::NONE;
    }

    WINNER check_vertical_winner() {
        //scan, from top to bottom, left to right, for a win in the vertical direction
        if (win_size > num_rows) {
            return WINNER::NONE;
        }

        int max_row_start  = num_rows - win_size;
        for (int col_index = 0; col_index < num_cols; col_index++) {
            for (int row_index = 0; row_index <= max_row_start; row_index++) {
                int entry_index = get_move_index(row_index, col_index);
                MOVE entry_of_interest = board_grid[entry_index];

                if (entry_of_interest != MOVE::EMPTY) {
                    int same_count = 1;
                    while (same_count < win_size) {
                        entry_index += num_cols;
                        if (board_grid[entry_index] == entry_of_interest) {
                            same_count += 1;
                        } else {
                            break;
                        }
                    }

                    if (same_count == win_size) {
                        return get_winner_from_move(entry_of_interest);
                    }
                }
            }
        }
        return WINNER::NONE;
    }

    WINNER check_right_diagonal_winner() {
        //scan, from left to right, top to bottom, for a win in the downwards-right diagonal
        int max_row_start  = num_rows - win_size;
        int max_col_start = num_cols - win_size;
        for (int row_index = 0; row_index <= max_row_start; row_index++) {
            for (int col_index = 0; col_index <= max_col_start; col_index++) {
                int entry_index = get_move_index(row_index, col_index);
                MOVE entry_of_interest = board_grid[entry_index];

                if (entry_of_interest != MOVE::EMPTY) {
                    int same_count = 1;
                    while (same_count < win_size) {
                        entry_index += num_cols + 1;
                        if (board_grid[entry_index] == entry_of_interest) {
                            same_count += 1;
                        } else {
                            break;
                        }
                    }

                    if (same_count == win_size) {
                        return get_winner_from_move(entry_of_interest);
                    }
                }
            }
        }
        return WINNER::NONE;
    }

    WINNER check_left_diagonal_winner() {
        //scan, from right to left, top to bottom, for a win in the downwards-left diagonal
        int max_row_start = win_size - 1;
        int min_col_start = win_size - 1;

        if ((win_size > num_rows) || (win_size > num_cols)) {
            return WINNER::NONE;
        }

        for (int row_index = 0; row_index <= max_row_start; row_index++) {
            for (int col_index = num_cols - 1; col_index >= min_col_start; col_index--) {
                int entry_index = get_move_index(row_index, col_index);
                MOVE entry_of_interest = board_grid[entry_index];

                if (entry_of_interest != MOVE::EMPTY) {
                    int same_count = 1;
                    while (same_count < win_size) {
                        entry_index += num_cols - 1;
                        if (board_grid[entry_index] == entry_of_interest) {
                            same_count += 1;
                        } else {
                            break;
                        }
                    }

                    if (same_count == win_size) {
                        return get_winner_from_move(entry_of_interest);
                    }
                }
            }
        }
        return WINNER::NONE;
    }

public:
    Board(int num_rows, int num_cols, int win_size, PLAYER first_player):
        current_player(first_player), win_size(win_size), num_rows(num_rows), num_cols(num_cols){
        //initialize total board size as well, and then set up an empty board
        total_board_size = num_rows * num_cols;
        initialize_empty_board();
    }

    void check_board_is_full() {
        //check if entire board is full, where there's no EMPTY entry anywhere
        for (int i = 0; i < total_board_size; i++) {
            if (board_grid[i] == EMPTY) {
                return; //
            }
        }
        throw GameOverError("Board::check_board_is_full, board is full, can't place any more pieces");
    }

    void process_move(int row_index, int col_index) {
        //with a row_index and col_index input, place a move given the current player, then switch turns
        //omit the full board check here, allow it to be checked separately, for console ui purposes
        if (check_winner() != WINNER::NONE) {
            throw GameOverError("Board::process_move, someone already won");
        } else {
            MOVE current_move = get_current_move();
            place_row_col_move(current_move, row_index, col_index);
            change_turn();
        }
    }

    MOVE* get_board_copy() {
        //return a copy of the board, so can get access without modifying private board_grid var
        MOVE* board_copy = new MOVE[total_board_size];
        for (int i = 0; i < total_board_size; i++) {
            *(board_copy + i) = *(board_grid + i);
        }
        return board_copy;
    }

    int* get_board_layout() {
        //return an array of length 2 with items in this order:
        //1. num_rows 2. num_cols 3. total_board_size
        int* board_layout = new int[3]{num_rows, num_cols, total_board_size};
        return board_layout;
    }

    WINNER check_winner() {
        //check all possible directions for a win, and return either a winner or no winner
        WINNER winner = WINNER::NONE;
        winner = check_horizontal_winner();
        if (winner != WINNER::NONE) {
            return winner;
        }

        winner = check_vertical_winner();
        if (winner != WINNER::NONE) {
            return winner;
        }

        winner = check_right_diagonal_winner();
        if (winner != WINNER::NONE) {
            return winner;
        }

        winner = check_left_diagonal_winner();
        if (winner != WINNER::NONE) {
            return winner;
        }

        return winner;
    }
};


#endif // BOARD_H_INCLUDED
