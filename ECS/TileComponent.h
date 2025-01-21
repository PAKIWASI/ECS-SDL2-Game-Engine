#pragma once

#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"

class TileComponent : public Component
{
public:                           // each tile has an Entity, TransformComp and SpriteComp
	TransformComponent* transform;
	SpriteComponent* sprite;

	SDL_Rect tileRect;
	int tileID = 0; // water, dirt, grass
	const char* path;      

	TileComponent() = default; //If some user-defined constructors are present, the user may still force the automatic generation of a default constructor by the compiler

	TileComponent(int x, int y, int w, int h, int id)
	{
		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;
		tileID = id;

		switch (tileID)
		{
		case 0: path = "assets/water.png"; break;
		case 1: path = "assets/dirt.png"; break;
		case 2: path = "assets/grass.png"; break;
		}
	}

	~TileComponent()
	{
		sprite->~SpriteComponent();  // didn't do             !!!
	}

	void init()
	{                                                                                        // scale
		entity->addComponent<TransformComponent>((float)tileRect.x, (float)tileRect.y, tileRect.w, tileRect.h, 1);
		transform = &entity->getComponent<TransformComponent>();

		entity->addComponent<SpriteComponent>(path);
		sprite = &entity->getComponent<SpriteComponent>();
	}
};
