#include <iostream>
#include <string>
#include "Board.h"
#include "Gui.h"

using namespace std;


int main()
{
    enum WINNER_PLR {
        TIE,
        PLR_X,
        PLR_O
    };

    string tPos[9];
    Gui gui;
    gui.specifyOS(gui.WINAPI32);

    int input_rows = 3;
    int input_cols = 3;
    int win_size = 3;
    bool endGame = false;
    PLAYER first_player;

    WINNER winner;
    WINNER_PLR player = WINNER_PLR::TIE;

    while (true) {

        gui.initGui();
        if (gui.getCurrentGameMode() == gui.PVP) {
            int x = 0;
            int player = gui.playerGui(false);
            for (int i = 0; i < 9; i++) {
                tPos[i] = to_string(i + 1);
            }

            if (player == 1) { first_player = PLAYER::X_PLAYER; }
            if (player == 2) { first_player = PLAYER::O_PLAYER; }
            Board board(input_rows, input_cols, win_size, first_player);
            for (int i = 0; i < 9; i++) {

                if (player == 1) { gui.printGui(tPos, 1); }
                else if (player == 2) { gui.printGui(tPos, 2); }
                x = gui.getCurrnentInputValue();

                while (x < 1 || x > 9 || tPos[x - 1] == "X" || tPos[x - 1] == "O") {
                    if (player == 1) { gui.printGui(tPos, 3); }
                    else if (player == 2) { gui.printGui(tPos, 4); }
                    x = gui.getCurrnentInputValue();
                }

                if (player == 1) { tPos[x - 1] = "X"; player = 2; }
                else if (player == 2) { tPos[x - 1] = "O"; player = 1; }

                if (x < 4) { board.process_move(1, x); }
                else if (x < 7) { board.process_move(2, x - 3); }
                else { board.process_move(3, x - 6); }

                winner = board.check_winner();
                switch (winner) {
                    case WINNER::X_WINNER:
                        endGame = true;
                        player = WINNER_PLR::PLR_X;
                        break;
                    case WINNER::O_WINNER:
                        endGame = true;
                        player = WINNER_PLR::PLR_O;
                        break;
                    case WINNER::NONE:
                        break;
                }

                if (endGame) {
                    i = 9;
                    endGame = false;
                }

            }

            gui.clear();
            cout << "" << endl;
            cout << " Thanks for playing!" << endl;
            if (player == PLR_X) { cout << "     X has won!" << endl; }
            if (player == PLR_O) { cout << "     O has won!" << endl; }
            if (player == TIE) { cout << "     It's a tie!" << endl; }
            cout << "" << endl;
            cout << " Press any key to continue.." << endl;
            gui.pause();


        }
    }
}
