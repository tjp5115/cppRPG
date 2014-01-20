#include "stdafx.h"
#pragma once
class SDL_Setup
{
public:
	SDL_Setup(bool* quit, int passed_screenWidth, int passed_screenHeight);
	~SDL_Setup(void);

	SDL_Renderer* getRenderer();
	SDL_Event* getMainEvent();

	void begin();
	void end();
private:
	int screenWidth;
	int screenHeight;
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event *mainEvent;
};

