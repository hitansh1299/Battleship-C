#ifndef GAMEUTILS_H_INCLUDED
#define GAMEUTILS_H_INCLUDED
///SOME USEFUL PREPROCESSOR DEFINITIONS
#define BOARD_SIZE 10
#define SHIP_COUNT 5

#define HIT '*'
#define MISS 'X'
#define EMPTY 'E'
#define AIRCRAFT_CARRIER 'A'
#define BATTLESHIP 'B'
#define CRUISER 'C'
#define SUBMARINE 'S'
#define DESTROYER 'D'
///END OF PREPROCESSOR DEFS

///GENERAL PURPOSE FIELDS
typedef struct Coord{ ///Coordinate, 0 based index, top left is (0,0); bottom right (N,N)
    int x,y;
}Coord;
///END OF GP FIELDS


///BOARD UTILS FIELDS
typedef struct Square{
    Coord coord;
    char ID[2];
    int isOccupied;
    char status;/// E for empty, H for hit, ID OF THE SHIP if occupied by a SHIP
    int colorCode;
}Square;

Square myBoard[BOARD_SIZE][BOARD_SIZE];
Square opponentBoard[BOARD_SIZE][BOARD_SIZE];

///END OF BOARD UTILS



///SERVER-CLIENT UTILS

///END OF SERVER-CLIENT UTILS



///SHIP UTILS FIELDS
char SHIP_NAMES[SHIP_COUNT][17];

typedef struct Ship{
    char* name;
    char ID;///DIFFERENT FROM ID IN SQUARE, HERE REPS. A SINGLE LETTER REP. OF THE SHIP.
    short maxHP;
    short HP;
    int orientation;/// 0 for horizontal 1 for vertical
    Coord coord;
    int isPlaced;///Can only have of 1 or 0
} Ship;

Ship ships[SHIP_COUNT];
///END OF SHIP UTILS

///END OF GAME UTILS

void initBoard(Square board[BOARD_SIZE][BOARD_SIZE]);

void initShips();
int getColorCode(char);

int moves;
double accuracy;
double score;

#endif // GAMEUTILS_H_INCLUDED
