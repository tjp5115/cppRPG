#pragma once
#include "stdafx.h"
class CollisionRect
{
public:
	CollisionRect(void);
	CollisionRect(int x , int y, int w , int h);
	~CollisionRect();

	SDL_Rect getRect(){ return collisionRect; }
	void setRect(int x , int y, int w, int h);
	void setX(int x){ collisionRect.x = x + offsetX; }
	void setY(int y){ collisionRect.y = y + offsetY; }
private:
	int offsetX,offsetY;
	SDL_Rect collisionRect;
};

