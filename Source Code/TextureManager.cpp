#include "../Header Files/TextureManager.h"


SDL_Texture* TextureManager::LoadTexture(const char* fileName)
{
	SDL_Surface* tempSurface = IMG_Load(fileName);

	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);

	SDL_FreeSurface(tempSurface);

	return tex;
}

void TextureManager::draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect des)
{
	SDL_RenderCopy(Game::renderer, tex, &src, &des);
}
