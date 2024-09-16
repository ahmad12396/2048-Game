#include<iostream>
#include<fstream>
#include<ctime>
#include<Windows.h>
#include<conio.h>
#include<cstdlib>

using namespace std;

#define Black         0
#define Blue          1
#define Green         2
#define Cyan          3
#define Red           4
#define Magenta       5
#define Brown         6
#define LightGray     7
#define DarkGray      8
#define LightBlue     9
#define LightGreen   10
#define LightCyan    11
#define LightRed     12
#define LightMagenta 13
#define Yellow       14
#define White        15

#define sr           10
#define sc           10

// Built in Functions To Find Rows And Columns Of Console Screen and also give them colors
void gotoRowCol(int rpos, int cpos)
{
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = cpos;
    scrn.Y = rpos;
    SetConsoleCursorPosition(hOuput, scrn);
}
void SetClr(int clr)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
}


void print_square(int Sr, int Sc, int height, int width, int clr)
{
    SetClr(clr);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
            {
                gotoRowCol(i + Sr, j + Sc);
                cout << char(-37);
                                  
            }                     

        }

        cout << endl;
    }

    SetClr(White);

}

void startGame(int** arr, int size) {
    int row = rand() % size;
    int cols = rand() % size;

    arr[row][cols] = 2;
    while (arr[row][cols] != 0)
    {
        row = rand() % size;
        cols = rand() % size;
    }

    arr[row][cols] = 2;
}

void randomNumber(int** arr, int size) {
    // ri is for rows index
    // ci is for column index
    int ri, ci;

    ri = rand() % size;
    ci = rand() % size;
    while (arr[ri][ci] != 0)
    {
        ri = rand() % size;
        ci = rand() % size;
        if (arr[ri][ci] == 0)
        {
            arr[ri][ci] = 2;
            return;
        }
    }

    arr[ri][ci] = 2;
}

void LeftMove(int** arr, int size) {
  
    int** new_arr = new int* [size];
    for (int i = 0; i < size; i++)
    {
        new_arr[i] = new int[size] {};
    }
    // Compressing
    for (int i = 0; i < size; i++)
    {
        int pos = 0;
        for (int j = 0; j < size; j++)
        {
            if (arr[i][j] != 0)
            {
                new_arr[i][pos] = arr[i][j];
                pos++;
            }

        }

    }
    
    // Merging
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (new_arr[i][j] == new_arr[i][j + 1] && new_arr[i][j] != 0)
            {
                new_arr[i][j] = new_arr[i][j] * 2;
                new_arr[i][j + 1] = 0;
            }

        }

    }

    //

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            arr[i][j] = 0;
        }
    }



    // Again Compressing to Complete Move
    for (int i = 0; i < size; i++)
    {
        int pos = 0;
        for (int j = 0; j < size; j++)
        {
            if (new_arr[i][j] != 0)
            {
                arr[i][pos] = new_arr[i][j];
                pos++;
            }

        }

    }

}

void RightMove(int** arr, int size) {
    // Compressing
    int** new_arr = new int* [size];
    for (int i = 0; i < size; i++)
    {
        new_arr[i] = new int[size] {};
    }

    for (int i = 0; i < size; i++)
    {
        int pos = size - 1;
        for (int j = size - 1; j >= 0; j--)
        {
            if (arr[i][j] != 0)
            {
                new_arr[i][pos] = arr[i][j];
                pos--;
            }

        }

    }

    // Merging
    for (int i = 0; i < size; i++)
    {
        for (int j = size - 1; j >= 0; j--)
        {
            if (new_arr[i][j] == new_arr[i][j - 1] && new_arr[i][j] != 0)
            {
                new_arr[i][j] = new_arr[i][j] * 2;
                new_arr[i][j - 1] = 0;
            }

        }

    }

    // copying values into the original array from the new array 

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            arr[i][j] = 0;
        }
    }



    // Again Compressing to Complete Move
    for (int i = 0; i < size; i++)
    {
        int pos = size - 1;
        for (int j = size - 1; j >= 0; j--)
        {
            if (new_arr[i][j] != 0)
            {
                arr[i][pos] = new_arr[i][j];
                pos--;
            }

        }

    }

}

void UpMove(int** arr, int size) {
    // Compressing
    int** new_arr = new int* [size];
    for (int i = 0; i < size; i++)
    {
        new_arr[i] = new int[size] {};
    }

    for (int i = 0; i < size; i++)
    {
        int pos = 0;
        for (int j = 0; j < size; j++)
        {
            if (arr[j][i] != 0)
            {
                new_arr[pos][i] = arr[j][i];
                pos++;
            }

        }

    }

    // Merging
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - 1; j++)
        {
            if (new_arr[j][i] == new_arr[j + 1][i] && new_arr[j][i] != 0)
            {
                new_arr[j][i] = new_arr[j][i] * 2;
                new_arr[j + 1][i] = 0;
            }

        }

    }


    // copying values into the original array from the new array 

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            arr[i][j] = 0;
        }
    }



    // Again Compressing to Complete Move
    for (int i = 0; i < size; i++)
    {
        int pos = 0;
        for (int j = 0; j < size; j++)
        {
            if (new_arr[j][i] != 0)
            {
                arr[pos][i] = new_arr[j][i];
                pos++;
            }

        }

    }

}

void DownMove(int** arr, int size) {
    // Compressing
    int** new_arr = new int* [size];
    for (int i = 0; i < size; i++)
    {
        new_arr[i] = new int[size] {};
    }

    for (int i = 0; i < size; i++)
    {
        int pos = size - 1;
        for (int j = size - 1; j >= 0; j--)
        {
            if (arr[j][i] != 0)
            {
                new_arr[pos][i] = arr[j][i];
                pos--;
            }

        }

    }

    // Merging
    for (int i = 0; i < size; i++)
    {
        for (int j = size - 1; j > 0; j--)
        {
            if (new_arr[j][i] == new_arr[j - 1][i] && new_arr[j][i] != 0)
            {
                new_arr[j][i] = new_arr[j][i] * 2;
                new_arr[j - 1][i] = 0;
            }

        }

    }


    // copying values into the original array from the new array 

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            arr[i][j] = 0;
        }
    }


    // Again Compressing to Complete Move
    for (int i = 0; i < size; i++)
    {
        int pos = size - 1;
        for (int j = size - 1; j >= 0; j--)
        {
            if (new_arr[j][i] != 0)
            {
                arr[pos][i] = new_arr[j][i];
                pos--;
            }

        }

    }

}

bool winning_condition(int** arr, int size) {
    // Anywhere 2048 is Present
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (arr[i][j] == 2048)
            {
                return true;
            }
        }
    }

    return false;
}

bool success_move(int** arr, int** store, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (arr[i][j] != store[i][j])
            {
                return true;
            }
        }
    }

    return false;
}

void printBoard(int** arr, int size, int height, int width)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (arr[i][j] == 2)
            {
                print_square(sr + (i * height), sc + (width * j), height, width, DarkGray);
                gotoRowCol(sr + (i * height) + (height / 2), sc + (width * j) + (width / 2) - 1);
                cout << arr[i][j];
            }
            else if (arr[i][j] == 4)
            {
                print_square(sr + (i * height), sc + (width * j), height, width, LightGreen);
                gotoRowCol(sr + (i * height) + (height / 2), sc + (width * j) + (width / 2) - 1);
                cout << arr[i][j];
            }
            else if (arr[i][j] == 8)
            {
                print_square(sr + (i * height), sc + (width * j), height, width, Brown);
                gotoRowCol(sr + (i * height) + (height / 2), sc + (width * j) + (width / 2) - 1);
                cout << arr[i][j];
            }
            else if (arr[i][j] == 16)
            {
                print_square(sr + (i * height), sc + (width * j), height, width, LightRed);
                gotoRowCol(sr + (i * height) + (height / 2), sc + (width * j) + (width / 2) - 1);
                cout << arr[i][j];
            }
            else if (arr[i][j] == 32)
            {
                print_square(sr + (i * height), sc + (width * j), height, width, Red);
                gotoRowCol(sr + (i * height) + (height / 2), sc + (width * j) + (width / 2) - 1);
                cout << arr[i][j];
            }
            else if (arr[i][j] == 64)
            {
                print_square(sr + (i * height), sc + (width * j), height, width, Red);
                gotoRowCol(sr + (i * height) + (height / 2), sc + (width * j) + (width / 2) - 1);
                cout << arr[i][j];
            }
            else if (arr[i][j] == 128)
            {
                print_square(sr + (i * height), sc + (width * j), height, width, LightBlue);
                gotoRowCol(sr + (i * height) + (height / 2), sc + (width * j) + (width / 2) - 1);
                cout << arr[i][j];
            }
            else if (arr[i][j] == 256)
            {
                print_square(sr + (i * height), sc + (width * j), height, width, LightCyan);
                gotoRowCol(sr + (i * height) + (height / 2), sc + (width * j) + (width / 2) - 1);
                cout << arr[i][j];
            }
            else if (arr[i][j] == 512)
            {
                print_square(sr + (i * height), sc + (width * j), height, width, LightRed);
                gotoRowCol(sr + (i * height) + (height / 2), sc + (width * j) + (width / 2) - 1);
                cout << arr[i][j];
            }
            else if (arr[i][j] == 1024)
            {
                print_square(sr + (i * height), sc + (width * j), height, width, Blue);
                gotoRowCol(sr + (i * height) + (height / 2), sc + (width * j) + (width / 2) - 1);
                cout << arr[i][j];
            }
            else if (arr[i][j] == 2048)
            {
                print_square(sr + (i * height), sc + (width * j), height, width, Green);
                gotoRowCol(sr + (i * height) + (height / 2), sc + (width * j) + (width / 2) - 1);
                cout << arr[i][j];
            }
            else
            {
                print_square(sr + (i * height), sc + (width * j), height, width, Yellow);
            }
        }
    }

    //undo_button();
    gotoRowCol(20, 90);
    cout << "Press (U/u) For Undo Move ";
    //reset_button(); 
    gotoRowCol(30, 90);
    cout << "Press (R/r) For Reset Board ";
    //Exit Game
    gotoRowCol(40, 90);
    cout << "Press Esc For Exit Game ";
}

bool loosing_condition(int** arr, int size)
{
    // Anywhere 0 is Present
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (arr[i][j] == 0)
            {
                return false;
            }

        }

    }

    // Check Every Row and Column Except Last Row, Column
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - 1; j++)
        {
            if (arr[i][j] == arr[i + 1][j] || arr[i][j] == arr[i][j + 1])
            {
                return false;
            }

        }

    }

    // Last Row
    for (int j = 0; j < size - 1; j++)
    {
        if (arr[size - 1][j] == arr[size - 1][j + 1])
        {
            return false;
        }

    }

    // // Last Column
    for (int i = 0; i < size - 1; i++)
    {
        if (arr[i][size - 1] == arr[i + 1][size - 1])
        {
            return false;
        }

    }
    return true;
}

void size_legality(int& size, int& height, int& width)
{
    gotoRowCol(10, 10);
    cout << "Enter the Size of Board (3-8)" << endl;
    cin >> size;
    while (size < 3 || size>8)
    {
        system("cls");
        gotoRowCol(10, 10);
        cout << "Enter the correct Size of Board(3-8) " << endl;
        cin >> size;
    }

    if (size == 3)
    {
        height = 15;
        width = 15;
    }
    else if (size == 4)
    {
        height = 14;
        width = 14;
    }
    else if (size == 5)
    {
        height = 13;
        width = 13;
    }
    else if (size == 6)
    {
        height = 12;
        width = 12;
    }
    else if (size == 7)
    {
        height = 10;
        width = 10;
    }
    else if (size == 8)
    {
        height = 9;
        width = 9;
    }
    system("cls");
}

void undo_move(int**& copy, int**& arr, int size, int height, int width)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            arr[i][j] = copy[i][j];
        }
    }

    system("cls");
    printBoard(arr, size, height, width);
}

void reset_move(int** arr, int size, int height, int width)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            arr[i][j] = 0;
        }
    }
    startGame(arr, size);
    system("cls");
    printBoard(arr, size, height, width);

}

int calculateScore(int** arr, int size) {
    int score = 0;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            // Add the value of each tile to the score
            score += arr[i][j];
        }
    }

    return score;
}

int main() {
    fstream out;
    out.open("HighScore.txt", ios::in | ios::out);

    gotoRowCol(10, 15);
    cout << "2048 GAME";
    gotoRowCol(15, 10);
    cout << "Press any key to continue";
    _getch();
    system("cls");
    int size = 0;
    int height = 0;
    int width = 0;
    int score = 0;
    int highscore = 0;
    int data;

    // Read high score only once
    if (out >> data)
    {
        highscore = data;
    }

    size_legality(size, height, width);

    int** arr = new int* [size];
    for (int i = 0; i < size; i++)
    {
        arr[i] = new int[size] {};
    }

    srand(time(0));

    startGame(arr, size);

    printBoard(arr, size, height, width);

    // Making Array For Undo Function
    int** copy = new int* [size];
    for (int i = 0; i < size; i++)
    {
        copy[i] = new int[size] {};
    }

    int key;
    while (true) {
        key = _getch();  // Use getch() for user input in console

        int** store = new int* [size];
        for (int i = 0; i < size; i++)
        {
            store[i] = new int[size] {};
        }

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                store[i][j] = arr[i][j];
            }
        }


        switch (key) {
        case 75:
            LeftMove(arr, size);
            break;
        case 77:
            RightMove(arr, size);
            break;
        case 72:
            UpMove(arr, size);
            break;
        case 80:
            DownMove(arr, size);
            break;

        case 27:  // ASCII code for Esc key
            system("cls");
            gotoRowCol(10, 10);
            cout << "Exiting the game.";
            Sleep(3000);
            return 0;
        case 117:
            undo_move(copy, arr, size, height, width);
            break;

        case 85:
            undo_move(copy, arr, size, height, width);
            break;

        case 114:
            gotoRowCol(50, 90);
            cout << "Are You sure You want to Reset the game(Y/N)";
            key = _getch();
            if (key == 121 || key == 89)
            {
                system("cls");
                gotoRowCol(10, 10);
                cout << "Resetting the game.";
                Sleep(3000);
                reset_move(arr, size, height, width);
            }
            else if (key == 110 || key == 78)
            {
                system("cls");
                gotoRowCol(10, 10);
                cout << "Continuing the game.";
                Sleep(3000);
                printBoard(arr, size, height, width);
            }
            else
            {
                gotoRowCol(55, 90);
                cout << "Invalid Command!";
                printBoard(arr, size, height, width);
            }
            break;

        case 82:
            gotoRowCol(50, 90);
            cout << "Are You sure You want to Reset the game(Y/N)";
            key = _getch();
            if (key == 121 || key == 89)
            {
                system("cls");
                gotoRowCol(10, 10);
                cout << "Resetting the game.";
                Sleep(3000);
                reset_move(arr, size, height, width);
            }
            else if (key == 110 || key == 78)
            {
                system("cls");
                gotoRowCol(10, 10);
                cout << "Continuing the game.";
                Sleep(3000);
                printBoard(arr, size, height, width);
            }
            else
            {
                gotoRowCol(55, 90);
                cout << "Invalid Command!";
                printBoard(arr, size, height, width);
            }
            break;
        }


        if ((key == 72 || key == 75 || key == 77 || key == 80 || key == 117 || key == 85) && success_move(arr, store, size))
        {

            if ((key == 72 || key == 75 || key == 77 || key == 80) && success_move(arr, store, size))
            {
                randomNumber(arr, size);
                system("cls");
            }

            if (winning_condition(arr, size))
            {
                system("cls");
                printBoard(arr, size, height, width);
                gotoRowCol(50, 90);
                cout << "CONGRATULATIONS! YOU WON!";
                _getch();
                break;
            }

            printBoard(arr, size, height, width);
            score = calculateScore(arr, size);
            gotoRowCol(8, 10);
            cout << "Current Score: " << score;
            if (score > highscore)
            {
                highscore = score;
                out.seekp(0, ios::beg);
                out << highscore << endl;
            }
            gotoRowCol(8, 55);
            cout << "High Score: " << highscore;

        }
        else
        {
            // Undo Move Function
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    copy[i][j] = arr[i][j];
                }
            }
        }

        if (loosing_condition(arr, size))
        {
            gotoRowCol(50, 90);
            cout << "GAME OVER!";
            gotoRowCol(80, 0);
            _getch();
            break;
        }

    }
    out.close();
    // Deleting array because they can't delete automatically
    for (int i = 0; i < size; i++) {
        delete[] arr[i];
        delete[] copy[i];
    }
    delete[] arr;
    delete[] copy;

    return 0;
}