#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

typedef struct {
    int x, y, width;
} Plate;

Plate our_plate;

typedef struct {
    int x, y;
} Our_ball;
Our_ball ball;

void initPlate() {
    our_plate.width = 7;
    our_plate.x = (65 - our_plate.width) / 2;
    our_plate.y = 24;
}

void clearPlate(char a[25][65]) {
    for (int i = our_plate.x; i < our_plate.x + 7; ++i) {
        a[our_plate.y][i] = ' ';
    }
}

void putPlate(char a[25][65]) {
    for (int i = our_plate.x; i < our_plate.x + 7; ++i) {
        a[our_plate.y][i] = '0';
    }
}

void secture(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void movePlate(int x) {
    if (x < 1) {
        our_plate.x = 1;
    }
    else if (x + 7 > 64) {
        our_plate.x = 57;
    }
    else {
        our_plate.x = x;
    }
}

void print(char a[25][65]) {
    for (int i = 0; i < 25; ++i) {
        for (int j = 0; j < 65; ++j) {
            printf("%c", a[i][j]);
        }
        printf("\n");
    }
}

void hideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void initBall() {
    ball.x = 2;
    ball.y = 2;
}
void putBall(char field[25][65]) {
    field[ball.y][ball.x] = '*';
}

void moveBall(int x, int y, char field[25][65]) {
    field[ball.y][ball.x] = ' ';
    ball.x = x;
    ball.y = y;
}
int main(void) {
    char field[25][65];

    for (int i = 0; i < 25; ++i) {
        for (int j = 0; j < 65; ++j) {
            if (i == 0) {
                field[i][j] = '_';

            }
            else if(j == 0 || j == 64){
                field[i][j] = '|';
            }
            else {
                field[i][j] = ' ';
            }
        }
    }
    initPlate();
    initBall();
    hideCursor();

    do {
        secture(0, 0);
        clearPlate(field);
        if (GetKeyState('A') < 0 || GetKeyState(VK_LEFT) < 0) movePlate(our_plate.x - 2);
        if (GetKeyState('D') < 0 || GetKeyState(VK_RIGHT) < 0) movePlate(our_plate.x + 2);
        putPlate(field);
        moveBall(our_plate.x + our_plate.width / 2, our_plate.y - 1, field);
        putBall(field);
        print(field);
    } while (1);


    return 0;
}
