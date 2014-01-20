#pragma once
#include "stdafx.h"
#include "CollisionRect.h"
class Sprite
{
public:
	Sprite(SDL_Renderer * passed_renderer, const char* FilePath, int x, int y, int h, int w, float *passed_cameraX, float *passed_cameraY, CollisionRect p_collisionRect);
	~Sprite();

	void Draw();
	
	float getX();
	float getY();
	
	void setX(float x);
	void setY(float y);

	void setPosition(float x, float y);

	void setOrigin(float x, float y);

	float getWidth();
	float getHeight();

	void setWidth(int w);
	void setHeight(int h);
	void playAnimation(int beginFrame, int endFrame, int row, float speed);
	void setupAnimation(int x, int y);

	CollisionRect getCollisionRext(){ return collisionRect; }

	void drawSteady();

	bool isColliding(CollisionRect theCollider);

	CollisionRect getCollisionRect(){ return collisionRect; }

	SDL_Rect getPositionRext(){ return rect; }
private:
	
	CollisionRect collisionRect;

	float *cameraX;
	float *cameraY;

	float origin_x;
	float origin_y;
	float xPos;
	float yPos;

	int image_width;
	int image_height;

	int amount_frame_x;
	int amount_frame_y;

	int currentFrame;
	int animationDelay;
	SDL_Rect crop;
	SDL_Texture* image;
	SDL_Texture* collImg;

	SDL_Rect rect;
	SDL_Renderer *renderer;

	SDL_Rect camera;
};

