#include <iostream>
#include <string>
#include "Board.h"
#include "Gui.h"

using namespace std;

enum WINNER_PLR {
    TIE,
    PLR_X,
    PLR_O
};

void playerMove(int player, string tPos[9], Gui gui, Board board,
                WINNER winner, WINNER_PLR &player_winner, bool retAi = false) {
    for (int i = 0; i < 9; i++) {
        ostringstream convert;
        convert << i + 1;
        tPos[i] = convert.str();
    }
    for (int i = 0; i < 9; i++) {
        int x = 0;
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
        if (x < 4) { board.process_move(0, (x-1)); }
        else if (x < 7) { board.process_move(1, (x-1) - 3); }
        else { board.process_move(2, (x-1) - 6); }
        winner = board.check_winner();
        if (winner == WINNER::X_WINNER) {
            cout << "X is the winner" << endl;
            player_winner = WINNER_PLR::PLR_X;
            break;
        } else if (winner == WINNER::O_WINNER) {
            cout << "O is the winner" << endl;
            player_winner = WINNER_PLR::PLR_O;
            break;
        } else {
            try {
                board.check_board_is_full();
            } catch (GameOverError) {
              break;
            }
        }

        if (retAi) { i = 9; }
    }
}

int main()
{

    Gui gui;
    gui.specifyOS(gui.WINAPI32);

    int input_rows = 3;
    int input_cols = 3;
    int win_size = 3;
    bool endGame = false;;
    PLAYER first_player;
    WINNER winner;
    WINNER_PLR player_winner = WINNER_PLR::TIE;
string tPos[9];

    while (!endGame) {

        gui.initGui();

        if (gui.getCurrentGameMode() == gui.PVP) {

            int player = gui.playerGui(false);

            if (player == 1) { first_player = PLAYER::X_PLAYER; }
            else if (player == 2) { first_player = PLAYER::O_PLAYER; }
            Board board(input_rows, input_cols, win_size, first_player);

            playerMove(player,tPos, gui, board, winner, player_winner);

        }

        else if (gui.getCurrentGameMode() == gui.PVAI_L1) {
            int player = gui.playerGui(true);
            int first = gui.playerGui(false);
            if (first == 1) { first_player = PLAYER::X_PLAYER; }
            else if (first == 2) { first_player = PLAYER::O_PLAYER; }
            Board board(input_rows, input_cols, win_size, first_player);

            while (true) {
            if (player == first) {
                playerMove(player,tPos, gui, board, winner, player_winner, true);
                if (player == 1) { player = 2; }
                else if (player == 2) { player = 1; }
            } else {
                tPos[5] = "X";
                if (player == 1) { player = 2; }
                else if (player == 2) { player = 1; }
            } }


        }

        gui.clear();
        cout << "" << endl;
        cout << " Thanks for playing!" << endl;
        if (player_winner == PLR_X) { cout << "     X has won!" << endl; }
        if (player_winner == PLR_O) { cout << "     O has won!" << endl; }
        if (player_winner == TIE) { cout << "     It's a tie!" << endl; }
        cout << "" << endl;
        cout << " Press any key to continue.." << endl;
        gui.pause();

    }
}
