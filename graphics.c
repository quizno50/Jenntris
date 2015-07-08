/****************************************
* Jenntris
*****************************************
* A special mac version of tetris using
* SDL written for my girlfriend Jennifer.
*****************************************
* File: graphics.c
*
* Author: Ron Moore
*
*****************************************/

#include "graphics.h"

void drawPoint(int x, int y, Uint32 c, SDL_Surface *surface)
{
   Uint32 *returnPixel;
   
   returnPixel = (Uint32*)surface->pixels;
   returnPixel += (surface->w * y);
   returnPixel += x;
   *returnPixel = c;
}

void swap(int *a, int *b)
{
   *a = *a ^ *b;
   *b = *a ^ *b;
   *a = *a ^ *b;
}

void drawLine(int x0, int y0, int x1, int y1, Uint32 c, SDL_Surface *surface)
{
   char steep = (abs(y1 - y0) > abs(x1 - x0));
   if (steep)
   {
      swap(&x0, &y0);
      swap(&x1, &y1);
   }
   if (x0 > x1)
   {
      swap(&x0, &x1);
      swap(&y0, &y1);
   }
   int deltax = x1 - x0;;
   int deltay = abs(y1 - y0);
   int error = 0;
   int ystep;
   int y = y0;
   int x;
   if (y0 < y1)
      ystep = 1;
   else
      ystep = -1;
   for (x = x0; x <= x1; ++x)
   {
      if (steep)
      {
         drawPoint(y, x, c, surface);
      }
      else
      {
         drawPoint(x, y, c, surface);
      }
      error += deltay;
      if (2 * error > deltax)
      {
         y += ystep;
         error -= deltax;
      }
   }
}


void drawGame(GAMEDATA *thisGame)
{
	const unsigned char PIECE_WIDTH = 20;
	const unsigned char PIECE_HEIGHT = 20;
	unsigned char x = 0;
	unsigned char y = 0;
	SDL_Surface *screen;
	SDL_Rect playRect;
	SDL_Rect pieceRect;
	
	screen = SDL_GetVideoSurface();
	playRect.x = 0;
	playRect.y = 0;
	playRect.w = PIECE_WIDTH * 10 + 14;
	playRect.h = PIECE_HEIGHT * 20 + 24;
	
	SDL_FillRect(screen, &playRect, SDL_MapRGB(screen->format, 255, 255, 255));
	
	playRect.x = 2;
	playRect.y = 2;
	playRect.w = PIECE_WIDTH * 10 + 10;
	playRect.h = PIECE_HEIGHT * 20 + 20;
	
	SDL_FillRect(screen, &playRect, SDL_MapRGB(screen->format, 0,0,0));
	
	for (y=0; y<20; ++y)
	{
		for (x=0; x<10; ++x)
		{
			pieceRect.x = x * PIECE_WIDTH + playRect.x + x;
			pieceRect.y = y * PIECE_HEIGHT + playRect.y + y;
			pieceRect.w = PIECE_WIDTH;
			pieceRect.h = PIECE_HEIGHT;
			if (thisGame->playField[x][y] != 0)
			{
				SDL_FillRect(screen, &pieceRect, SDL_MapRGB(screen->format, 0, 255, 0));
			}
			else if (thisGame->playField[x][y] == 0)
			{
				SDL_FillRect(screen, &pieceRect, SDL_MapRGB(screen->format, 0, 0, 0));
			}
		}
	}
	
	for (x = 0; x < 4; ++x)
	{
		pieceRect.x = thisGame->currentPiece.x[x] * PIECE_WIDTH + playRect.x + 
			thisGame->currentPiece.x[x];
		pieceRect.y = thisGame->currentPiece.y[x] * PIECE_HEIGHT + playRect.y + 
			thisGame->currentPiece.y[x];
		SDL_FillRect(screen, &pieceRect, SDL_MapRGB(screen->format, 255, 255, 0));
	}
	
	scoreDraw(thisGame->score);
	linesDraw(thisGame->lines);
}

void makeChars()
{
	CHARS[0].points[0][0] = 37; CHARS[0].points[1][0] = 4;
	CHARS[0].points[0][1] = 6; CHARS[0].points[1][1] = 20;
	CHARS[0].points[0][2] = 6; CHARS[0].points[1][2] = 96;
	CHARS[0].points[0][3] = 37; CHARS[0].points[1][3] = 118;
	CHARS[0].points[0][4] = 67; CHARS[0].points[1][4] = 96;
	CHARS[0].points[0][5] = 67; CHARS[0].points[1][5] = 20;
	CHARS[0].points[0][6] = 37; CHARS[0].points[1][6] = 4;
	CHARS[0].numOPoints = 7;
	CHARS[1].points[0][0] = 23; CHARS[1].points[1][0] = 17;
	CHARS[1].points[0][1] = 36; CHARS[1].points[1][1] = 4;
	CHARS[1].points[0][2] = 36; CHARS[1].points[1][2] = 111;
	CHARS[1].points[0][3] = 10; CHARS[1].points[1][3] = 111;
	CHARS[1].points[0][4] = 65; CHARS[1].points[1][4] = 111;
	CHARS[1].numOPoints = 5;
	CHARS[2].points[0][0] = 11; CHARS[2].points[1][0] = 20;
	CHARS[2].points[0][1] = 22; CHARS[2].points[1][1] = 7;
	CHARS[2].points[0][2] = 48; CHARS[2].points[1][2] = 7;
	CHARS[2].points[0][3] = 59; CHARS[2].points[1][3] = 16;
	CHARS[2].points[0][4] = 65; CHARS[2].points[1][4] = 28;
	CHARS[2].points[0][5] = 58; CHARS[2].points[1][5] = 44;
	CHARS[2].points[0][6] = 9; CHARS[2].points[1][6] = 108;
	CHARS[2].points[0][7] = 61; CHARS[2].points[1][7] = 108;
	CHARS[2].numOPoints = 8;
	CHARS[3].points[0][0] = 9; CHARS[3].points[1][0] = 21;
	CHARS[3].points[0][1] = 35; CHARS[3].points[1][1] = 10;
	CHARS[3].points[0][2] = 60; CHARS[3].points[1][2] = 19;
	CHARS[3].points[0][3] = 60; CHARS[3].points[1][3] = 45;
	CHARS[3].points[0][4] = 35; CHARS[3].points[1][4] = 52;
	CHARS[3].points[0][5] = 60; CHARS[3].points[1][5] = 58;
	CHARS[3].points[0][6] = 60; CHARS[3].points[1][6] = 100;
	CHARS[3].points[0][7] = 37; CHARS[3].points[1][7] = 107;
	CHARS[3].points[0][8] = 12; CHARS[3].points[1][8] = 101;
	CHARS[3].numOPoints = 9;
	CHARS[4].points[0][0] = 25; CHARS[4].points[1][0] = 7;
	CHARS[4].points[0][1] = 13; CHARS[4].points[1][1] = 41;
	CHARS[4].points[0][2] = 62; CHARS[4].points[1][2] = 41;
	CHARS[4].points[0][3] = 55; CHARS[4].points[1][3] = 41;
	CHARS[4].points[0][4] = 55; CHARS[4].points[1][4] = 7;
	CHARS[4].points[0][5] = 55; CHARS[4].points[1][5] = 112;
	CHARS[4].numOPoints = 6;
	CHARS[5].points[0][0] = 57; CHARS[5].points[1][0] = 14;
	CHARS[5].points[0][1] = 17; CHARS[5].points[1][1] = 14;
	CHARS[5].points[0][2] = 12; CHARS[5].points[1][2] = 57;
	CHARS[5].points[0][3] = 35; CHARS[5].points[1][3] = 50;
	CHARS[5].points[0][4] = 56; CHARS[5].points[1][4] = 56;
	CHARS[5].points[0][5] = 66; CHARS[5].points[1][5] = 81;
	CHARS[5].points[0][6] = 56; CHARS[5].points[1][6] = 107;
	CHARS[5].points[0][7] = 36; CHARS[5].points[1][7] = 115;
	CHARS[5].points[0][8] = 12; CHARS[5].points[1][8] = 107;
	CHARS[5].numOPoints = 9;
	CHARS[6].points[0][0] = 55; CHARS[6].points[1][0] = 14;
	CHARS[6].points[0][1] = 36; CHARS[6].points[1][1] = 6;
	CHARS[6].points[0][2] = 15; CHARS[6].points[1][2] = 15;
	CHARS[6].points[0][3] = 6; CHARS[6].points[1][3] = 54;
	CHARS[6].points[0][4] = 17; CHARS[6].points[1][4] = 112;
	CHARS[6].points[0][5] = 37; CHARS[6].points[1][5] = 120;
	CHARS[6].points[0][6] = 61; CHARS[6].points[1][6] = 111;
	CHARS[6].points[0][7] = 71; CHARS[6].points[1][7] = 84;
	CHARS[6].points[0][8] = 48; CHARS[6].points[1][8] = 63;
	CHARS[6].points[0][9] = 10; CHARS[6].points[1][9] = 75;
	CHARS[6].numOPoints = 10;
	CHARS[7].points[0][0] = 13; CHARS[7].points[1][0] = 20;
	CHARS[7].points[0][1] = 13; CHARS[7].points[1][1] = 10;
	CHARS[7].points[0][2] = 66; CHARS[7].points[1][2] = 10;
	CHARS[7].points[0][3] = 15; CHARS[7].points[1][3] = 115;
	CHARS[7].numOPoints = 4;
	CHARS[8].points[0][0] = 37; CHARS[8].points[1][0] = 10;
	CHARS[8].points[0][1] = 12; CHARS[8].points[1][1] = 19;
	CHARS[8].points[0][2] = 12; CHARS[8].points[1][2] = 52;
	CHARS[8].points[0][3] = 68; CHARS[8].points[1][3] = 77;
	CHARS[8].points[0][4] = 68; CHARS[8].points[1][4] = 114;
	CHARS[8].points[0][5] = 37; CHARS[8].points[1][5] = 122;
	CHARS[8].points[0][6] = 7; CHARS[8].points[1][6] = 115;
	CHARS[8].points[0][7] = 7; CHARS[8].points[1][7] = 74;
	CHARS[8].points[0][8] = 62; CHARS[8].points[1][8] = 53;
	CHARS[8].points[0][9] = 62; CHARS[8].points[1][9] = 18;
	CHARS[8].points[0][10] = 37; CHARS[8].points[1][10] = 10;
	CHARS[8].numOPoints = 11;
	CHARS[9].points[0][0] = 35; CHARS[9].points[1][0] = 4;
	CHARS[9].points[0][1] = 14; CHARS[9].points[1][1] = 13;
	CHARS[9].points[0][2] = 5; CHARS[9].points[1][2] = 53;
	CHARS[9].points[0][3] = 37; CHARS[9].points[1][3] = 59;
	CHARS[9].points[0][4] = 58; CHARS[9].points[1][4] = 51;
	CHARS[9].points[0][5] = 65; CHARS[9].points[1][5] = 31;
	CHARS[9].points[0][6] = 58; CHARS[9].points[1][6] = 14;
	CHARS[9].points[0][7] = 35; CHARS[9].points[1][7] = 4;
	CHARS[9].points[0][8] = 58; CHARS[9].points[1][8] = 14;
	CHARS[9].points[0][9] = 65; CHARS[9].points[1][9] = 31;
	CHARS[9].points[0][10] = 65; CHARS[9].points[1][10] = 116;
	CHARS[9].numOPoints = 11;
}

void drawChar(char inChar, SDL_Rect *destination)
{
	SDL_Surface *screen;
	static SDL_Surface *charSurface = NULL;
	int i;
	
	screen = SDL_GetVideoSurface();
	inChar -= 48;
	
	if (charSurface == NULL)
	{
		charSurface = SDL_CreateRGBSurface(SDL_HWSURFACE, destination->w, destination->h,
			32,
			screen->format->Rmask, screen->format->Gmask, screen->format->Bmask,
			screen->format->Amask);
	}
	
	SDL_FillRect(charSurface, NULL, SDL_MapRGB(charSurface->format, 0, 0, 0));
	
	if (inChar >= 0 && inChar <= 9)
	{
		if (SDL_MUSTLOCK(screen) != 0)
		{
			SDL_LockSurface(screen);
		}
		
		for (i = 1; i < CHARS[inChar].numOPoints; ++i)
		{
			drawLine(CHARS[inChar].points[0][i], CHARS[inChar].points[1][i],
				CHARS[inChar].points[0][i-1], CHARS[inChar].points[1][i-1],
				SDL_MapRGB(screen->format, 255, 0, 0),
				charSurface);
		}
		if (SDL_MUSTLOCK(screen) != 0)
		{
			SDL_UnlockSurface(screen);
		}
		
		SDL_BlitSurface(charSurface, NULL, screen, destination);
	}
}

void scoreDraw(int score)
{
	char data[20];
	SDL_Rect destRect;
	char i=0;
	
	sprintf(data, "%i", score);
	
	destRect.x = 300;
	destRect.y = 10;
	destRect.w = 75;
	destRect.h = 150;
	
	while (data[i] != 0)
	{
		drawChar(data[i], &destRect);
		destRect.x += destRect.w;
		++i;
	}
}

void linesDraw(int lines)
{
	char data[20];
	SDL_Rect destRect;
	char i=0;
	
	sprintf(data, "%i", lines);
	
	destRect.x = 300;
	destRect.y = 200;
	destRect.w = 75;
	destRect.h = 150;
	
	while (data[i] != 0)
	{
		drawChar(data[i], &destRect);
		destRect.x += destRect.w;
		++i;
	}
}