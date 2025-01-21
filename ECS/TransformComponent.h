#pragma once

#include "Components.h"
#include "Vector2D.h"


struct TransformComponent : public Component
{
	Vector2D position;
	Vector2D velocity;

	int speed = 3;

	int height = 32, width = 32;
	int scale = 1;
	
	TransformComponent()
	{
		position.Zero();
	}

	TransformComponent(int scale)
	{
		position.Zero();
		this->scale = scale;
	}

	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	TransformComponent(float x, float y, int w, int h, int scale)
	{
		position.x = x;
		position.y = y;
		width = w;
		height = h;
		this->scale = scale;
	}

	void init() override
	{
		velocity.Zero();
	}

	void update() override
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed; // if -1 * 3 ->move up 3 pixels
	}
};
