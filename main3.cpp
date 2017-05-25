#include <iostream>
#include <string>
#include "Board.h"
#include "Gui.h"

using namespace std;

int main() ///DEMO EXAMPLE!
{

    string tPos[9]{"0","1","2","3","4","5","6","7","8"}; //Array of displayed positions
    /*for (int i = 0; i < 9; i++) {
        tPos[i] = to_string(i + 1);
    }*/

    //Create gui and specify os
    Gui gui;
    gui.specifyOS(gui.WINAPI32);

    while (true) { //Start while loop game

        gui.initGui(); //Init gui, display start menu with pvp, pve, credits and exit comp.
        if (gui.getCurrentGameMode() == gui.PVP) { //If first gamemode selected other oprions gui.PVAI_L1, gui.PVAI_L2, gui.PVAI_L3

            int x = 0; //Variable that will get the player input
            int player = gui.playerGui(false); //Display player screen (Change false to true only on pve)
            for (int i = 0; i < 9; i++) { //9 times eatch tictactoe game

                if (player == 1) { gui.printGui(tPos, 1); } //If player X plays first he shall do his move
                else if (player == 2) { gui.printGui(tPos, 2); } //Else the O should start first

                x = gui.getCurrnentInputValue(); //Get input value //TODO: Update the tictactoe table by changing tPos[] values

                while (x < 1 || x > 9 ) { //If out of bounds loop until entered valid value
                    if (player == 1) { gui.printGui(tPos, 3); } // The 3 is for asking X to reenter a value
                    else if (player == 2) { gui.printGui(tPos, 4); } //The 4 is for asking O to reenter a value
                    x = gui.getCurrnentInputValue(); //Check if correct, else loop  //TODO: Check if selected already occupied position
                }

                if (player == 1) { player = 2; } //Change players order
                else if (player == 2) { player = 1; } //The same is true if O is first

            }// After 9 moves someone won! //TODO: match 3 if in a row..

            gui.clear(); //Clear the screen
            //Display the following message
            cout << "" << endl;
            cout << " Thanks for playing!" << endl;
            cout << "     X has won!" << endl;
            cout << "" << endl;
            cout << " Press any key to continue.." << endl;
            gui.pause(); //Pause until player presses a key

        } //After pressing a key the loop will start over again and reinitialise the GUI
    }

}

