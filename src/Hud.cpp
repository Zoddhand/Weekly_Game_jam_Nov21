#include "Engine.h"
#include "TextureManager.h"
#include "Player.h"
#include <iostream>
#include <string>
using namespace std;

void Engine::hud()
{

	//HIGH SCORE

	SDL_Rect HSdest = { screen_width/2 - 16, 0, 64, 12 };
	HSdest.y = 0;
	std::string text = "High  Score";
	//text += std::to_string(0);
	const char* c = text.c_str();
	TextureManager::DrawFont(font, c, { 255,255,50}, HSdest);

	
	//HIGH SCORE #

	SDL_Rect Ndest = { screen_width/2 - 16, 0, 64, 12 };
	Ndest.y = 8;
	char buffer[256]; sprintf(buffer, "%06d", Player::highscore);
	string str2(buffer);
	c = str2.c_str();
	TextureManager::DrawFont(font, c, { 255,255,255}, Ndest);

		
	//SCORE #

	SDL_Rect Sdest = { 0, 0, 64, 12 };
	Sdest.y = 8;
	char buffer2[256]; sprintf(buffer2, "%06d", Player::coins);
	string str(buffer2);
	c = str.c_str();
	TextureManager::DrawFont(font, c, { 255,255,255}, Sdest);
}