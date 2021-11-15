#include "Engine.h"
#include "Map.h"
#include "Camera.h"
#include <iostream>
using namespace std;

float Engine::time;
Engine::Control Engine::cont;
Mix_Chunk* Engine::effect[10];

SDL_Window* Engine::window = nullptr;
SDL_Renderer* Engine::renderer = nullptr;
SDL_Event Engine::event;
Camera* camera = nullptr;
Map* map = nullptr;

Engine::Engine(const char* title, int posX, int posY, bool fullscreen)
{
	int scale = 3.0f;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) < 0)
	{
		print("Error: SDL NOT INITIALIZED -" << SDL_GetError())
	}
	else print("Subsystems Started");

	window = SDL_CreateWindow(title, posX, posY, screen_width, screen_height, fullscreen);
	if (window == NULL) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Window did not Create.", NULL);
	}
	SDL_SetWindowSize(window, screen_width * scale, screen_height * scale);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Renderer did not Create.", NULL);
	}
	SDL_RenderSetScale(renderer, scale, scale);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	camera = new Camera();
	map = new Map();

}

Engine::~Engine()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Engine::handle_event(float time)
{
	/* gets items in the event queue */
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		print("SDL Successfully Quit!");
		break;
	}

	/* Get key presses */
	if (Engine::event.type == SDL_KEYDOWN)
	{
		switch (Engine::event.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			run = false;
			break;
		case SDLK_1:
			style = 0;
			break;
		case SDLK_2:
			style = 1;
			break;
		}
	}
}

void Engine::update()
{
}

void Engine::render()
{
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

void Engine::playBG()
{
}