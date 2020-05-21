#include "..\include\maploader.h"
#include <iostream>

MapLoader::MapLoader(){
	player = new Player();			// Create player
	map = new WallObj();			// Create Map

									// All objects made here:
	std::vector<glm::vec3> posAndSize;
	objModelVector.push_back({});
	posAndSize.push_back({ 4, -50, 22 });
	posAndSize.push_back({ 0.2, 0.2, 0.2 });
	objModelVector.push_back({});
	posAndSize.push_back({ 4, -52, 27 });
	posAndSize.push_back({ 0.2, 0.2, 0.2 });

	int objModelCounter = 0;

	for (auto iter = begin(objModelVector); iter != end(objModelVector); ++iter) {
		iter->load("resources/Objects/Duck/12248_Bird_v1_L2.obj", "resources/Objects/Duck/12248_Bird_v1_diff.png", posAndSize[objModelCounter], posAndSize[objModelCounter+1]);
		objModelCounter += 2;
		std::cout << objModelCounter << std::endl;
	}
}

