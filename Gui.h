#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#include <cstdlib>
#include <iomanip>

using namespace std;

class Gui {

public: //Enums

    enum OS_TYPE {
         WINAPI32,
         UNIXBASED,
         DEFAULT_OS
    };

    enum GME_MODE {
         NONE,
         DEFAULT,
         PVP,
         PVAI_L1,
         PVAI_L2,
         PVAI_L3
    };

private: //Variables

    OS_TYPE console = OS_TYPE::DEFAULT_OS;
    GME_MODE gamemode = GME_MODE::NONE;
    int curValue;
    int startValue;
    int pvpValue;
    int exitValue;
    int difValue;

private: //Functions

    bool isNum(const std::string& s)
    {
        std::string::const_iterator it = s.begin();
        while (it != s.end() && std::isdigit(*it)) ++it;
        return !s.empty() && it == s.end();
    }

    int selNum(int minNum, int maxNum, int &saveValue, int player = 0) {
        string value;
        string turn;

        if (player == 1) { turn = " X:"; }
        else if (player == 2) { turn = " O:"; }
        else if (player == 3) { turn = " X: Try again: "; }
        else if (player == 4) { turn = " O: Try again: "; }
        else { turn = ""; }

        cout << "" << endl;
        cout << turn << " Select a number: ";
        cin >> setw(10) >> value;

        if (isNum(value)) { saveValue = stoi(value); }
        else { saveValue = 0; }
        if (saveValue < 0 || saveValue > 100) { saveValue = 0; }

        if (saveValue >= minNum && saveValue <= maxNum) {
            cout << turn << " Selected " << saveValue << endl;
            return saveValue;
        }
        else {
            cerr << " Not a valid input" << endl;
            saveValue = 0;
            return 0;
        }

    }

    void aiGui() {
        clear();
        cout << " TicTacToe v1.0" <<endl;
        cout << "" <<endl;
        cout << " SELECT DIFFICULTY" <<endl;
        cout << " 1. Easy" <<endl;
        cout << " 2. Normal" <<endl;
        cout << " 3. Hard" <<endl;
        selNum(1,3, difValue);
        if (difValue == 1) { gamemode = GME_MODE::PVAI_L1; }
        else if (difValue == 2) { gamemode = GME_MODE::PVAI_L2; }
        else if (difValue == 3) { gamemode = GME_MODE::PVAI_L3; }
        else { initGui(); }
    }

    void creditsGui() {
        clear();
        cout << " TicTacToe v1.0" <<endl;
        cout << "" <<endl;
        cout << " Made by: Nico" <<endl;
        cout << "          Alex" <<endl;
        cout << "" <<endl;
        cout << " Press any key to return: " << endl;
        pause();
        initGui();
    }

    void exitGui() {
        clear();
        cout << " Thanks for playing!" <<endl;
        cout << "" <<endl;
        cout << " EXIT?" <<endl;
        cout << " 1. Yes" <<endl;
        cout << " 2. No" <<endl;
        cout << "" <<endl;
        selNum(1, 2, exitValue);
        if (exitValue == 1) { exit(0); }
        else { initGui(); }
    }

public:

    Gui() { }

    void specifyOS(OS_TYPE console) {
        this->console = console;
    }

      void clear() {
        if (console = OS_TYPE::WINAPI32) {system("cls");}
        if (console = OS_TYPE::UNIXBASED) {system("clear");}
        else {system("clear");}
    }

    void pause() {
        if (console = OS_TYPE::WINAPI32) {system("pause");}
        if (console = OS_TYPE::UNIXBASED) {system("stty -icanon -echo; dd if=/dev/tty of=/dev/null bs=1 count=1 2>/dev/null; stty icanon echo");}
        else {system("stty -icanon -echo; dd if=/dev/tty of=/dev/null bs=1 count=1 2>/dev/null; stty icanon echo");}
    }

    bool printGui(string tPos[], int player) {
        clear();
        try {
            cout << " Welcome to TicTacToe" << endl;
            cout << "" << endl;

            for (int x = 0; x < 9;) {
                cout << "      |     |     " << endl;
                cout << "   "<<tPos[x]<<"  |  "<<tPos[x + 1]<<"  |  "<<tPos[x + 2]<< endl;
                if (x != 6) { cout << " _____|_____|_____" << endl; }
                else { cout << "      |     |     " << endl;}
                x = x + 3;
            }

            selNum(1, 9, pvpValue, player);
            return true;

        } catch(...) {
            cerr << " Something went wrong (GUI_INIT)" << endl;
        }
    }

    void initGui() {
        clear();
        cout << " Welcome to TicTacToe v1.0" <<endl;
        cout << " The most hardcore game ever!" <<endl;
        cout << "" <<endl;
        cout << " CHOOSE A GAME MODE:" <<endl;
        cout << " 1. Player vs player" <<endl;
        cout << " 2. Player vs computer" <<endl;
        cout << " 3. Game credits" <<endl;
        cout << " 4. Exit game!" <<endl;
        selNum(1, 4, startValue);
        clear();
        if (startValue == 0) { initGui(); }
        else if (startValue == 1) { gamemode = GME_MODE::PVP; }
        else if (startValue == 2) { aiGui(); }
        else if (startValue == 3) { creditsGui(); }
        else if (startValue == 4) { exitGui(); }
        else { gamemode = GME_MODE::DEFAULT; }
        return;
    }

     int playerGui(bool isAi = false) {
        clear();
        int x = 0;
        cout << " TicTacToe v1.0" <<endl;
        cout << "" <<endl;
        if (isAi) { cout << " PLAY AS:" <<endl; }
        else { cout << " WHO PLAYS FIRST:" <<endl; }
        cout << " 1. X" <<endl;
        cout << " 2. O" <<endl;
        selNum(1,2, x);
        if (x == 0) {
            cout << "Invalid input: try again.." << endl;
            playerGui(isAi);
        }
        else if (x == 1) { return 1; }
        else if (x == 2) { return 2; }
        else { return 0; }
    }

    int getCurrentGameMode() {
        return gamemode;
    }

    int getCurrnentInputValue() {
        return pvpValue;
    }

};

#endif // GUI_H_INCLUDED
