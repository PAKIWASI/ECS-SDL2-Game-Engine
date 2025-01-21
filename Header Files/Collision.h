#pragma once

#include <SDL.h>
#include "../ECS/ColliderComponent.h"


struct Collision
{
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);        // Axis Alligned Bounding Box

	static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);
};