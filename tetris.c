/****************************************
* Jenntris
*****************************************
* A special mac version of tetris using
* SDL written for my girlfriend Jennifer.
*****************************************
* File: tetris.c
*
* Author: Ron Moore
*
*****************************************/

#include <stdio.h> //for debug
#include <stdlib.h>
#include <string.h> //for memcpy

#include "tetris.h"

void removeRow(GAMEDATA *thisGame, int starting)
{
	int y;
	int x;
	for (y = starting; y > 0; --y)
	{
		for (x = 0; x<10; ++x)
		{
			thisGame->playField[x][y] = thisGame->playField[x][y-1];
		}
	}
}

void checkRows(GAMEDATA *thisGame)
{
	int y;
	int x;
	int multiplier = 0;
	char gotRow = 1;
	char hasBlocks = 0;
	
	for (y=19; y>=0; --y)
	{
		for (x=0; x<10; ++x)
		{
			if (thisGame->playField[x][y] == 0)
			{
				gotRow = 0;
			}
			else
			{
				hasBlocks = 1;
			}
		}
		if (gotRow == 1)
		{
			thisGame->lines += 1;
			removeRow(thisGame, y);
			y=20; //start over; make sure we don't miss anything...
			multiplier += 1;
			if (thisGame->lines % 5 == 0)
			{
				thisGame->dropDelay -= thisGame->dropDelay / 100;
			}
		}
		
		if (hasBlocks == 1)
		{
			thisGame->junkHeight += 1;
		}
		hasBlocks = 0;
		gotRow = 1;
	}
	thisGame->score += multiplier * multiplier;
}

void makeShapes()
{
	SHAPES[0][0].Rx[0] = 0; SHAPES[0][0].Ry[0] = 0; //##
	SHAPES[0][0].Rx[1] = 1; SHAPES[0][0].Ry[1] = 0; // ##
	SHAPES[0][0].Rx[2] = 1; SHAPES[0][0].Ry[2] = 1; //
	SHAPES[0][0].Rx[3] = 2; SHAPES[0][0].Ry[3] = 1; //
	///////////////////////////
	SHAPES[0][1].Rx[0] = 1; SHAPES[0][1].Ry[0] = 0; // #
	SHAPES[0][1].Rx[1] = 1; SHAPES[0][1].Ry[1] = 1; //##
	SHAPES[0][1].Rx[2] = 0; SHAPES[0][1].Ry[2] = 1; //#
	SHAPES[0][1].Rx[3] = 0; SHAPES[0][1].Ry[3] = 2; //
	///////////////////////////
	memcpy(&SHAPES[0][2], &SHAPES[0][0], sizeof(PIECE));
	memcpy(&SHAPES[0][3], &SHAPES[0][1], sizeof(PIECE));
	///////////////////////////
	SHAPES[1][0].Rx[0] = 1; SHAPES[1][0].Ry[0] = 0; // ##
	SHAPES[1][0].Rx[1] = 2; SHAPES[1][0].Ry[1] = 0; //##
	SHAPES[1][0].Rx[2] = 0; SHAPES[1][0].Ry[2] = 1; //  
	SHAPES[1][0].Rx[3] = 1; SHAPES[1][0].Ry[3] = 1; //  
	///////////////////////////
	SHAPES[1][1].Rx[0] = 0; SHAPES[1][1].Ry[0] = 0; //#
	SHAPES[1][1].Rx[1] = 0; SHAPES[1][1].Ry[1] = 1; //##
	SHAPES[1][1].Rx[2] = 1; SHAPES[1][1].Ry[2] = 1; // #
	SHAPES[1][1].Rx[3] = 1; SHAPES[1][1].Ry[3] = 2; //
	///////////////////////////
	memcpy(&SHAPES[1][2], &SHAPES[1][0], sizeof(PIECE));
	memcpy(&SHAPES[1][3], &SHAPES[1][1], sizeof(PIECE));
	///////////////////////////
	SHAPES[2][0].Rx[0] = 0; SHAPES[2][0].Ry[0] = 0; //##
	SHAPES[2][0].Rx[1] = 1; SHAPES[2][0].Ry[1] = 0; //##
	SHAPES[2][0].Rx[2] = 1; SHAPES[2][0].Ry[2] = 1;
	SHAPES[2][0].Rx[3] = 0; SHAPES[2][0].Ry[3] = 1;
	///////////////////////////
	memcpy(&SHAPES[2][1], &SHAPES[2][0], sizeof(PIECE));
	memcpy(&SHAPES[2][2], &SHAPES[2][0], sizeof(PIECE));
	memcpy(&SHAPES[2][3], &SHAPES[2][0], sizeof(PIECE));
	///////////////////////////
	SHAPES[3][0].Rx[0] = 0; SHAPES[3][0].Ry[0] = 0; //####
	SHAPES[3][0].Rx[1] = 1; SHAPES[3][0].Ry[1] = 0;
	SHAPES[3][0].Rx[2] = 2; SHAPES[3][0].Ry[2] = 0;
	SHAPES[3][0].Rx[3] = 3; SHAPES[3][0].Ry[3] = 0;
	///////////////////////////
	SHAPES[3][1].Rx[0] = 0; SHAPES[3][1].Ry[0] = 0; //#
	SHAPES[3][1].Rx[1] = 0; SHAPES[3][1].Ry[1] = 1; //#
	SHAPES[3][1].Rx[2] = 0; SHAPES[3][1].Ry[2] = 2; //#
	SHAPES[3][1].Rx[3] = 0; SHAPES[3][1].Ry[3] = 3; //#
	///////////////////////////
	memcpy(&SHAPES[3][2], &SHAPES[3][0], sizeof(PIECE));
	memcpy(&SHAPES[3][3], &SHAPES[3][1], sizeof(PIECE));
	///////////////////////////
	SHAPES[4][0].Rx[0] = 1; SHAPES[4][0].Ry[0] = 0; // #
	SHAPES[4][0].Rx[1] = 0; SHAPES[4][0].Ry[1] = 1; //###
	SHAPES[4][0].Rx[2] = 1; SHAPES[4][0].Ry[2] = 1;
	SHAPES[4][0].Rx[3] = 2; SHAPES[4][0].Ry[3] = 1;
	///////////////////////////
	SHAPES[4][1].Rx[0] = 0; SHAPES[4][1].Ry[0] = 0; //#
	SHAPES[4][1].Rx[1] = 0; SHAPES[4][1].Ry[1] = 1; //##
	SHAPES[4][1].Rx[2] = 0; SHAPES[4][1].Ry[2] = 2; //#
	SHAPES[4][1].Rx[3] = 1; SHAPES[4][1].Ry[3] = 1;
	///////////////////////////
	SHAPES[4][2].Rx[0] = 0; SHAPES[4][2].Ry[0] = 0; //###
	SHAPES[4][2].Rx[1] = 1; SHAPES[4][2].Ry[1] = 0; // #
	SHAPES[4][2].Rx[2] = 2; SHAPES[4][2].Ry[2] = 0;
	SHAPES[4][2].Rx[3] = 1; SHAPES[4][2].Ry[3] = 1;
	///////////////////////////
	SHAPES[4][3].Rx[0] = 0; SHAPES[4][3].Ry[0] = 1; // #
	SHAPES[4][3].Rx[1] = 1; SHAPES[4][3].Ry[1] = 0; //##
	SHAPES[4][3].Rx[2] = 1; SHAPES[4][3].Ry[2] = 1; // #
	SHAPES[4][3].Rx[3] = 1; SHAPES[4][3].Ry[3] = 2;
	///////////////////////////
	SHAPES[5][0].Rx[0] = 0; SHAPES[5][0].Ry[0] = 0; //#
	SHAPES[5][0].Rx[1] = 0; SHAPES[5][0].Ry[1] = 1; //#
	SHAPES[5][0].Rx[2] = 0; SHAPES[5][0].Ry[2] = 2; //##
	SHAPES[5][0].Rx[3] = 1; SHAPES[5][0].Ry[3] = 2;
	///////////////////////////
	SHAPES[5][1].Rx[0] = 0; SHAPES[5][1].Ry[0] = 1; //  #
	SHAPES[5][1].Rx[1] = 1; SHAPES[5][1].Ry[1] = 1; //###
	SHAPES[5][1].Rx[2] = 2; SHAPES[5][1].Ry[2] = 1;
	SHAPES[5][1].Rx[3] = 2; SHAPES[5][1].Ry[3] = 0;
	///////////////////////////
	SHAPES[5][2].Rx[0] = 0; SHAPES[5][2].Ry[0] = 0; //##
	SHAPES[5][2].Rx[1] = 1; SHAPES[5][2].Ry[1] = 0; // #
	SHAPES[5][2].Rx[2] = 1; SHAPES[5][2].Ry[2] = 1; // #
	SHAPES[5][2].Rx[3] = 1; SHAPES[5][2].Ry[3] = 2;
	///////////////////////////
	SHAPES[5][3].Rx[0] = 0; SHAPES[5][3].Ry[0] = 1; //###
	SHAPES[5][3].Rx[1] = 0; SHAPES[5][3].Ry[1] = 0; //#  
	SHAPES[5][3].Rx[2] = 1; SHAPES[5][3].Ry[2] = 0; //
	SHAPES[5][3].Rx[3] = 2; SHAPES[5][3].Ry[3] = 0;
	///////////////////////////
	SHAPES[6][0].Rx[0] = 1; SHAPES[6][0].Ry[0] = 0; // #
	SHAPES[6][0].Rx[1] = 1; SHAPES[6][0].Ry[1] = 1; // #
	SHAPES[6][0].Rx[2] = 1; SHAPES[6][0].Ry[2] = 2; //##
	SHAPES[6][0].Rx[3] = 0; SHAPES[6][0].Ry[3] = 2;
	///////////////////////////
	SHAPES[6][1].Rx[0] = 0; SHAPES[6][1].Ry[0] = 1; //#
	SHAPES[6][1].Rx[1] = 1; SHAPES[6][1].Ry[1] = 1; //###
	SHAPES[6][1].Rx[2] = 2; SHAPES[6][1].Ry[2] = 1;
	SHAPES[6][1].Rx[3] = 0; SHAPES[6][1].Ry[3] = 0;
	///////////////////////////
	SHAPES[6][2].Rx[0] = 1; SHAPES[6][2].Ry[0] = 0; //##
	SHAPES[6][2].Rx[1] = 0; SHAPES[6][2].Ry[1] = 0; //#
	SHAPES[6][2].Rx[2] = 0; SHAPES[6][2].Ry[2] = 1; //#
	SHAPES[6][2].Rx[3] = 0; SHAPES[6][2].Ry[3] = 2;
	///////////////////////////
	SHAPES[6][3].Rx[0] = 2; SHAPES[6][3].Ry[0] = 1; //###
	SHAPES[6][3].Rx[1] = 0; SHAPES[6][3].Ry[1] = 0; //  #
	SHAPES[6][3].Rx[2] = 1; SHAPES[6][3].Ry[2] = 0; //
	SHAPES[6][3].Rx[3] = 2; SHAPES[6][3].Ry[3] = 0;
}

void fillPiece(GAMEDATA *thisGame)
{
	int i;
	for (i=0; i<4; ++i)
	{
		thisGame->currentPiece.x[i] = thisGame->currentPiece.upperLeftX + thisGame->currentPiece.Rx[i];
		thisGame->currentPiece.y[i] = thisGame->currentPiece.upperLeftY + thisGame->currentPiece.Ry[i];
	}
}

void placePiece(GAMEDATA *thisGame)
{
	int i;
	
	for (i=0; i<4; ++i)
	{
		thisGame->playField[thisGame->currentPiece.x[i]][thisGame->currentPiece.y[i] - 1] = 1;
	}
}

void newPiece(GAMEDATA *thisGame)
{	
	thisGame->currentPiece.type = rand() % 7;
	thisGame->currentPiece.rotation = 0;
	thisGame->currentPiece.upperLeftX = 4;
	thisGame->currentPiece.upperLeftY = 0;
	
	memcpy(thisGame->currentPiece.Rx, 
		SHAPES[thisGame->currentPiece.type][thisGame->currentPiece.rotation].Rx, 
		sizeof(char) * 4);
	memcpy(thisGame->currentPiece.Ry, 
		SHAPES[thisGame->currentPiece.type][thisGame->currentPiece.rotation].Ry, 
		sizeof(char) * 4);
	
	fillPiece(thisGame);
}

void doDrop(GAMEDATA *thisGame)
{
	static int doneDropping = 0;
	static int drops = 0;
	int i;
	thisGame->lastDrop = SDL_GetTicks();
	thisGame->currentPiece.upperLeftY += 1;
	
	for (i = 0; i < 4; ++i)
	{
		thisGame->currentPiece.y[i] += 1;
		
		if (thisGame->playField[thisGame->currentPiece.x[i]][thisGame->currentPiece.y[i]] != 0 ||
			thisGame->currentPiece.y[i] > 19)
		{
			doneDropping = 1;
		}
	}
	++drops;
	if (doneDropping == 1)
	{
		placePiece(thisGame);
		newPiece(thisGame);
		checkRows(thisGame);
		doneDropping = 0;
		if (drops == 1)
		{
			thisGame->running = -1;
		}
		drops = 0;
	}
}

void processRotate(GAMEDATA *thisGame)
{
	int i;
	memcpy(thisGame->currentPiece.Rx, 
		SHAPES[thisGame->currentPiece.type][thisGame->currentPiece.rotation].Rx, 
		sizeof(unsigned char) * 4);
	memcpy(thisGame->currentPiece.Ry, 
		SHAPES[thisGame->currentPiece.type][thisGame->currentPiece.rotation].Ry, 
		sizeof(unsigned char) * 4);
	fillPiece(thisGame);
	for (i = 0; i < 4; ++i)
	{
		if (thisGame->currentPiece.x[i] >= 10)
		{
			thisGame->currentPiece.upperLeftX -= thisGame->currentPiece.Rx[i];
		}
		if (thisGame->currentPiece.y[i] >= 20)
		{
			thisGame->currentPiece.upperLeftY -= thisGame->currentPiece.Ry[i];
		}
	}
	fillPiece(thisGame);
}

void rotateRight(GAMEDATA *thisGame)
{
	++thisGame->currentPiece.rotation;
	if (thisGame->currentPiece.rotation >= 4)
	{
		thisGame->currentPiece.rotation = 0;
	}
	processRotate(thisGame);
}

void rotateLeft(GAMEDATA *thisGame)
{
	--thisGame->currentPiece.rotation;
	if (thisGame->currentPiece.rotation >= 4) //use the > check because it's unsigned
	{
		thisGame->currentPiece.rotation = 3;
	}
	processRotate(thisGame);
}