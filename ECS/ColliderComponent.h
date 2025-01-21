#pragma once

#include <string>
#include <SDL.h>
#include "Components.h"

struct ColliderComponent : public Component
{
	SDL_Rect collider;
	std::string tag;

	TransformComponent* transform;

	ColliderComponent(std::string tag)
	{
		this->tag = tag;
	}

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>()) // if the colliding entity doesnot yet have a transform comp, give it one
			entity->addComponent<TransformComponent>();
		
		transform = &entity->getComponent<TransformComponent>(); // store Transform comp of entity(to cehck collition) in transform var
	}

	void update() override
	{
		collider.x = static_cast<int>(transform->position.x); // float to int
		collider.y = static_cast<int>(transform->position.y);
		collider.w = transform->width * transform->scale;
		collider.h = transform->height * transform->scale;
	}
};