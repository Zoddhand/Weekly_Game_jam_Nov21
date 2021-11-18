#include "Player.h"
#include "Collision.h"
#include <iostream>
#include "Sound.h"

bool Player::isOnGround;
int Player::coins = 0;
int Player::highscore = 0;
int Player::health = 3;

Player::Player(const char* texturesheet, float x, float y) : GameObject(texturesheet,x,y,8,8)
{
	frame.num = 2;
	frame.offset_x = 0;
	frame.offset_y = 16;
	src.h = Engine::tileSize *2;
	dest.h = Engine::tileSize *2;

	src.x = 0;
	src.y = 0;
	src.w = 10;
	src.h = Engine::tileSize *2;
	dest.x = pos.x;
	dest.y = pos.y;
	dest.w = 10;
	dest.h = Engine::tileSize *2;
}
Player::~Player()
{
	print("destroyed Player");
}

void Player::Movement(int style)
{
	vel.y += 20.0f * Engine::time; // Gravity.
	if (style == RPG)
	{
				
		if (vel.x == 0 && vel.y == 0)
		{
			frame.num = 1;
		}	
		else frame.num = 2;
		if(!gravity)
		{
			if (keys[SDL_SCANCODE_DOWN] || Engine::cont.Down) {
				moveDown();
			}
			else if (keys[SDL_SCANCODE_UP] || Engine::cont.Up) {
				moveUp();
			}
			else 
			{
				vel.y = 0; 
				frame.num = 1;
			}	
		}
		if(isOnGround)
		{
			if (keys[SDL_SCANCODE_RIGHT] || Engine::cont.Right) {
				Sound::playEffect(Engine::effect[5]);
				moveRight(RPG);
			}
			else if (keys[SDL_SCANCODE_LEFT] || Engine::cont.Left) {
				Sound::playEffect(Engine::effect[5]);
				moveLeft(RPG);
			}
			else 
			{
				vel.x = 0; 
				frame.num = 1;
			}
			vel.x += -3.0f * vel.x * Engine::time; // Slows us to a stop.
			if (fabs(vel.x) < 0.01f)
				vel.x = 0.0f;
		}
	}

	// SCREEN BOUNDS.
	if (*getXpos() <= 0)
		setXpos((int)* getXpos());
	else if (*getXpos() >= Engine::mapSizeX - 1)
		setXpos((int)* getXpos());
	if (*getYpos() <= 0)
		setYpos((int)* getYpos());
	else if (*getYpos() >= Engine::mapSizeY - 2)
		setYpos((int)* getYpos());
	if (*getYpos() <= 12)
	{
		pos.y = 12;
	}
}

void Player::update(Map* map)
{
	Collect(map);
	if(isOnGround)
		hitFire = false;
	GameObject::update();
	if(coins <= 0)
		coins = 0;
	if(health == 0)
	{
		coins = 0;
	}
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
		Sound::playEffect(Engine::effect[3]);
		Player::coins += 100;
	}
	if (Collision::ItemCollect(map, *getXpos(), *getYpos(), 2, 0))
	{
		// Do stuff if we collect a coin.
		Sound::playEffect(Engine::effect[3]);
		Player::coins += 100;
	}
	if (Collision::ItemCollect(map, *getXpos(), *getYpos(), 3, 3))
	{
		hitFire = true;
		health -= 1;
		pos.y = pos.y +1;
		pos.x = pos.x +1;
		setGravity(true);
		isOnGround = false;
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
	//Sound::playEffect(Engine::effect[1]);
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
	//Sound::playEffect(Engine::effect[1]);
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
	if(map->getItemTile(pos.x,pos.y-1) == 11 || map->getItemTile(pos.x,pos.y-1) == 3)
	{
		if(allowExt)
		{
			coins += 100;
			Sound::playEffect(Engine::effect[4]);
			map->setItemTile(pos.x,pos.y-1,57);
			map->setItemTile(pos.x,pos.y-2,57);
		}
	}
	else if(map->getItemTile(pos.x,pos.y-2) == 11  || map->getItemTile(pos.x,pos.y-1) == 3)
	{
		if(allowExt)
		{
			coins += 100;
			Sound::playEffect(Engine::effect[4]);
			map->setItemTile(pos.x,pos.y-2,57);
			map->setItemTile(pos.x,pos.y-3,57);
		}
	}
}
