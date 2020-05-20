#include "..\include\maploader.h"
#include <iostream>

MapLoader::MapLoader(){
	player = new Player();			// Create player
	map = new WallObj();			// Create Map
}

