#include <stdio.h>
#include "gameUtils.h"
#include "game.h"
#include "server.h"
#include "client.h"
#include "setup.h"
#include "controller.h"
#include "menu.h"
#include "view.h"
int main()
{
    menu();
    initShips();
    initBoard(myBoard);
    initBoard(opponentBoard);
    initController();
    //showGameScreen();
    setupGame();
    printf("\nAre you player 1 or 2?\n");
    int ch;
    scanf("%d", &ch);
    fflush(stdin);

    if(ch == 1) {
        isServer = 1;
        printf("Setting up server!\n");
        Smain();
    }
    else {
        isServer = 0;
        printf("Finding Server!\n");
        char *argv[2] = {"localhost",""};
        clientMain(2, argv);
    }
}

