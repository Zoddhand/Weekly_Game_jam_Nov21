#include "Menu.h"

Menu::Menu()
{
	tex[menu] = TextureManager::loadTexture("/Assets/Menu/Menu.png");
	tex[credit] = TextureManager::loadTexture("/Assets/Menu/Credits.png");
	tex[option] = TextureManager::loadTexture("/Assets/Menu/Options.png");
}

void Menu::drawMenu()
{

}

void Menu::drawCredits()
{

}

void Menu::drawOptions()
{

}
