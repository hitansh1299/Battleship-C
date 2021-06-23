#include<stdio.h>
#include<strings.h>
#include<conio.h>
#include<dos.h>
#include<windows.h>

#define DOWN_ARROW 80
#define UP_ARROW 72
#define ENTER 13
#define ESC 27

COORD coord = {0,0};

void rules();
void intro();
int menu();
int width = 104;

void gotoxy (int x, int y)
{
    coord.X = x;
    coord.Y = y; // X and Y coordinates
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int menu()
{
    int n;
    printf("\n\n\n\n\n");
    //centre aligning
    char str[] = "BATTLESHIPS";
    int length = strlen(str);  // Discount the terminal '\0'
    int pad = (length >= width) ? 0 : (width - length) / 2;
    system("cls");
    printf("\033[1;38;5;196m ");
    printf("\n\n\n");

    printf("\033[38;2;20;88;193m");
    printf(  "\t\t      ____  ___   ____________ __    ______\033[38;2;226;51;49m _____ __  __ ________  _____\033[38;2;20;88;193m");
    printf("\n\t\t     / __ )/   | /_  __/_  __// /   / ____/\033[38;2;226;51;49m/  __// / / //  _/ __ \\/ ___/ \033[38;2;20;88;193m");
    printf("\n\t\t    / __  / /| |  / /   / /  / /   / __/  \033[38;2;226;51;49m/__ \\ / /_/ / / // /_/ /\\__ \\ \033[38;2;20;88;193m");
    printf("\n\t\t   / /_/ / ___ | / /   / /  / /___/ /___ \033[38;2;226;51;49m ___/ / __  / / // ____/___/ /  \033[38;2;20;88;193m");
    printf("\n\t\t  /_____/_/  |_|/_/   /_/  /_____/_____/\033[38;2;226;51;49m /____/_/ /_//___/_/    /____/  \033[0m");
    int x=45,y=18;
    gotoxy(x,y);
    printf("\033[38;2;252;255;219m");
    printf(">");
    char str1[] = "PLAY NOW"; //START
    char str2[] = "INTRODUCTION";
    char str3[] = "HOW TO PLAY"; //INSTRUCTIONS
    char str4[] = "QUIT"; //EXIT
    puts(str1);
    for(int i=0; i<(pad); i++) {
        printf(" ");

    }
    puts(str2);
    for(int i=0; i<(pad); i++) {
        printf(" ");

    }
    puts(str3);
    for(int i=0; i<(pad); i++) {
        printf(" ");
    }
    puts(str4);
    gotoxy(x,y);
    printf("\033[15m");
    while(1) {
        char ch;
        ch = _getch();
        if(ch==0 || ch==-32) {
            switch(_getch()) {
            case DOWN_ARROW: {
                gotoxy(x,y);
                printf(" ");
                y = y + 1 > 21 ? 21 : ++y;
                gotoxy(x,y);
                printf(">");
                break;
            }

            case UP_ARROW: {
                gotoxy(x,y);
                printf(" ");
                y = y - 1 < 18 ? 18 : --y;
                gotoxy(x,y);
                printf(">");
                break;
            }
            }
        }

        char chr;

        if(ch == ENTER) {
            if(y==18) {
                system("cls");
                return;
            }

            else if(y==19) {

                system("cls");
                intro();
                return;

            }
            else if(y==20) {

                system("cls");
                rules();
                return;
            }
            else if(y==21) {
                system("cls");
                exit(0);
            }
        }
    }
}


void rules()
{

    printf("<Press Esc to go back");
    char t;
    char k[] = "HOW TO PLAY?";
    int l1 = strlen(k);
    int pad2 = (l1 >= width) ? 0 : (width - l1) / 2;
    printf("\n\n\n");
    for(int i=0; i<(pad2); i++) {
        printf(" ");
    }
    puts(k);
    printf("\n\n\n");
    printf("\t  1. The first step is to set your virtual board by placing your ships across");
    printf("\n\t     the board. A few things to keep in mind while placing your ships");
    printf("\n\t\t  >Ships can only be placed horizontally or vertically \n\t\t  >Ships cannot overlap each other");
    printf("\n\t\t  >All five ships must be placed \n\t\t  >The positions of the placed ships cannot be altered after the \n\t\t  commencement of the game");
    printf("\n\t  2. After the ships are placed, you will now be able to view your board along ");
    printf("\n\t     with your opponent's board on the screen. The grid is labelled [A-J] column wise");
    printf("\n\t     and row wise[0-9]. Take a shot at the opponent's board using the coordinates.");
    printf("\n\t  3. If it's a miss, an 'X' appears at the square. If it's a hit, an '*' will ");
    printf("\n\t     appear at the square and you get an additional shot for every hit, till");
    printf("\n\t     you encounter a miss.");
    printf("\n\t  4. When all the squares of a ship is hit, the opponent's respective ship sinks");
    printf("\n\t  5. Take turns shooting until one player has lost all their ships. Whoever ");
    printf("\n\t     manages to sink all of their opponent's ships first wins the game.");
    do {
        t = getch();

        if(t == ESC) {
            system("cls");
            menu();
            break;
        }
    }
    while(1);
}

void intro()
{

    printf("<Press Esc to go back");
    printf("\n\n");
    char i[] = "INTRODUCTION";
    int l2 = strlen(i);
    int pad3 = (l2 >= width) ? 0 : (width - l2) / 2;
    for(int i=0; i<(pad3); i++) {
        printf(" ");

    }
    puts(i);
    printf("\n\n");
    printf("   Battleships is a two-player strategy-guessing game which tests your planning, precision ");
    printf("\n   and strategic thinking which will have you in splits trying to figure out your opponent's");
    printf("\n   mind all while being fun and a great way to tap into your curiosity, creativity and");
    printf("\n   well, entertainment.");
    printf("\n\n");
    printf("   So are you ready to test your grit?");
    do {
        char z;
        z = getch();
        if (z == ESC) {
            menu();
            break;
        }
    }
    while(1);
}
