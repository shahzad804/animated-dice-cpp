#include <iostream>
#include <windows.h>
#include <ctime>
#include <cctype>
using namespace std;

// Cursor move (NO FLICKER)
void gotoXY(int x, int y)
{
    COORD pos = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// Get center of console
void getCenter(int &cx, int &cy)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    cx = width / 2;
    cy = height / 2;
}

// ASCII Dice (Dev-C++ Safe)
void drawDice(int value, int x, int y, int color)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, color);

    string d[6][5] = {
        {"+-----+","|     |","|  o  |","|     |","+-----+"}, //1
        {"+-----+","|o    |","|     |","|    o|","+-----+"}, //2
        {"+-----+","|o    |","|  o  |","|    o|","+-----+"}, //3
        {"+-----+","|o   o|","|     |","|o   o|","+-----+"}, //4
        {"+-----+","|o   o|","|  o  |","|o   o|","+-----+"}, //5
        {"+-----+","|o   o|","|o   o|","|o   o|","+-----+"}  //6
    };

    for(int i = 0; i < 5; i++)
    {
        gotoXY(x, y + i);
        cout << d[value-1][i];
    }

    SetConsoleTextAttribute(h, 7);
}

// Smooth rolling animation
void rollAnimation(int x1, int x2, int y)
{
    for(int i = 0; i < 10; i++)
    {
        drawDice(rand()%6+1, x1, y, 10);
        drawDice(rand()%6+1, x2, y, 10);
        Sleep(60);
    }
}

int main()
{
    srand(time(0));
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    int cx, cy;
    getCenter(cx, cy);

    while(true)
    {
        system("cls"); // clear once per round

        getCenter(cx, cy);

        // Title
        SetConsoleTextAttribute(h, 11);
        gotoXY(cx - 12, cy - 6);
        cout << "==== SMOOTH DICE GAME ====";
        SetConsoleTextAttribute(h, 7);

        int x1 = cx - 12;
        int x2 = cx + 2;
        int y  = cy - 2;

        // Animation
        rollAnimation(x1, x2, y);

        // Final dice
        int d1 = rand()%6 + 1;
        int d2 = rand()%6 + 1;

        drawDice(d1, x1, y, 10);
        drawDice(d2, x2, y, 10);

        Beep(800, 120);

        // Total
        gotoXY(cx - 5, cy + 5);
        cout << "Total: " << (d1 + d2);

        // Input (NO LINE JUMP BUG)
        char choice;
        gotoXY(cx - 10, cy + 7);
        cout << "Roll again? (Y/N):   ";

        gotoXY(cx + 8, cy + 7);
        cin >> choice;
        cin.ignore(1000, '\n');

        if(toupper(choice) != 'Y')
            break;
    }

    // Exit message
    gotoXY(cx - 6, cy + 9);
    SetConsoleTextAttribute(h, 14);
    cout << "Thanks for playing!";
    SetConsoleTextAttribute(h, 7);

    Sleep(1200);
    return 0;
}

