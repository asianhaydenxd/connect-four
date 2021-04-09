#include <iostream>
#include <limits>
#include <windows.h>
using namespace std;

const int width = 7;
const int height = 6;

char board[width][height];

bool turnr = true;

void setColor(int color = 0x07) {
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), color);
}

void load(string msg = "Connect Four") {
    setColor();
    
    for (int i = 0; i < 50; i++) {
        cout << "\n";
    }

    cout << " " << msg << "\n\n";

    for (int i = 1; i <= width; i++) {
        cout << " " << i;
    }
    cout << "\n";

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
                cout << "|";
                if (board[x][y] == ' ') {
                    cout << " ";
                }
                else {
                    if (board[x][y] == 'r') {
                        setColor(0x0C);
                    }
                    else if (board[x][y] == 'y') {
                        setColor(0x0E);
                    }
                    cout << "O";
                    setColor();
                }
                
        }
        cout << "|\n";
    }
    cout << "\n";
}

int main() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            board[x][y] = ' ';
        }
    }

    load();

    while (true) {
        int input;

        cout << "Enter coords (";
        if (turnr) {
            setColor(0x0C);
        } 
        else {
            setColor(0x0E);
        }
        cout << "O";
        setColor();
        cout << "): ";
        cin >> input;

        if (input < 1 || input > width) {
            load("Out of bounds"); continue;
        }

        bool colFilled = true;
        int availableHeight;
        for (int i = 0; i < height; i++) {
            if (board[input-1][i] == ' ') {
                colFilled = false;
                availableHeight = i;
            }
        }
        if (colFilled) {
            load("Column unavailable");
            continue;
        }
        
        char turnchar;
        if (turnr) {
            turnchar = 'r';
        }
        else {
            turnchar = 'y';
        }
        
        board[input-1][availableHeight] = turnchar;

        char winner = ' ';
        
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                if (board[x][y] == ' ') {
                    continue;
                }

                if (x + 3 < width) { // Looks right
                    if (board[x][y] == board[x+1][y] && board[x+1][y] == board[x+2][y] && board[x+2][y] == board[x+3][y]) {
                        winner = turnchar;
                    }
                }
                if (y - 3 >= 0) { // Looks up
                    if (board[x][y] == board[x][y-1] && board[x][y-1] == board[x][y-2] && board[x][y-2] == board[x][y-3]) { // Looks straight up
                        winner = turnchar;
                    }
                    if (x + 3 < width) { // Looks up and right
                        if (board[x][y] == board[x+1][y-1] && board[x+1][y-1] == board[x+2][y-2] && board[x+2][y-2] == board[x+3][y-3]) {
                            winner = turnchar;
                        }
                    }
                    if (x - 3 >= 0) { // Looks up and left
                        if (board[x][y] == board[x-1][y-1] && board[x-1][y-1] == board[x-2][y-2] && board[x-2][y-2] == board[x-3][y-3]) {
                            winner = turnchar;
                        }
                    }
                }
            }
        }

        if (winner == 'r') {
            load("Red Wins");
            break;
        }
        else if (winner == 'y') {
            load("Yellow Wins");
            break;
        }
        else {
            bool blankExists = false;
            for (int x = 0; x < width; x++) {
                for (int y = 0; y < height; y++) {
                    if (board[x][y] == ' ') {
                        blankExists = true;
                        break;
                    }
                }
            }
            if (!blankExists) {
                load("Draw");
                break;
            }
        }
        
        load();
        turnr = !turnr;
    }

    return 0;
}