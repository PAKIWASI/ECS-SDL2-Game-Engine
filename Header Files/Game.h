#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>


// constants

// system core
const int FPS = 30;
const int frameDelay = 1000 / FPS;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 640; // multiple of 32

// game elements


class Game
{
private:
	bool isRunning;
	SDL_Window* window;
public:
	Game();
	~Game();

	bool init();
	void quit();
	
	void handleEvents();
	void update();
	void render();

	bool running() { return isRunning; }

	static SDL_Renderer* renderer; // static member variables in a class are shared by the objects.There cannot be multiple copies of the same static variables for different objects
	static SDL_Event event;   
};