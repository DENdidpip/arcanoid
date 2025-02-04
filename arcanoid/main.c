#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include <math.h>
#include <stdbool.h>

typedef struct {
    int x, y, width;
} Plate;

Plate our_plate;

typedef struct {
    float x, y;
    int ix, iy;
    float speed, angle;
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
    ball.x = our_plate.x + our_plate.width / 2;
    ball.y = our_plate.y - 1;
    ball.ix = (int)round(ball.x);
    ball.iy = (int)round(ball.y);
    ball.angle = -1;
    ball.speed = 0.5;
}

void clearBall(char field[25][65]) {
    field[ball.iy][ball.ix] = ' ';
}

void putBall(char field[25][65]) {
    field[ball.iy][ball.ix] = '*';
}

void moveBall(bool ide, int x, int y, char field[25][65]) {
    clearBall(field);
    if (ide == true) {
        ball.x = x;
        ball.y = y;
    }
    else {
        ball.x = our_plate.x + our_plate.width / 2;
        ball.y = our_plate.y - 1;
    }

    ball.ix = (int)round(ball.x);
    ball.iy = (int)round(ball.y);
}
void ball_move(char field[25][65]) {
    moveBall(true, ball.x + cos(ball.angle) * ball.speed, ball.y + sin(ball.angle)* ball.speed, field);
}

int main(void) {
    char field[25][65];

    for (int i = 0; i < 25; ++i) {
        for (int j = 0; j < 65; ++j) {
            if (i == 0) {
                field[i][j] = '_';
            }
            else if (j == 0 || j == 64) {
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
        moveBall(false, 0,0,field);
        putPlate(field);
        putBall(field);
        print(field);
    } while (1);

    return 0;
}

