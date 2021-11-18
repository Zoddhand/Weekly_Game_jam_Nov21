#pragma once
#include "GameObject.h"
#include "Map.h"
class Player :
	public GameObject
{
private:
	enum{ Platformer, RPG };
	const Uint8* keys = SDL_GetKeyboardState(NULL);
public:
	static bool isOnGround;
	static int coins;
	static int highscore;
	bool gravity = true;
	bool hitFire;
	static int health;
	bool allowExt = true;

	Player(const char* texturesheet, float x, float y);
	void Movement(int);
	void Collect(Map* map);
	virtual ~Player();
	virtual void update(Map* map);
	virtual void moveLeft(int style);
	virtual void moveRight(int style);
	virtual void moveUp();
	virtual void moveDown();
	void setGravity(bool a);
	bool getGravity();
	void jump();
	void smoke(Map*);
};

