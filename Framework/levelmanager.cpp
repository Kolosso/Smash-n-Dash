
#include "levelmanager.h"

#include "backbuffer.h"
#include "tile.h"



LevelManager::LevelManager()
: levelWidth(25)
, levelHeight(19)
, background('O')
, platform('W')
, scoretile('S')
{

}

LevelManager::~LevelManager()
{
	// delete tiles
	for (int i = 0; i < tiles.size(); i++)
	{
		delete tiles[i];
		tiles[i] = 0;
	}

	std::vector<Tile*>().swap(tiles);

	mapFile.clear();
	mapFile.close();
}

bool
LevelManager::Initialise()
{
	ReadMapFile();

	return(true);
}

void
LevelManager::ReadMapFile()
{
	mapFile.open("assets\\maplayout.txt");
}

void
LevelManager::CreateLevel(BackBuffer* m_pBackBuffer, b2World* gameWorld)
{
	char tileID;

	for (int h = 0; h < levelHeight; h++)
	{
		for (int w = 0; w < levelWidth; w++)
		{
			mapFile >> (tileID);
			if (tileID == background)
			{
				// Sprites from online tutorial. www.photonstorm.com/flash-game-dev-tips/flash-game-dev-tip-12-building-a-retro-platform-game-in-flixel-part-1
				// Not free for commercial use.
				Sprite* pTileSprite = m_pBackBuffer->CreateSprite("assets\\background.png");
				Tile* tile = new Tile(pTileSprite, 0.0f, 0.0f);

				tile->SetPositionX((float) w * 32);
				tile->SetPositionY((float) h * 32);
				tile->Initialise(pTileSprite, 16, 16); // Height and Width taken as half lengths object width = 2*given width)
				
				tiles.push_back(tile);
			}
			else if (tileID == platform)
			{
				Sprite* pTileSprite = m_pBackBuffer->CreateSprite("assets\\platform.png");
				Tile* tile = new Tile(pTileSprite, 0.0f, 0.0f);

				tile->SetPositionX((float) w * 32);
				tile->SetPositionY((float) h * 32);
				tile->Initialise(pTileSprite, gameWorld, 16, 16); // Height and Width taken as half lengths object width = 2*given width)
				
				tiles.push_back(tile);
			}
			else if (tileID == scoretile)
			{
				Sprite* pTileSprite = m_pBackBuffer->CreateSprite("assets\\scoretile.png");
				Tile* tile = new Tile(pTileSprite, 0.0f, 0.0f);

				tile->SetPositionX((float)w * 32);
				tile->SetPositionY((float)h * 32);
				tile->Initialise(pTileSprite, gameWorld, 16, 16); // Height and Width taken as half lengths object width = 2*given width)

				tiles.push_back(tile);
			}
		}
	}
}

std::vector<Tile*>
LevelManager::GetTiles()
{
	return tiles;
}
