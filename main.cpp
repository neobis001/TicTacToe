#include <iostream>
#include <string>
#include "Board.h"
#include "Gui.h"

using namespace std;

int main() ///DEMO EXAMPLE!
{
    //Array with values to apear
    string tPos[9];
    for (int i = 0; i < 9; i++) {
        tPos[i] = to_string(i + 1);
    }

    Gui gui; //Creating gui
    gui.specifyOS(gui.WINAPI32); //Specify platform (Current Windows)
    gui.initGui(); //Clears the screen and start gui menu with pvp, pve, credits, exit options

    //When selected either 1.PVP or 2.PVE and the player enters game you can get the gamemode:
    if (gui.getCurrentGameMode() == gui.NONE) { cerr << "Gamemode error (GMD_ERR)"<<endl; }          //None if gui.initGui(); function never runs or runs after the request of gamemode line
    if (gui.getCurrentGameMode() == gui.DEFAULT) { return 1; /*Maybe here gui.printGui(tPos) too*/}  //Default state, if other than the requested number is entered
    if (gui.getCurrentGameMode() == gui.PVP) { gui.printGui(tPos); gui.getCurrnentInputValue();}     //PVP if the option 1 from the start menu is selected
    if (gui.getCurrentGameMode() == gui.PVAI_L1) { /*Call ai function ai(1);*/ }                     //Ai level 1: if the option 2 from the start menu is selected and then difficulty Easy
    if (gui.getCurrentGameMode() == gui.PVAI_L2) { /*Call ai function ai(2);*/ }                     //Ai level 2: if the option 2 from the start menu is selected and then difficulty Normal
    if (gui.getCurrentGameMode() == gui.PVAI_L3) { /*Call ai function ai(3);*/ }                     //Ai level 3: if the option 2 from the start menu is selected and then difficulty Hard

    ///NOTES
    // In the if statement you can display a text or the gui.printGui(tPos); that will print the tictactoe gui with the tPos string array as values and then it will ask for input.
    // The logic is that you will print the gui with gui.printGui(tPos); and get the input value with gui.getCurrnentInputValue(); update the tPos string array and repeat. Mabe call a function that does that
    // If not added the if statements, when choosing an option the game will exit and close(Nothing to do). If initGui() apears below again you have to manage the input cases again.
    // If not valid input value the getCurrnentInputValue() will be zero, and the message "Not valid input" will apear on the screen

    return 0;

}

