#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include<conio.h>
#include "gameUtils.h"
#include "controller.h"
#include "kitu.h"

void displayBoard(Square board[BOARD_SIZE][BOARD_SIZE])
{
    char a = 65;
    int b = 0;
    printf("    ");
    printf("\033[38;5;40m ");
    for(int i = 0; i < BOARD_SIZE; i++) {
        printf("%c    ", a);
        a++;
    }
    printf("\033[0m\n");

    for(int i = 0; i < BOARD_SIZE; i++) {
        printf("\033[38;5;40m");
        printf(" %d ", b);
        b++;
        printf("\033[0m\ ");
        for(int j = 0; j < BOARD_SIZE; j++) {
            printf("[");
            printf("\033[38;5;%dm%c\033[0m",getColorCode(board[i][j].status), board[i][j].status);
            printf("]  ");
        }
        printf("\n");
    }
}

int getColorCode(char status)
{
    switch(status) {
    case 'A':
        return 160;
    case 'B':
        return 220;
    case 'C':
        return 205;
    case 'S':
        return 208;
    case 'D':
        return 39;
    case HIT:
        return 9;
    case 'X':
        return 246;
    case 'E':
        return 0;
    }
}

void showGameScreen()
{
    int x = 55;
    int y = 2;

    system("cls");
    printf(isServer ? "PLAYER 1\n" : "PLAYER 2\n");
    printf("YOUR BOARD: \n");
    displayBoard(myBoard);
    gotoxy(x,y);
    for(int i = 0; i < 5; i++) {
        if(myHP[i] <= 0 )printf("\033[38;5;9m");
        printf("%s ",ships[i].name);
        gotoxy(x+20,y);
        for(int j = 0 ; j < ships[i].maxHP; j++) {
            printf("[%c]", (j >= (ships[i].maxHP - myHP[i]) ? ' ' : HIT));
        }
        if(myHP[i] <= 0 )printf("-SUNK!");
        printf("\033[0m");
        gotoxy(x,++y);

    }
    printf("\n\n\n\n\n\n\n\n");
    printf("OPPONENT BOARD: \n");
    displayBoard(opponentBoard);
    y+=10;
    gotoxy(x,y);
    for(int i = 0; i < SHIP_COUNT; i++) {
        if(clientHP[i] <= 0 )printf("\033[38;5;9m");
        printf("%s",ships[i].name);
        if(clientHP[i] <= 0 )printf("-SUNK!");
        printf("\033[0m");
        gotoxy(x,++y);
    }
    printf("\n\n\n\n\n\n");

    if(!isMyTurn) {
        printf("WAITING FOR OPPONENT TO PLAY!\n");
    }
}


void showGameOverScreeen(int winner)
{
    system("cls");
    printf("\n\n\n\n\n");
    printf("\033[38;5;9m");
    printf("\t\t\t   ______ ___     __  ___ ______   ____  _    __ ______ ____ ");
    printf("\n\t\t\t  / ____//   |   /  |/  // ____/  / __ \\| |  / // ____// __ \\ ");
    printf("\n\t\t\t / / __ / /| |  / /|_/ // __/    / / / /| | / // __/  / /_/ /");
    printf("\n\t\t\t/ /_/ // ___ | / /  / // /___   / /_/ / | |/ // /___ / _, _/ ");
    printf("\n\t\t\t\\____//_/  |_|/_/  /_//_____/   \\____/  |___//_____//_/ |_|  ");
    printf("\n\n\n\n\n\n\n");
    printf("\t\t\t\tPLAYER %d WINS\n",winner);
    printf("\n\t\t\t\tUSER STATISTICS: \n");
    printf("\t\t\t\tTotal moves: %d\n",moves);
    printf("\t\t\t\txHitAccuracyScore: %.2f%%\n",((score/(moves == 0 ? 1:moves)*100)));
    system("pause");
    exit(0);
}
