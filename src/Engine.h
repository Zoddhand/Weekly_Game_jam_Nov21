#pragma once
#define print(x) std::cout << x << std::endl;
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>



class Engine
{
private:
	//Sound Variables Set enum to sound effect ie. jump.
	Mix_Music* Bg = NULL;
	enum { E1, E2 };
	int style = 1;
	struct Control
	{
		bool Up;
		bool Down;
		bool Left;
		bool Right;
		bool Start;
		bool Back;
		bool LeftShoulder;
		bool RightShoulder;
		bool AButton;
		bool BButton;
		bool XButton;
		bool YButton;
		int16_t StickX;
		int16_t StickY;
	};

public:
	Engine(const char*, int, int, bool);
	~Engine();
	//Public Variables.
	bool run = true;
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	//Static Variables.
	static SDL_Window* window;
	static SDL_Event event;
	static SDL_Renderer* renderer;
	static const int tileSize = 8;
	static const int screen_width = 240;
	static const int screen_height = 320;
	static const int mapSizeX = 30;
	static const int mapSizeY = 40;
	static float time;
	static Control cont;
	static Mix_Chunk* effect[10];

	//Static Functions.

	//Functions.
	void handle_event(float);
	void update();
	void render();
	void playBG();
	void Controller();
	void controllerInit();
	void hud();
};
