#pragma once
#include "Sprite.h"
#include "stdafx.h"
#include "SDL_Setup.h"

class Tree
{
public:
	Tree(SDL_Setup *p_sdl_setup, int x, int y, float *cameraX, float *cameraY);
	~Tree();

	void drawCrown();
	void drawTrunk();

	int getX(){ return x; };
	int getY(){ return y; };

	Sprite* getTrunk(){ return trunk; }
	Sprite* getCrown(){ return crown; }

	float *cameraX;
	float *cameraY;
private:
	int x, y;
	SDL_Setup *sdl_setup;
	Sprite *crown;
	Sprite *trunk;
};

