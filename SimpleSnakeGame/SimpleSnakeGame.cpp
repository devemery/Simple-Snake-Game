// SimpleSnakeGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <conio.h> //console input output file
#include <ctime>
#include <Windows.h>
using namespace std;

bool gameOver;
const int width = 25;
const int height = 25;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;


void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    srand(time(NULL));
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Draw() {
    system("cls"); //clears console window
    for (int i = 0; i < width; ++i) {
        cout << "#";
    }
    cout << endl;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (j == 0) {
                cout << "#";
            }
            else if (j == width - 1) {
                cout << "#";
            }            
            else if (i == y && j == x) {
                cout << "0";
            }
            else if (i == fruitY && j == fruitX) {
                cout << "F";
            }
            else {
                bool print = false;
                for (int k = 0; k < nTail; ++k) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";
                        print = true;
                    }
                    
                }
                if (!print) {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }
    for (int i = 0; i < width; ++i) {
        cout << "#";
    }
    cout << endl;
    cout << "Score: " << score << endl;
}

void Input() {
    if (_kbhit()) { //boolean function that will return true if keyboard is pressed
        switch (_getch()) {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; ++i) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
    case LEFT:
        --x;
        break;
    case RIGHT:
        ++x;
        break;
    case UP:
        --y;
        break;
    case DOWN:
        ++y;
        break;
    default:
        break;
    }
    if (x >= width-1 || x <= 0 || y >= height || y < 0) {
        gameOver = true;
    }
    for (int i = 0; i < nTail; ++i) {
        if (tailX[i] == x && tailY[i] == y) {
            gameOver = true;
        }
    }
    if (x == fruitX && y == fruitY) {
        score+=10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        while (fruitX == 0 || fruitX == width || fruitY == 0 || fruitY == height) {
            fruitX = rand() % width;
            fruitY = rand() % height;
        }
        ++nTail;
    }

}

int main()
{
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(50); //function to slow game
    }
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
