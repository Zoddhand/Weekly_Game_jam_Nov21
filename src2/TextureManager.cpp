#include "TextureManager.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>


TextureManager::TextureManager()
{
}

SDL_Texture* TextureManager::loadTexture(const char* filename, bool message)
{
	SDL_Surface* tmpSurface = IMG_Load(filename);
	if (tmpSurface == NULL)
	{
		print("Error Loading tmpSurface: " << filename);
	}
	else if (message) std::cout << filename << " Loaded Successfully" << std::endl;

	SDL_Texture* text = SDL_CreateTextureFromSurface(Engine::renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	return text;
}

void TextureManager::Draw(SDL_Texture* text, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Engine::renderer, text, &src, &dest, NULL, NULL, flip);
}

void TextureManager::DrawRect(SDL_Rect dest)
{
	SDL_RenderDrawRect(Engine::renderer, &dest);
}

void TextureManager::FrameUpdate(SDL_Rect* src, int framenum, int x, int y)
{
	Uint32 ticks = SDL_GetTicks();
	Uint32 sprite = (ticks / 100) % framenum;
	src->x = x + sprite * src->w;
	src->y = y;
}
TTF_Font* TextureManager::LoadFont(const char* file, int ptsize)
{
	if (TTF_Init() == -1)
	{
		print("Error, Coult not load SDL_TTF\n");
	}

	TTF_Font* font = TTF_OpenFont(file, ptsize);

	if (font == NULL)
	{
		std::cout << "Could not load Font" << file;
	}

	return font;
}

void TextureManager::DrawFont(TTF_Font* font, const char* mess, SDL_Color textColor, SDL_Rect dest)
{

	SDL_Surface* message = TTF_RenderText_Solid(font, mess, textColor);

	//If there was an error in rendering the text
	if (message == NULL)
	{
		print("Font Surface Failed.");
	}
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Engine::renderer, message);
	SDL_FreeSurface(message);
	SDL_RenderCopy(Engine::renderer, tex, NULL, &dest);
}