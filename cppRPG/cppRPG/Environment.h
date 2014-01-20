#pragma once
#include "Sprite.h"
#include "stdafx.h"
#include "SDL_Setup.h"
#include "Tree.h"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
class Environment
{
public:
	Environment(SDL_Setup *p_sdl_setup, int passed_screenWidth, int passed_screenHeight, float *cameraX, float *cameraY);
	~Environment();

	void drawBack();
	void drawFront();

	void update();

	void loadEnvFromFile();
	void saveEnvFile();
	enum ModeType{
		PLAY,
		EDIT	
	};
	enum EnvType{
		ENV_NONE,
		ENV_FOREST,
	};

	std::vector<Tree*> getTrees(){ return trees; }
private:
	std::vector<Sprite*> grass;
	std::vector<Sprite*> border;
	Sprite *corner[4];
	SDL_Setup *sdl_setup;
	bool onePressed;
	int game_mode;
	int env_type;
	float *cameraX;
	float *cameraY;
	std::vector<Tree*> trees;
	
};

