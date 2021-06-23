#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <string.h>
#include "gameUtils.h"
#include "setup.h"
#include "view.h"

#define LEFT_ARROW 75
#define UP_ARROW 72
#define RIGHT_ARROW 77
#define DOWN_ARROW 80
#define ENTER 13
#define NEXT_SHIP 46
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

int currentShipNumber = 0;//Aircraft Carrier[0]
//Ship setShips[SHIP_COUNT];
//Square** board = board;
Ship* currentShip;
void runSetupPhase()
{
    currentShip = &ships[currentShipNumber];
    system("cls");
    printf("\033[0m");
    display();
    do {
        if (_kbhit()) {

            system("cls");
            char ch = _getch();
            if (ch == 0 || ch == -32) {
                switch(_getch()) {
                case RIGHT_ARROW:
                    shift(currentShip, 4);
                    break;
                case LEFT_ARROW:
                    shift(currentShip, 3);
                    break;
                case UP_ARROW:
                    shift(currentShip, 1);
                    break;
                case DOWN_ARROW:
                    shift(currentShip, 2);
                    break;
                }
            }
            if(ch == '.') {
                currentShipNumber = ((currentShipNumber + 1) % SHIP_COUNT);
                currentShip = &ships[currentShipNumber];
            }
            if(ch == ',') {
                currentShipNumber = --currentShipNumber < 0 ? SHIP_COUNT - 1 : currentShipNumber;
                currentShip = &ships[currentShipNumber];
            }
            if(ch == 'r' || ch == 'R') {
                shift(currentShip, 5);
            }
            if(ch == ENTER) {
                if(!isIntersectingSetShip(currentShip)) {
                    currentShip->isPlaced = 1;
                    currentShipNumber = ((currentShipNumber + 1) % SHIP_COUNT);
                    currentShip = &ships[currentShipNumber];
                }
                else {
                    printf("\033[31mNOT A VALID PLACE FOR THE SHIP!\033[0m");
                }
            }
            if(ch == 'F' || ch == 'f') {
                if(isShipsSet()) {
                    system("cls");
                    display();
                    printf("\033[38mAre you sure you want to confirm the position?(Y/N)\n\033[0m");
                    char ch;
                    scanf("%c",&ch);
                    if(ch == 'Y'||ch == 'y')
                        break;
                    system("cls");
                }
                else {
                    printf("\033[31mONE OR MORE SHIPS ARE YET TO BE PLACED!!\033[0m");
                }
            }
            display();
        }
    }
    while(1);

    printf("SETUP PHASE HAS ENDED!");
}

void display()
{
    updateShips();
    printf("\n///////////////////////////SETUP PHASE://///////////////////////////////////////\n\n");
    printf("-> Use Arrow keys to move ships\n");
    printf("-> Use 'R' to rotate ships\n");
    printf("-> Press Enter to set the ship\n");
    printf("-> Press < or > to change ships\n");
    printf("-> Press 'F' to finalize ships position\n");
    //printf("-> Press SET ");
    displayBoard(myBoard);
    printf("Current Ship: %s\n",SHIP_NAMES[currentShipNumber]);
}


void updateShips()
{
    for(int i = 0; i< BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            myBoard[i][j].status = EMPTY;
        }
    }
    for(int i = 0; i < SHIP_COUNT; i++) {
        if(ships[i].isPlaced == 0 && i != currentShipNumber) {
            continue;
        }
        placeShip(ships[i]);
    }
}

void placeShip(Ship s)
{
    int n = s.maxHP;
    int x = s.coord.x;
    int y = s.coord.y;


    if(s.orientation == 0) {
        for(int i = x; i < x + n; i++) {
            myBoard[y][i].status = s.ID;
            myBoard[y][i].colorCode = getColorCode(s.ID);
        }
    }
    else if(s.orientation == 1) {
        for(int i = y; i <y + n; i++) {
            myBoard[i][x].status = s.ID;
            myBoard[i][x].colorCode = getColorCode(s.ID);
        }
    }
}


///dir: 1 : UP | 2: DOWN | 3: LEFT | 4:RIGHT | 5:ROTATE
void shift(Ship *s, int dir)
{
    s->isPlaced = 0;
    switch(dir) {
    case 1:
        if(isValidPlace(*s, (Coord) {
        .x = s->coord.x, .y = s->coord.y - 1
    }, s->orientation)) {
            s->coord.y--;
        }
        break;
    case 2:
        if(isValidPlace(*s, (Coord) {
        .x = s->coord.x, .y = s->coord.y + 1
    }, s->orientation)) {
            s->coord.y++;
        }
        break;
    case 3:
        if(isValidPlace(*s, (Coord) {
        .x = s->coord.x - 1, .y = s->coord.y
    }, s->orientation)) {
            s->coord.x--;
        }
        break;
    case 4:
        if(isValidPlace(*s, (Coord) {
        .x = s->coord.x + 1, .y = s->coord.y
    }, s->orientation)) {
            s->coord.x++;
        }

        break;
    case 5:
        if(isValidPlace(*s, (Coord) {
        .x = s->coord.x, .y = s->coord.y
    }, !s->orientation)) {
            s->orientation = !s->orientation;
        }
        break;
    }
}

int isValidPlace(Ship s,Coord c, int orientation)
{
    if(c.x < 0 || c.x >= BOARD_SIZE) return 0;
    if(c.y < 0 || c.y >= BOARD_SIZE) return 0;

    if(orientation == 0) {
        if(c.x + s.maxHP > BOARD_SIZE) return 0;
    }
    if(orientation == 1) {
        if(c.y + s.maxHP > BOARD_SIZE) return 0;
    }
    return 1;
}



int isIntersectingSetShip(Ship *s)
{
    for(int i = 0; i < SHIP_COUNT; i++) {
        if(ships[i].isPlaced == 1 && i != currentShipNumber) {
            if(intersect(s, &ships[i])) {
                return 1;
            }
        }
    }
    return 0;
}

int intersect(Ship *s1, Ship *s2)
{
    ///ship1 is (x1,y1) to (x3,y3)
    ///ship2 is (x2,y2) to (x4,y4)
    int x1 = s1->coord.x;
    int y1 = s1->coord.y;

    int x2 = s2->coord.x;
    int y2 = s2->coord.y;

    int x3 = s1->orientation == 0 ? x1 + s1->maxHP - 1: x1;
    int y3 = s1->orientation == 0 ? y1 : y1 + s1->maxHP - 1;

    int x4 = s2->orientation == 0 ? x2 + s2->maxHP - 1: x2;
    int y4 = s2->orientation == 0 ? y2 : y2 + s2->maxHP - 1;


    if(x3 < x2 || x1 > x4) return 0;
    if(y3 < y2 || y1 > y4) return 0;
    if(x1 == x2 &&  y1 == y2) return 1;
    return 1;
}

int isShipsSet()
{
    for(int i = 0; i < SHIP_COUNT; i++) {
        if(ships[i].isPlaced == 0) return 0;
    }
    return 1;
}


