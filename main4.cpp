#include <iostream>
#include <string>
#include "Board.h"
#include "Gui.h"

using namespace std;

int main()
{

    string win;
    string tPos[9];

    Gui gui;
    gui.specifyOS(gui.WINAPI32);

    while (true) {

        gui.initGui();
        win = "";
        int x = 0;
        if (gui.getCurrentGameMode() == gui.PVP) {
            int player = gui.playerGui(false);
            for (int i = 0; i < 9; i++) {
                tPos[i] = to_string(i + 1);
            }
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

                for (int k = 0; k < 10;) {
                    if (tPos[k] == tPos[k + 1] && tPos[k + 1] == tPos[k + 2]) { win = tPos[k]; i = 9; } k = k + 3; }
                for (int k = 0; k < 10; k++) {
                    if (tPos[k] == tPos[k + 3] && tPos[k + 3] == tPos[k + 6]) { win = tPos[k]; i = 9; } }
                if (tPos[0] == tPos[4] && tPos[4] == tPos[8]) { win = tPos[4]; i = 9; }
                else if (tPos[2] == tPos[4] && tPos[4] == tPos[6]) { win = tPos[4]; i = 9; }

            }
        }

        else if (gui.getCurrentGameMode() == gui.PVAI_L1) {
            int player = gui.playerGui(true);
            int playsFirst = gui.playerGui(false);
            for (int i = 0; i < 9; i++) {
                tPos[i] = to_string(i + 1);
            }
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

                for (int k = 0; k < 10;) {
                    if (tPos[k] == tPos[k + 1] && tPos[k + 1] == tPos[k + 2]) { win = tPos[k]; i = 9; } k = k + 3; }
                for (int k = 0; k < 10; k++) {
                    if (tPos[k] == tPos[k + 3] && tPos[k + 3] == tPos[k + 6]) { win = tPos[k]; i = 9; } }
                if (tPos[0] == tPos[4] && tPos[4] == tPos[8]) { win = tPos[4]; i = 9; }
                else if (tPos[2] == tPos[4] && tPos[4] == tPos[6]) { win = tPos[4]; i = 9; }

            }
        }

        gui.clear();
        cout << "" << endl;
        cout << " Thanks for playing!" << endl;
        if (win == "X") { cout << "     X has won!" << endl; }
        else if (win == "O") { cout << "     O has won!" << endl; }
        else { cout << "     It's a tie!" << endl; }
        cout << "" << endl;
        cout << " Press any key to continue.." << endl;
        gui.pause();

    }
}
