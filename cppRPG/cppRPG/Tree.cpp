#include "Tree.h"


Tree::Tree(SDL_Setup *p_sdl_setup,int p_x,int p_y,float *p_cameraX, float *p_cameraY)
{		
	cameraX = p_cameraX;
	cameraY = p_cameraY;
	x = p_x;
	y = p_y;
	sdl_setup = NULL;
	sdl_setup = p_sdl_setup;

	trunk = new Sprite(sdl_setup->getRenderer(), "data/environment/trunk.png", x, y, 43, 145, cameraX, cameraY,CollisionRect(0,100,43,45));
	crown = new Sprite(sdl_setup->getRenderer(), "data/environment/crown.png", x-75, y-115, 183, 165, cameraX, cameraY,CollisionRect());
	//std::cout << "trunk collRect: "<<trunk->getCollisionRect().getRect().y << std::endl;
}


Tree::~Tree()
{
	delete trunk;
	delete crown;
}

void Tree::drawTrunk(){
	if (100 <= trunk->getPositionRext().y  - *cameraY){
		trunk->Draw();
	}
}

void Tree::drawCrown(){
	if (100 >= trunk->getPositionRext().y - *cameraY){
		trunk->Draw();
	}
	crown->Draw();

}