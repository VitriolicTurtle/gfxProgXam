#pragma once
#include "constants.h"
#include "wallobj.h"


class MapLoader {
private:
	std::vector<WallObj> wallVector;
public:
	MapLoader(){	}
	void loadMap(const char* levelFilePath);
};