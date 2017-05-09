#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

using namespace std;

class Gui {

private:

    enum OS_TYPE {
         WINAPI32,
         UNIXBASED,
         DEFAULT
    };

    OS_TYPE console;
    int curValue;
    int startValue;
    int pvpValue;
    int exitValue;

private:

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

    void tempPose() { //FOR LATER USE (Linux comp.)
        cin.ignore().get();  //TODO: Remove it!
    }

    void exsit() {
        if (console = OS_TYPE::WINAPI32) {system("exit");}
        if (console = OS_TYPE::UNIXBASED) {cin.ignore().get();}
        else {cin.ignore().get();}
    }

    bool isNum(const std::string& s)
    {
        std::string::const_iterator it = s.begin();
        while (it != s.end() && std::isdigit(*it)) ++it;
        return !s.empty() && it == s.end();
    }

    int selNum(int minNum, int maxNum, int &saveValue) {
        string value;
        cout << "" << endl;
        cout << " Select a number: ";
        cin  >> value;

        if (isNum(value)) { saveValue = stoi(value); }
        else { saveValue = 0; }
        if (saveValue >= minNum && saveValue <= maxNum) {
            cout << " Selected " << saveValue << endl;
            return saveValue;
        }
        else {
            cerr << " Not a valid input" << endl;
            saveValue = 0;
            return 0;
        }
    }

public:

    Gui() { }

    void specifyOS(OS_TYPE console) {
        this->console = console;
    }

    bool printGui(string tPos[]) {
        clear();
        try {
            cout << " Welcome to TicTacToe" << endl;
            cout << "" << endl;

            for (int x = 0; x < 9;) {
                cout << "      |     |     " << endl;
                cout << "   "<<tPos[x]<<"  |  "<<tPos[x + 1]<<"  |  "<<tPos[x + 2]<< endl;
                if (x != 6) { cout << " _____|_____|_____" << endl; }
                else { cout << "      |     |     " << endl;}
                x = x+3;
            }

            selNum(1, 9, pvpValue);
            return true;

        } catch(...) {
            cerr << " Something went wrong (GUI_INIT)" << endl;
        }
    }

    int initGui() {
        clear();
        cout << " Welcome to TicTacToe v1.0" <<endl;
        cout << " The most hardcore game ever!" <<endl;
        cout << "" <<endl;
        cout << " CHOOSE A GAME MODE:" <<endl;
        cout << " 1. Player vs player" <<endl;
        cout << " 2. Player vs computer" <<endl;
        cout << " 3. Game credits" <<endl;
        cout << " 4. Exit game!" <<endl;
        selNum(1,4, startValue);
        clear();
        if (startValue == 0) { initGui(); }
        else if (startValue == 1) { return 1; }
        else if (startValue == 2) { return 2; }
        else if (startValue == 3) { creditsGui(); }
        else if (startValue == 4) { exitGui(); }
        return 0;
    }

    void aiGui() {
        initGui();
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
        selNum(1,2, exitValue);
        if (exitValue == 1) { return; }
        else { initGui(); }
    }

};

#endif // GUI_H_INCLUDED
