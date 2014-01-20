#include "Cmain.h"


Cmain::Cmain(int passed_screenWidth, int passed_screenHeight)
{
	quit = false; 
	cameraX = 0;
	cameraY = 0;

	sdl_setup = NULL;
	sdl_setup = new SDL_Setup(&quit, passed_screenWidth, passed_screenHeight);

	forestArea = NULL;
	forestArea = new Environment(sdl_setup, passed_screenWidth, passed_screenHeight, &cameraX, &cameraY);

	bob = NULL;
	bob = new mainCharacter(sdl_setup,&mouseX,&mouseY,&cameraX,&cameraY,forestArea);

}


Cmain::~Cmain()
{
	delete sdl_setup;
	delete bob;
}


void Cmain::GameLoop(void){
	while (!quit && sdl_setup->getMainEvent()->type != SDL_QUIT){
		//perform the begining loop functions
		SDL_GetMouseState( & mouseX, &mouseY);
		sdl_setup->begin();

		//draw sprites
		forestArea->drawBack();

		bob->draw();
		bob->update();

		forestArea->drawFront();
		
		forestArea->update();
		//run the end main loop routines
		sdl_setup->end();
	}
}


