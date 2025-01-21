#pragma once

#include "Components.h"
#include "../Header Files/TextureManager.h"
#include <SDL.h>


class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcR, desR;
public:
	SpriteComponent() = default;

	SpriteComponent(const char* path)
	{
		setTex(path);
	}
	
	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void init() override
	{               
		transform = &entity->getComponent<TransformComponent>();

		srcR.x = srcR.y = 0; // 0,0 to 32,32 -> whole image 
		srcR.w = transform->width;
		srcR.h = transform->height;
		desR.w = transform->width * transform->scale; // 64,64 top left
		desR.h = transform->height * transform->scale;
	}
	void update() override
	{
		desR.x = static_cast<int>(transform->position.x); // rects are ints
		desR.y = static_cast<int>(transform->position.y);
	}
	void draw() override
	{
		TextureManager::draw(texture, srcR, desR);
	}

	void setTex(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}
};