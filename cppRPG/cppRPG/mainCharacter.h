#pragma once
#include "Sprite.h"
#include "stdafx.h"
#include "SDL_Setup.h"
#include "Environment.h"

class mainCharacter
{
public:
	mainCharacter(SDL_Setup *sdl_setup, int *mouseX, int *mouseY, float *passed_cameraX, float*passed_cameraY, Environment *p_environment);
	~mainCharacter();

	float getDistance(int x1, int y1, int x2, int y2);

	void update();
	void draw();
private:
	Environment *environment;

	float SPEED;
	Sprite *bob;
	int follow_point_x;
	int follow_point_y;
	bool follow;
	bool stopAnimation;
	int timeCheck;
	float distance;
	int *mouseX;
	int *mouseY;
	SDL_Setup *sdl_setup;

	int debugTime;

	float *cameraX;
	float *cameraY;

	void mainCharacter::updateAnimation();
	void mainCharacter::updateControls();
};

