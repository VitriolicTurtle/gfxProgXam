#pragma once
#include "constants.h"
#include "wallobj.h"
#include "player.h"

class MapLoader {
private:
	WallObj* map;
	Player* player;
	std::vector<ObjModel> objModelVector;

public:
	MapLoader();														// Creates the map and player
	void moveObjModels(float deltaTime, float timeCapturer);


	inline Player* getPlayer() { return player; }						//	Returns player for use in game loop
	inline WallObj* getMap() { return map; }							//	Returns vector containing walls.
	inline std::vector<ObjModel>* getObjModels() { return &objModelVector; }
};