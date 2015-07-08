/****************************************
* Jenntris
*****************************************
* A special mac version of tetris using
* SDL written for my girlfriend Jennifer.
*****************************************
* File: graphics.h
*
* Author: Ron Moore
*
*****************************************/
#ifndef GRAPHICS__H
#define GRAPHICS__H

#include <SDL.h>

#include "tetris.h"

typedef struct
{
	int numOPoints;
	int points[2][11];
} CHARACTER;

extern void drawGame(GAMEDATA *thisGame);
extern void drawPoint(int x, int y, Uint32 c, SDL_Surface *surface);
extern void swap(int *a, int *b);
extern void drawLine(int x0, int y0, int x1, int y1, Uint32 c, SDL_Surface *surface);
extern void makeChars();
extern void drawChar(char inChar, SDL_Rect *destination);
extern void scoreDraw(int);
extern void linesDraw(int lines);

CHARACTER CHARS[10];

#endif
