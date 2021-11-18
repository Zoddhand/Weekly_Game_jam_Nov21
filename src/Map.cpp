#include "Map.h"
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

Map::Map()
{
	tilesize = Engine::tileSize;

	/* Tile Init */
	sprite[tile].tex = TextureManager::loadTexture("ASSETS/Tiles/tileset.png");
	sprite[tile].src = { 0,0,Engine::tileSize,Engine::tileSize };
	sprite[tile].dest = { 0,0,Engine::tileSize,Engine::tileSize };
	SDL_QueryTexture(sprite[tile].tex, NULL, NULL, &imagew, &imageh);
	sprite[tile].dest.w = Engine::tileSize;
	sprite[tile].dest.h = Engine::tileSize;
	imagew = imagew / tilesize;
	imageh = imageh / tilesize;

	/* Coin Init */
	sprite[coin].tex = TextureManager::loadTexture("ASSETS/Sprites/Red_coin.png");
	sprite[man].tex = TextureManager::loadTexture("ASSETS/Sprites/man.png");
	sprite[woman].tex = TextureManager::loadTexture("ASSETS/Sprites/woman.png");
	sprite[fire].tex = TextureManager::loadTexture("ASSETS/Sprites/fire.png");
	sprite[smoke].tex = TextureManager::loadTexture("ASSETS/Sprites/smoke.png");
	sprite[cloud].tex = TextureManager::loadTexture("ASSETS/Sprites/cloud.png");
	sprite[cloud].src = { 0,0,32,24 };
	sprite[cloud].dest = { 0,32,32,24 };

	loadLevel(1);
}

Map::~Map()
{

}

void Map::update()
{
	srand ( time(NULL) );
	print("NumOfCit:" << NumOfCit);
}

void Map::render()
{
	
	drawMap(maps);
	drawMap(maps2);
	//drawMap(mapsCol);
	drawMap(mapsItem);
	drawBackground();
	newWin = false;
}

void Map::loadMap(std::string txt, int arr[Engine::mapSizeY][Engine::mapSizeX])
{
	std::fstream fs(txt, std::fstream::in | std::fstream::out);
	if (fs.is_open()) {
		while (!fs.eof()) {
			if (fs.get() == ',') {
				fs.seekp((fs.tellp() - static_cast<std::streampos>(1)));
				fs.put(' ');
				fs.seekp(fs.tellp());
			}
		}
	}
	else
	{
		print("Unable to fix file:" << txt);
		fs.close();
	}

	std::ifstream map;
	map.open(txt);

	if (!map) {
		print("Unable to open file:" << txt);
		exit(1);
	}
	else print("File:" << txt << " Opened Successfully");

	if (map.is_open())
	{
		while (!map.eof())
		{
			for (int i = 0; i < Engine::mapSizeY; ++i) {
				for (int j = 0; j < Engine::mapSizeX; ++j) {
					map >> arr[i][j];
					//std::cout << arr[i][j];
				}
				//std::cout << std::endl;
			}
		}
	}
	map.close();
}

void Map::drawMap(int arr[Engine::mapSizeY][Engine::mapSizeX])
{
	NumOfCit = 0;
	for (int i = 0; i < Camera::vis.y + Camera::offY; i++)
	{
		for (int k = 0; k < Camera::vis.x + Camera::offX; k++)
		{
			sprite[tile].src.y = (arr[i][k] / imagew) * Engine::tileSize;
			sprite[tile].src.x = (arr[i][k] % imagew) * Engine::tileSize;
			sprite[tile].dest.x = (k - Camera::offX) * Engine::tileSize;
			sprite[tile].dest.y = (i - Camera::offY) * Engine::tileSize;
			if (arr[i][k] != -1)
			{
				TextureManager::Draw(sprite[tile].tex, sprite[tile].src, sprite[tile].dest);
			}
			if (arr[i][k] == 40)
			{
				if(newWin)
				{
					if(rand() % 10 + 1 < 5)
					{
						if(rand() % 3 + 1 == 1)
						{
							setItemTile(k,i,1);
						}
						else if(rand() % 3 + 1 == 2)
						{
							setItemTile(k,i,2);
						}
						else if(rand() % 3 + 1 == 3)
						{
							setItemTile(k,i,3);
						}
					}
				}

			}
			if (arr[i][k] == 1)
			{
				NumOfCit += 1;
				sprite[man].dest.x = sprite[tile].dest.x;
				sprite[man].dest.y = sprite[tile].dest.y;
				sprite[man].dest.w = 8;
				sprite[man].dest.h = 8;
				TextureManager::Draw(sprite[man].tex, sprite[man].src, sprite[man].dest);
				TextureManager::FrameUpdate(&sprite[man].src, 2, 0, 0);
			}
			if (arr[i][k] == 2)
			{
				NumOfCit += 1;
				sprite[woman].dest.x = sprite[tile].dest.x;
				sprite[woman].dest.y = sprite[tile].dest.y;
				sprite[woman].dest.w = 8;
				sprite[woman].dest.h = 8;
				TextureManager::Draw(sprite[woman].tex, sprite[woman].src, sprite[woman].dest);
				TextureManager::FrameUpdate(&sprite[woman].src, 2, 0, 0);
			}
			if (arr[i][k] == 3)
			{
				sprite[fire].dest.x = sprite[tile].dest.x;
				sprite[fire].dest.y = sprite[tile].dest.y;
				sprite[fire].dest.w = 8;
				sprite[fire].dest.h = 8;
				TextureManager::Draw(sprite[fire].tex, sprite[fire].src, sprite[fire].dest);
				TextureManager::FrameUpdate(&sprite[fire].src, 2, 0, 0);
			}
			if (arr[i][k] == 57)
			{
				sprite[smoke].dest.x = sprite[tile].dest.x;
				sprite[smoke].dest.y = sprite[tile].dest.y;
				sprite[smoke].dest.w = 8;
				sprite[smoke].dest.h = 8;
				TextureManager::Draw(sprite[smoke].tex, sprite[smoke].src, sprite[smoke].dest);
				TextureManager::FrameUpdate(&sprite[smoke].src, 2, 0, 0);
			}
		}
	}
}

/* Sends the correct file to the loadMap function. */
void Map::loadLevel(int level)
{
	// Create a new string to add levels.
	std::string* ptr = nullptr;
	std::string map1[4] = { "ASSETS/Maps/map1_Tile Layer 1.csv" , "ASSETS/Maps/map1_Tile Layer 2.csv" ,"ASSETS/Maps/map1_Col Layer.csv","ASSETS/Maps/map1_Item Layer.csv"};
	//std::string map2[4] = { "ASSETS/Maps/tiled_example2_Tile Layer 1.csv","ASSETS/Maps/tiled_example2_Tile Layer 2.csv","ASSETS/Maps/tiled_example2_Col Layer.csv","ASSETS/Maps/tiled_example2_Item Layer.csv" };

	switch (level)
	{
	case 1: // level 1
		ptr = map1;
		break;
	case 2:
		//ptr = map2;
		break;
	case 3:
		//ptr = map3;coin
		break;
	default:
		ptr = map1;
	}
	print("level:" << level << " loaded.");

	// Send all our layers for the level we've chosen to be loaded into the map array.
	loadMap(ptr[0], maps); // Our first map to load.
	loadMap(ptr[1], maps2); // Our second map to load.
	loadMap(ptr[2], mapsCol); // Our third map to load.
	loadMap(ptr[3], mapsItem); // Our third map to load.
}

void Map::drawBackground()
{
	sprite[cloud].dest.x += 1;
	if(sprite[cloud].dest.x == Engine::mapSizeX * Engine::tileSize)
		sprite[cloud].dest.x = 0;
	TextureManager::Draw(sprite[cloud].tex, sprite[cloud].src, sprite[cloud].dest);
}

int Map::getColTile(float x, float y)
{
	return mapsCol[(int)y][(int)x];
}

void Map::setColTile(float x, float y, int value)
{
	mapsCol[(int)y][(int)x] = value;
}

int Map::getItemTile(float x, float y)
{
	return mapsItem[(int)y][(int)x];
}

void Map::setItemTile(float x, float y, int value)
{
	mapsItem[(int)y][(int)x] = value;
}

