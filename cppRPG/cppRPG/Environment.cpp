#include "Environment.h"


Environment::Environment(SDL_Setup *p_sdl_setup, int passed_screenWidth, int passed_screenHeight,float *passed_cameraX, float *passed_cameraY)
{
	cameraX = passed_cameraX;
	cameraY = passed_cameraY;
	int grassWidth= 130;
	int cWidth = 264;
	int cHeight= 275;
	onePressed = false;
	sdl_setup = p_sdl_setup;
	for (int i = 0; i < 4; ++i){
		int j = 0;

		for (j; j < 7; ++j){
			if (i == 0){
				border.push_back(new Sprite(sdl_setup->getRenderer(), "data/environment/side_l.png", passed_screenWidth   * i - grassWidth, passed_screenHeight  * j, grassWidth, passed_screenHeight, cameraX, cameraY, CollisionRect()));
			}
			else if (i == 3){
				i++;
				border.push_back(new Sprite(sdl_setup->getRenderer(), "data/environment/side_r.png", passed_screenWidth * i, passed_screenHeight * j, grassWidth, passed_screenHeight, cameraX, cameraY, CollisionRect()));
				--i;
			}
			if (j == 0){
				border.push_back(new Sprite(sdl_setup->getRenderer(), "data/environment/side_u.png", passed_screenWidth * i, passed_screenHeight * j - grassWidth, passed_screenWidth, grassWidth, cameraX, cameraY, CollisionRect()));
			}else if (j == 6){
				j++;
				border.push_back(new Sprite(sdl_setup->getRenderer(), "data/environment/side_b.png", passed_screenWidth * i, passed_screenHeight * j, passed_screenWidth, grassWidth, cameraX, cameraY, CollisionRect()));
				j--;
			}

			if (j == 0 & i == 0){
				corner[0] = new Sprite(sdl_setup->getRenderer(), "data/environment/corner_tl.png", passed_screenWidth * i - grassWidth, passed_screenHeight * j - grassWidth, cWidth, cHeight, cameraX, cameraY, CollisionRect());
			}
			else if (j == 0 && i == 3){
				corner[1] = new Sprite(sdl_setup->getRenderer(), "data/environment/corner_tr.png", passed_screenWidth * i + passed_screenWidth - cWidth/2, passed_screenHeight * j - cHeight/2, cWidth, cHeight, cameraX, cameraY, CollisionRect());
			}
			else if (j == 6 && i == 0){
				corner[2] = new Sprite(sdl_setup->getRenderer(), "data/environment/corner_bl.png", passed_screenWidth * i - cWidth/2 , passed_screenHeight * j + passed_screenHeight-cHeight/2, cWidth, cHeight, cameraX, cameraY, CollisionRect());
			}
			else if (j == 6 && i == 3){
				corner[3] = new Sprite(sdl_setup->getRenderer(), "data/environment/corner_br.png", passed_screenWidth * i + passed_screenWidth - cWidth/2, passed_screenHeight * j +passed_screenHeight- cWidth/2, cWidth, cHeight, cameraX, cameraY, CollisionRect());
			}

			grass.push_back( new Sprite(sdl_setup->getRenderer(), "data/environment/grass.bmp", passed_screenWidth * i, passed_screenHeight * j, passed_screenWidth, passed_screenHeight, cameraX, cameraY,CollisionRect()) );
		}

	}
	game_mode = PLAY;
	env_type = ENV_NONE;

	loadEnvFromFile();
}


Environment::~Environment()
{
	for (std::vector<Sprite*>::iterator i = grass.begin(); i != grass.end(); ++i){
		delete (*i);
	}
	for (std::vector<Tree*>::iterator i = trees.begin(); i != trees.end(); ++i){
		delete (*i);
	}

	for (std::vector<Sprite*>::iterator i = border.begin(); i != border.end(); ++i){
		delete (*i);
	}
	for (int i = 0; i < 4; ++i) {
		delete corner[i];
	}

	border.clear();
	trees.clear();
}

void Environment::drawBack(){

	for (int i = 0; i < 4; ++i) {
		corner[i]->Draw();
	}
	for (std::vector<Sprite*>::iterator i = grass.begin(); i != grass.end(); ++i){
		(*i)->Draw();
	}

	for (std::vector<Tree*>::iterator i = trees.begin(); i != trees.end(); ++i){
		(*i)->drawTrunk();
	}

	for (std::vector<Sprite*>::iterator i = border.begin(); i != border.end(); ++i){
		(*i)->Draw();
	}
}

void Environment::drawFront(){
	for (std::vector<Tree*>::iterator i = trees.begin(); i != trees.end(); ++i){
		(*i)->drawCrown();
	}

}

void Environment::update(){
	if (game_mode == EDIT){
		if (sdl_setup->getMainEvent()->type == SDL_KEYDOWN){
			if (!onePressed && sdl_setup->getMainEvent()->key.keysym.sym == SDLK_F1){
				trees.push_back(new Tree(sdl_setup, -*cameraX + 275, -*cameraY + 50, cameraX, cameraY));
				onePressed = true;
				//std::cout << "X: " << *cameraX << "\tY: " << *cameraY << std::endl;
			}
			else if (!onePressed && sdl_setup->getMainEvent()->key.keysym.sym == SDLK_F2){
				if (!trees.empty()){
					delete trees.back();
					trees.pop_back();
				}
				onePressed = true;
			}
			else if (!onePressed && sdl_setup->getMainEvent()->key.keysym.sym == SDLK_F11){
				saveEnvFile();
				onePressed = true;
			}
		}
		if (sdl_setup->getMainEvent()->type == SDL_KEYUP){
			if (onePressed && sdl_setup->getMainEvent()->key.keysym.sym == SDLK_F1){
				onePressed = false;
			}
			else if (onePressed && sdl_setup->getMainEvent()->key.keysym.sym == SDLK_F2){
				onePressed = false;
			}
			else if (onePressed && sdl_setup->getMainEvent()->key.keysym.sym == SDLK_F11){
				onePressed = false;
			}
		}
	}


		if (sdl_setup->getMainEvent()->type == SDL_KEYDOWN){
			if (!onePressed && sdl_setup->getMainEvent()->key.keysym.sym == SDLK_F12){
				if (game_mode == EDIT){
					game_mode = PLAY;
					std::cout << "Level Creation: OFF" << std::endl;
				}
				else{
					game_mode = EDIT;
					std::cout << "Level Creation: ON" << std::endl;
				}
				onePressed = true;
			}
		}
		if (sdl_setup->getMainEvent()->type == SDL_KEYUP){
			if (onePressed && sdl_setup->getMainEvent()->key.keysym.sym == SDLK_F12){
				onePressed = false;
			}
		}




}

void Environment::loadEnvFromFile(){
	std::ifstream file("data/stageLevel.txt");
	std::string line;
	if (file.is_open()){
		while (file.good()){
			std::getline(file, line);
			std::cout << line << std::endl;
			if (line == "=====BEGIN_FOREST====="){
				env_type = ENV_FOREST;
			}
			else if (line == "=====END_FOREST====="){
				env_type = ENV_NONE;
			}
			else{
				if (env_type == ENV_FOREST){
					std::string prevWord = "";
					std::istringstream iss(line);
					int temp_x, temp_y;
					while (iss){
						std::string word;
						iss >> word;
						if (prevWord == "x:"){
							temp_x = atoi(word.c_str());
						}
						else if (prevWord == "y:"){
							temp_y = atoi(word.c_str());
							trees.push_back(new Tree(sdl_setup, temp_x, temp_y, cameraX, cameraY));
						}
						prevWord = word;
					}
				}
			}
		}
	}
	else{
		std::cout << "Error loading environment" << std::endl;
	}
}

void Environment::saveEnvFile(){
	std::ofstream file;
	file.open("data/stageLevel.txt");
	file << "=====BEGIN_FOREST=====" << std::endl;
	for (std::vector<Tree*>::iterator i = trees.begin(); i != trees.end(); ++i){
		file << "x: " << (*i)->getX() << "\ty: " << (*i)->getY() <<std::endl;
	}
	file << "=====END_FOREST=====" << std::endl;
	file.close();

	std::cout << "LEVEL SAVED" << std::endl;
}

