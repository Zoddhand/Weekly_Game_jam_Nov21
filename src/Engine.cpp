#include "Engine.h"
#include <iostream>
using namespace std;
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"
#include "Camera.h"
#include "Player.h"
#include "Collision.h"
#include "Sound.h"
#include "Timer.h"

float Engine::time;
Engine::Control Engine::cont;
Mix_Chunk* Engine::effect[10];

SDL_Window* Engine::window = nullptr;
SDL_Renderer* Engine::renderer = nullptr;
SDL_Event Engine::event;
Camera* camera = nullptr;
Map* map = nullptr;
Player* player = nullptr;
GameObject* ladder = nullptr;
Collision* col = nullptr;
Sound* sound = nullptr;

Engine::Engine(const char* title, int posX, int posY, bool fullscreen)
{
	int scale = 3.0f;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_JOYSTICK) < 0)
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

	
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "SDL_mixer could not initialize! SDL_mixer Error: %s\n";
		std::cout << Mix_GetError();
	}
	Bg = Sound::loadBackground("ASSETS/Sound/Intergalactic Odyssey.ogg");
	Engine::effect[0] = Sound::loadEffect("ASSETS/Sound/Retro_8-Bit_Game-Bomb_Explosion_09.wav");
	Engine::effect[1] = Sound::loadEffect("ASSETS/Sound/walking.wav");
	Engine::effect[2] = Sound::loadEffect("ASSETS/Sound/Retro_8-Bit_Game-Digitalized_Voice_Scream_01.wav");
	Engine::effect[3] = Sound::loadEffect("ASSETS/Sound/Retro_8-Bit_Game-Pickup_Object_Item_Coin_18.wav");
	Engine::effect[4] = Sound::loadEffect("ASSETS/Sound/Retro_8-Bit_Game-Bomb_Explosion_17.wav");


	controllerInit();

	camera = new Camera();
	map = new Map();
	player = new Player("ASSETS/Sprites/player.png", 10, 260);
	ladder = new GameObject("ASSETS/Sprites/ladder.png",40,100,8,8*27);
	col = new Collision(map);
	sound = new Sound();
}

Engine::~Engine()
{
	
}

void Engine::handle_event(float time)
{
	
	Controller();
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
			//map->loadLevel(1);
			map->newFire = true;
			Sound::playEffect(Engine::effect[0]);
			//style = 0;
			break;
		case SDLK_2:
			//map->loadLevel(2);
			style = 1;
			break;
		case SDLK_a:
			
			break;
		}
	}
	player->Movement(style);
		if(!player->hitFire)
	{
		if (keys[SDL_SCANCODE_A]  && !player->isOnGround || cont.AButton && !player->isOnGround) {
			player->smoke(map);
			player->allowExt = false;
		}
		if(!keys[SDL_SCANCODE_A])
			player->allowExt = true;	
		if(player->isOnGround)
			player->setGravity(true);

		if(col->rectCol(player->dest,ladder->dest))
		{
			if (keys[SDL_SCANCODE_A]  && player->isOnGround == true || cont.AButton && player->isOnGround == true) {	
				ladder->setXpos(*player->getXpos());
			}
			else if(keys[SDL_SCANCODE_UP] || cont.Up)
			{
				player->setGravity(false);
				player->setXpos(*ladder->getXpos());
			}
			else
			{
				ladder->setXpos(round(*ladder->getXpos()));
			}
		
		}
	}

}

void Engine::update()
{
	playBG();
	col->collide(*player->getXpos(), *player->getYpos(), *player->getXvel(), *player->getYvel());
	player->update(map);
	ladder->update();
	camera->update(*player->getXpos(), *player->getYpos());
	map->update();
}

void Engine::render()
{
	SDL_RenderClear(renderer);
	map->render();
	ladder->render();
	player->render();
	//SDL_RenderDrawRect(renderer, &player->dest);
	hud();
	SDL_RenderPresent(renderer);
	sounds();
}

void Engine::playBG()
{
	Sound::setVolume(60);
	Sound::playBackground(Bg,1);
}

void Engine::sounds()
{
	if(i != map->NumOfCit)
	{
		//Sound::playEffect(Engine::effect[3]);
		print(i);
	}	
	i = map->NumOfCit;
}