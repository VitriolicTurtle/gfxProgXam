#pragma once
#include "constants.h"
#include "wallobj.h"
#include "player.h"

class MapLoader {
private:
	WallObj* map;
	Player* player;
public:
	MapLoader();														// Creates the map and player


	inline Player* getPlayer() { return player; }						//	Returns player for use in game loop
	inline WallObj* getMap() { return map; }							//	Returns vector containing walls.
};