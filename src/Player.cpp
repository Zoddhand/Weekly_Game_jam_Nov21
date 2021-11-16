#include "Player.h"
#include "Collision.h"
#include <iostream>
#include "Sound.h"

bool Player::isOnGround;
int Player::coins = 0;

Player::Player(const char* texturesheet, float x, float y) : GameObject(texturesheet,x,y,8,8)
{
	frame.num = 2;
	frame.offset_x = 0;
	frame.offset_y = 8;
	src.h = Engine::tileSize *2;
	dest.h = Engine::tileSize *2;

	src.x = 0;
	src.y = 0;
	src.w = 12;
	src.h = Engine::tileSize *2;
	dest.x = pos.x;
	dest.y = pos.y;
	dest.w = 12;
	dest.h = Engine::tileSize *2;
}

void Player::Movement(int style)
{
	if (style == RPG)
	{
		vel.y += 20.0f * Engine::time; // Gravity.
		if(!gravity)
		{
			if (keys[SDL_SCANCODE_DOWN] || Engine::cont.Down) {
				moveDown();
			}
			else if (keys[SDL_SCANCODE_UP] || Engine::cont.Up) {
				moveUp();
			}
			else vel.y = 0; frame.num = 1;
		}
		if(isOnGround)
		{
			if (keys[SDL_SCANCODE_RIGHT] || Engine::cont.Right) {
				moveRight(RPG);
			}
			else if (keys[SDL_SCANCODE_LEFT] || Engine::cont.Left) {
				moveLeft(RPG);
			}
			else vel.x = 0; frame.num = 1;
		}
		

		if (vel.x == 0 && vel.y == 0)
			frame.num = 1;
		else frame.num = 2;
	}

	if (*getXpos() <= 0)
		setXpos((int)* getXpos());
	else if (*getXpos() >= Engine::mapSizeX - 1)
		setXpos((int)* getXpos());
	if (*getYpos() <= 0)
		setYpos((int)* getYpos());
	else if (*getYpos() >= Engine::mapSizeY - 2)
		setYpos((int)* getYpos());
}

void Player::update(Map* map)
{
	GameObject::update();
	Collect(map);
}
void Player::setGravity(bool a)
{
	gravity = a;
}

bool Player::getGravity()
{
	return gravity;
}

void Player::Collect(Map* map)
{
	if (Collision::ItemCollect(map, *getXpos(), *getYpos(), 1, 0))
	{
		// Do stuff if we collect a coin.
		Sound::playEffect(Engine::effect[0]);
		Player::coins += 100;
	}
	if (Collision::ItemCollect(map, *getXpos(), *getYpos(), 2, 0))
	{
		// Do stuff if we collect a coin.
		Sound::playEffect(Engine::effect[0]);
		Player::coins += 100;
	}
	if (Collision::ItemCollect(map, *getXpos(), *getYpos(), 3, 3))
	{
		pos.y = pos.y +1;
		// Do stuff if we collect a coin.
		Sound::playEffect(Engine::effect[0]);
		Player::coins -= 100;
	}
}

void Player::moveLeft(int style)
{
	if (style == Platformer)
	{
		vel.x += (isOnGround ? -25.0f : -15.0f) * Engine::time;
	}
	else if (style == RPG)
	{
		vel.x = -15.0f;
	}
	frame.flip = SDL_FLIP_HORIZONTAL;
	frame.offset_y = 16;
}

void Player::moveRight(int style)
{
	if (style == Platformer)
	{
		vel.x += (isOnGround ? 25.0f : 15.0f) * Engine::time;
	}
	else if (style == RPG)
	{
		vel.x = 15.0f;
	}
	frame.flip = SDL_FLIP_NONE;
	frame.offset_y = 16;
}

void Player::moveUp()
{
	vel.y = -15.0f;
	frame.offset_y = 32;
}

void Player::moveDown()
{
	vel.y = 15.0f;
	frame.offset_y = 0;
}

void Player::jump()
{
	if (vel.y == 0 && isOnGround)
	{
		vel.y = -12.0f;
	}
}

void Player::smoke(Map* map)
{
	map->setItemTile(pos.x,pos.y-1,57);
}
