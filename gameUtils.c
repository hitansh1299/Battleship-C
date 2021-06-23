#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gameUtils.h"

#define LEFT_ARROW 75
#define UP_ARROW 72
#define RIGHT_ARROW 77
#define DOWN_ARROW 80
#define ENTER 13

static void updateBoard();

void initBoard(Square board[BOARD_SIZE][BOARD_SIZE])
{

    int j = 0;
    for(char c = 'A'; c <= 'J'; c++) {
        for(int i = 0; i<BOARD_SIZE; i++) {
            board[j][i].ID[0] = c;
            board[j][i].ID[1] = (char)(i + 48);
            board[j][i].coord = (Coord) {
                .x = i, .y = j
            };
            board[j][i].status  = EMPTY;
            board[j][i].colorCode = getColorCode(board[i][j].status);
        }
        j++;
    }
}


void initShips()///INIT SHIP_NAMES[], AC, BShip, Cruiser, Sub, Des.and ships[]
{
    strcpy(SHIP_NAMES[0],"Aircraft Carrier");
    strcpy(SHIP_NAMES[1],"Battleship");
    strcpy(SHIP_NAMES[2],"Cruiser");
    strcpy(SHIP_NAMES[3],"Submarine");
    strcpy(SHIP_NAMES[4],"Destroyer");

    Ship AircraftCarrier = (Ship) {
        .name = SHIP_NAMES[0], .maxHP = 5, .HP = 5, .coord.x = 0, .coord.y = 0, .ID = AIRCRAFT_CARRIER
    };
    Ship Battleship = (Ship) {
        .name = SHIP_NAMES[1], .maxHP = 4, .HP = 4, .coord.x = 0, .coord.y = 0, .ID = BATTLESHIP
    };
    Ship Cruiser = (Ship) {
        .name = SHIP_NAMES[2], .maxHP = 3, .HP = 3, .coord.x = 0, .coord.y = 0, .ID = CRUISER
    };
    Ship Submarine = (Ship) {
        .name = SHIP_NAMES[3], .maxHP = 3, .HP = 3, .coord.x = 0, .coord.y = 0, .ID = SUBMARINE
    };
    Ship Destroyer = (Ship) {
        .name = SHIP_NAMES[4], .maxHP = 2, .HP = 2, .coord.x = 0, .coord.y = 0, .ID = DESTROYER
    };

    ships[0] = AircraftCarrier;
    ships[1] = Battleship;
    ships[2] = Cruiser;
    ships[3] = Submarine;
    ships[4] = Destroyer;
}

static Square getSquareCopy(Square s)
{
    Square copy;
    copy.coord = s.coord;

    strcpy(copy.ID,s.ID);
    copy.isOccupied = s.isOccupied;
    copy.status = s.status;

    return copy;
}




