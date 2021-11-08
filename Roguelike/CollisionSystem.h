#pragma once
#include "System.h"
#include <SDL_rect.h>

class CollisionSystem : public System
{
public:
	void Init();

	void Update();

	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
};
