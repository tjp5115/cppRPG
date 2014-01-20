#pragma once
#include "mainCharacter.h"
#include "SDL_Setup.h"
#include "Sprite.h"
#include "Environment.h"
#include <math.h>
class Cmain
{
public:
	Cmain(int passed_screenWidth, int passed_screenHeight);
	~Cmain();

	void GameLoop();

private: 
	int screenHeight;
	int screenWidth;

	Environment *forestArea;

	bool quit;

	int mouseX;
	int mouseY;

	SDL_Setup * sdl_setup;

	mainCharacter *bob;

	float cameraX;
	float cameraY;
};

