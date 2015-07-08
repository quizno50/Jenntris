/****************************************
* Jenntris
*****************************************
* A special mac version of tetris using
* SDL written for my girlfriend Jennifer.
*****************************************
* File: tetris.h
*
* Author: Ron Moore
*
*****************************************/
#ifndef TETRIS__H
#define TETRIS__H

typedef struct
{
	unsigned char type;
	unsigned char rotation;
	unsigned char x[4];
	unsigned char y[4];
	unsigned char Rx[4];
	unsigned char Ry[4];
	unsigned char upperLeftX;
	unsigned char upperLeftY;
} PIECE;

typedef struct
{
	char running;
	char playField[10][20];
	char junkHeight;
	char level;
	unsigned int dropDelay;
	unsigned int lastDrop;
	unsigned int score;
	unsigned int lines;
	PIECE currentPiece;
	char speedDrop;
} GAMEDATA;

extern void fillPiece(GAMEDATA *thisGame);
extern void newPiece(GAMEDATA *thisGame);
extern void doDrop(GAMEDATA *thisGame);
extern void makeShapes();
extern void rotateLeft(GAMEDATA *thisGame);
extern void rotateRight(GAMEDATA *thisGame);
extern void checkRows(GAMEDATA *thisGame);

PIECE SHAPES[7][4];

#endif