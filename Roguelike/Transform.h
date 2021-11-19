#pragma once
#include "Vector2D.h"
struct Transform
{
	float xpos = 0;
	float ypos = 0;
	bool canMove;
	float speed = 1.0;
	float startX;
	float startY;
	bool init = false;

	Vector2D velocity = Vector2D();
	Vector2D position = Vector2D();
};