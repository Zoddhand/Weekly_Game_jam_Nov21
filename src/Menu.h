#pragma once
#include "Engine.h"
#include "TextureManager.h"

class Menu
{
	Menu();

	SDL_Rect* dest = nullptr;
	SDL_Texture* tex[3];
	enum{ menu, credit, option };

	void drawMenu();
	void drawCredits();
	void drawOptions();
};

