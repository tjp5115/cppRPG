#include "CollisionRect.h"


CollisionRect::CollisionRect(int x, int y , int w, int h)
{
	offsetX = x;
	offsetY = y;
	setRect(x, y, w, h);
}

CollisionRect::CollisionRect()
{
	offsetX = 0;
	offsetY = 0;
	setRect(0, 0, 0, 0);
}
CollisionRect::~CollisionRect()
{
}

void CollisionRect::setRect(int x, int y, int w, int h){
	collisionRect.x = x + offsetX;
	collisionRect.y = y + offsetY;
	collisionRect.w = w;
	collisionRect.h = h;
}