#include "SDL_Setup.h"

SDL_Setup::SDL_Setup(bool * quit, int passed_screenWidth, int passed_screenHeight)
{
	screenWidth = passed_screenWidth;
	screenHeight = passed_screenHeight;
	SDL_Init(SDL_INIT_VIDEO);
	window = NULL;
	window = SDL_CreateWindow("Tyler's RPG", 100, 100, screenWidth, screenHeight, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
	if (window == NULL){
		std::cout << "failed to create window" << std::endl;
		*quit = true;
	}

	renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	mainEvent = new SDL_Event();
}


SDL_Setup::~SDL_Setup()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	delete mainEvent;
}

SDL_Renderer* SDL_Setup::getRenderer(){
	return renderer;
}

SDL_Event* SDL_Setup::getMainEvent(){
	return mainEvent;
}


void SDL_Setup::begin(){
	SDL_PollEvent(getMainEvent());
	SDL_RenderClear(getRenderer());
}

void SDL_Setup::end(){
	SDL_RenderPresent(getRenderer());
}