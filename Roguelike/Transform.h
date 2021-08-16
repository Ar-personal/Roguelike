#pragma once
#include "Vector2D.h"
struct Transform
{
	float xpos = 0;
	float ypos = 0;
	float speed = 3;
	Vector2D velocity = Vector2D();
	Vector2D position = Vector2D();
};