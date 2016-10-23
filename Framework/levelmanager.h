#ifndef __LEVELMANAGER_H__
#define __LEVELMANAGER_H__

#include <fstream>
#include <Box2D.h>
#include <vector>

#include "tile.h"

// Forward Delcarations
class BackBuffer;
class Sprite;

class LevelManager
{
	// Member Methods
public:
	LevelManager();
	~LevelManager();

	bool Initialise();

	void CreateLevel(BackBuffer* m_pBackBuffer, b2World* gameWorld);
	
	void ReadMapFile();

	std::vector<Tile*> GetTiles();

protected:
private:
	// Member Variables
public:
protected:
	char background;
	char platform;
	char scoretile;
	int levelWidth;
	int levelHeight;

	std::ifstream mapFile;

	std::vector<Tile*> tiles;


private:
};




#endif __LEVELMANAGER_H__