/****************************************
* Jenntris
*****************************************
* A special mac version of tetris using
* SDL written for my girlfriend Jennifer.
*****************************************
* File: main.c
*
* Author: Ron Moore
*
*****************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>

#include "tetris.h"
#include "graphics.h"

void clearField(GAMEDATA *thisGame)
{
	int x;
	int y;
	for (y=0; y<20; ++y)
	{
		for (x=0; x<10; ++x)
		{
			thisGame->playField[x][y] = 0;
		}
	}
}

int main(int argc, char **argv)
{
	SDL_Surface *screen;
	SDL_Event theEvent;
	GAMEDATA thisGame;
	SDL_Init(SDL_INIT_VIDEO);
	int i;
	int undoMove = 0;
	
	screen = SDL_SetVideoMode(640, 480, 32, SDL_DOUBLEBUF);
	
	thisGame.running = 1;
	srand(time(NULL));
	thisGame.lastDrop = SDL_GetTicks();
	makeShapes();
	newPiece(&thisGame);
	thisGame.dropDelay = 800;
	thisGame.junkHeight = 0;
	thisGame.score = 0;
	thisGame.lines = 0;
	thisGame.speedDrop = 0;
	clearField(&thisGame);
	makeChars();
	
	while (thisGame.running == 1)
	{
		while (SDL_PollEvent(&theEvent))
		{
			if (theEvent.type == SDL_QUIT)
			{
				thisGame.running = 0;
			}
			if (theEvent.type == SDL_KEYDOWN)
			{
				if (theEvent.key.keysym.sym == SDLK_LEFT)
				{
					thisGame.currentPiece.upperLeftX -= 1;
					for (i=0;i<4;++i)
					{
						thisGame.currentPiece.x[i] -= 1;
						if (thisGame.playField[thisGame.currentPiece.x[i]][thisGame.currentPiece.y[i]] != 0 ||
							thisGame.currentPiece.x[i] > 10)
						{
							undoMove = 1;
						}
					}
					if (undoMove)
					{
						undoMove = 0;
						thisGame.currentPiece.upperLeftX += 1;
						for (i=0; i<4; ++i)
						{
							thisGame.currentPiece.x[i]+=1;
						}
					}
				}
				else if (theEvent.key.keysym.sym == SDLK_RIGHT)
				{
					thisGame.currentPiece.upperLeftX += 1;
					for (i=0; i<4; ++i)
					{
						thisGame.currentPiece.x[i] += 1;
						if (thisGame.playField[thisGame.currentPiece.x[i]][thisGame.currentPiece.y[i]] != 0 ||
							thisGame.currentPiece.x[i] >= 10)
						{
							undoMove = 1;
						}
					}
					if (undoMove)
					{
						undoMove = 0;
						thisGame.currentPiece.upperLeftX += 1;
						for (i=0; i<4; ++i)
						{
							thisGame.currentPiece.x[i]-=1;
						}
					}
				}
				else if (theEvent.key.keysym.sym == SDLK_UP)
				{
					rotateLeft(&thisGame);
				}
				else if (theEvent.key.keysym.sym == SDLK_RSHIFT) 
				{
					rotateRight(&thisGame);
				}
				else if (theEvent.key.keysym.sym == SDLK_DOWN)
				{
					thisGame.speedDrop = 1;
				}
				drawGame(&thisGame);
			}
			else if (theEvent.type == SDL_KEYUP)
			{
				if (theEvent.key.keysym.sym == SDLK_DOWN)
				{
					thisGame.speedDrop = 0;
				}
			}
		}
		
		if (SDL_GetTicks() > thisGame.lastDrop + (thisGame.speedDrop == 1?20:thisGame.dropDelay))
		{
			doDrop(&thisGame);
		}
		
		drawGame(&thisGame);
		SDL_Flip(screen);
	}
	
	if (thisGame.running == -1)
	{
		printf("Game Over...\n");
	}
	printf("Your score: %i\n", thisGame.score);
	
	return 0;
}