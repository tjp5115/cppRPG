#include "mainCharacter.h"



mainCharacter::mainCharacter(SDL_Setup *passed_sdl_setup, int *passed_mouseX, int *passed_mouseY, float *passed_cameraX, float *passed_cameraY,Environment *p_environment)
{
	SPEED = 5.2f;
	cameraX = passed_cameraX;
	cameraY = passed_cameraY;

	follow = false;
	follow_point_x = *passed_mouseX;
	follow_point_y = *passed_mouseY;

	environment = p_environment;

	mouseX = passed_mouseX;
	mouseY = passed_mouseY;

	timeCheck = SDL_GetTicks();
	debugTime = SDL_GetTicks();
	distance = 0;

	stopAnimation = false;

	sdl_setup = passed_sdl_setup;

	bob = new Sprite(sdl_setup->getRenderer(), "data/tom.png", 300, 250, 130, 130,cameraX,cameraY,CollisionRect(137,112,60,35));

	bob->setY(bob->getY());
	bob->setX(bob->getX());

	bob->setupAnimation(4, 4);
}


mainCharacter::~mainCharacter()
{
	delete bob;
}

void mainCharacter::draw(){
		bob->drawSteady();
}

void mainCharacter::updateAnimation(){
	float angle = atan2(follow_point_y - *cameraY, follow_point_x -*cameraX );
	angle = angle * (180 / 3.14) + 180;
	if (!stopAnimation){
		if (angle > 225 && angle <= 315){
			//up
			if (distance > 15){
				bob->playAnimation(0, 3, 3, 300);
			}
			else{
				bob->playAnimation(1, 1, 3, 300);
			}
		}
		else if ((angle <= 360 && angle > 315) || (angle >= 0 && angle <= 45)) {
			//right
			if (distance > 15){
				bob->playAnimation(0, 3, 2, 300);
			}
			else{
				bob->playAnimation(1, 1, 2, 300);
			}
		}
		else if (angle > 45 && angle <= 135){
			//down
			if (distance > 15){
				bob->playAnimation(0, 3, 0, 300);
			}
			else{
				bob->playAnimation(1, 1, 0, 300);
			}
		}
		else if (angle > 135 && angle <= 225){
			//left
			if (distance > 15){
				bob->playAnimation(0, 3, 1, 300);
			}
			else{
				bob->playAnimation(1, 1, 1, 300);
			}
		}
	}
}

void mainCharacter::updateControls(){

	if (sdl_setup->getMainEvent()->type == SDL_MOUSEBUTTONDOWN || sdl_setup->getMainEvent()->type == SDL_MOUSEMOTION){
		if (sdl_setup->getMainEvent()->button.button == SDL_BUTTON_LEFT){
			follow_point_x = *cameraX - *mouseX+ 300;
			follow_point_y = *cameraY - *mouseY + 250;
			follow = true;


		}
	}


	if (timeCheck + 7 < SDL_GetTicks() && follow){

		distance = getDistance(*cameraX, *cameraY,follow_point_x, follow_point_y);
		if (distance == 0){
			stopAnimation = true;
		}
		else{
			stopAnimation = false;
		}
		if (distance > 15){
			bool collide = false;
			std::vector<Tree*> trees = environment->getTrees();
			for (int i = 0; i < trees.size(); ++i){
				if (bob->isColliding( trees[i]->getTrunk()->getCollisionRect() ) ) {
					if (follow_point_x < *cameraX){
						*cameraX += 1;
					}
					if (follow_point_x > *cameraX){
						*cameraX -= 1;
					}
					if (follow_point_y < *cameraY){
						*cameraY += 1;
					}
					if (follow_point_y > *cameraY){
						*cameraY -= 1;
					}
					follow_point_x = *cameraX;
					follow_point_y = *cameraY;
					collide = true;
					stopAnimation = true;
				}
			}
			if (!collide){
				if (*cameraY != int(follow_point_y)){
					*cameraY = *cameraY - (((*cameraY - follow_point_y) / distance)*SPEED);
				}
				if (*cameraX != int(follow_point_x)){
					*cameraX = *cameraX - (((*cameraX - follow_point_x) / distance)*SPEED);
				}
			}
		}
		timeCheck = SDL_GetTicks();
	}
	if (debugTime + 5000 < SDL_GetTicks()){
		std::cout << "MP_CAMERA:\t  X: " << *cameraX << "\tY: " << *cameraY << std::endl;
		std::cout << "MP_FOLLOW:\t  X: " << follow_point_x << "\tY: " << follow_point_y << std::endl;
		std::cout << "MP_MOUSE:\t X: " << *mouseX << "\tY: " << *mouseY << std::endl;
		std::cout << "DISTANCE: " << distance << std::endl;
		debugTime = SDL_GetTicks();
	}
}

void mainCharacter::update(){

	updateAnimation();
	updateControls();

}
float mainCharacter::getDistance(int x1, int y1, int x2, int y2){
	float diffx = x1 - x2;
	float diffy = y1 - y2;

	return (float)sqrt((diffx * diffx) + (diffy * diffy));
}