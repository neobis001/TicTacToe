#include <iostream>

using namespace std;

const char EMPTY = 'E';
const char X_PIECE = 'X';
const char O_PIECE = 'O';
const int BOARD_SIZE = 9;


class Board {
private:
    char* board_grid;

public:
    Board(char board_input[BOARD_SIZE]): board_grid(board_input) {
        cout << board_grid[0] << endl;
    }
};

Board initialize_empty_board() {
    char board_input[BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; i++) {
        board_input[i] = EMPTY;
    }
    Board new_board = Board(board_input);
    return new_board;
}

int main()
{
/*    char* speeding[3]{"speeding", "running"};
    for (int i = 0; i < 3; i++) {
        speeding[i] = "abacus";
    }
    cout << speeding[0] << endl;


    char runner[]{'a', 'b', 'c'};
    test(runner);
    cout << "Hello world!" << endl;
    */


    //int speed[4]{4,4,4};
    //char board[9] = {'a','b','c','d','e','f','g'};
    //Board b = initialize_empty_board();
    //cout << speed[2] << endl;
    return 0;
}
