#include <iostream>

using namespace std;

const char EMPTY = 'E';
const char X_PIECE = 'X';
const char O_PIECE = 'O';
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

class Board {
private:
    char* board_grid;
    int board_size;
public:
    Board(char* board_input, int input_size): board_grid(board_input), board_size(input_size) {
        cout << board_grid[0] << endl;
    }

    void place_move(char move_input, int board_index) {
        if (board_index < 0 || board_index >= board_size) {
            throw InvalidMoveError("Board::place_move, the board index is out of range");
        } else if (*(board_grid + board_index) != EMPTY) {
            throw InvalidMoveError("Board::place_move, the board index already has a move placed in it");
        } else if (move_input != X_PIECE || move_input != O_PIECE) {
            throw InvalidMoveError("Board::place_move, invalid move input");
        } else {
            *(board_grid + board_index) = move_input;
        }
    };

    bool check_winner() {

    }
};

Board initialize_empty_board() {
    //initialize an array input of EMPTY entries and create a Board object with that input
    char board_input[BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; i++) {
        board_input[i] = EMPTY;
    }
    Board new_board = Board(board_input, BOARD_SIZE);
    return new_board;
}

enum {
    astronaut,
    bollywood,
};

int main()
{
    cout << "astronaut value is " << astronaut << endl;
    Board board = initialize_empty_board();
    try {
        board.place_move('sentinel', 2);
    } catch (InvalidMoveError e) {
        cout << "InvalidMoveError: " << e.get_error() << endl;
    }

    return 0;
}
