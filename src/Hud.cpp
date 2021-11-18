#include "Engine.h"
#include <SDL2/SDL_ttf.h>
#include "TextureManager.h"
#include "Player.h"
#include <iostream>
#include <string>

void Engine::hud()
{
	TTF_Font* font;
	SDL_Rect dest = { 0, 0, 32, 8 };
	dest.y = screen_height - dest.h;
	font = TextureManager::LoadFont("ASSETS/Fonts/ARCADECLASSIC.TTF",16);

	//Text Example. Create a string then add our variable to it.
	std::string text = "Coins: ";
	text += std::to_string(Player::coins);
	const char* c = text.c_str();
	TextureManager::DrawFont(font, c, { 255,255,50}, dest);

	//HIGH SCORE

	SDL_Rect HSdest = { screen_width/2 - 16, 0, 64, 12 };
	HSdest.y = 0;
	text = "High  Score";
	//text += std::to_string(0);
	c = text.c_str();
	TextureManager::DrawFont(font, c, { 255,255,50}, HSdest);

	
	//HIGH SCORE #

	SDL_Rect Ndest = { screen_width/2 - 16, 0, 64, 12 };
	Ndest.y = 8;
	text = "";
	text += std::to_string(100000);
	c = text.c_str();
	TextureManager::DrawFont(font, c, { 255,255,255}, Ndest);

		
	//SCORE #

	SDL_Rect Sdest = { 0, 0, 64, 12 };
	Sdest.y = 8;
	text = "";
	text += std::to_string(Player::coins+100000);
	c = text.c_str();
	TextureManager::DrawFont(font, c, { 255,255,255}, Sdest);
}