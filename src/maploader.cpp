#include "..\include\maploader.h"
#include <iostream>

struct objModelData {
	const char* obj;
	const char* tex;
	glm::vec3 pos;
	glm::vec3 size;
	bool isFlying;
	int climbHeight;
	float rotate;
};

MapLoader::MapLoader(){
	player = new Player();			// Create player
	map = new WallObj();			// Create Map
									// All objects made here:
	std::vector<glm::vec3> posAndSize;
	std::vector<const char*> links;
	std::vector<objModelData> models;
	
	//		FIRST MODEL: Duck
	objModelVector.push_back({});
	models.push_back({ "resources/Objects/Fish/fish.obj", "resources/Objects/Fish/fish.png", glm::vec3(4, -50, 22), glm::vec3(0.2, 0.2, 0.2), false, -55, 0.0 });		// -55 tells us that it cant go to points higher than y=-55. This in theory limits the fish to water though it isnt represented well graphically

	
	//		SECOND MODEL: Plane
	objModelVector.push_back({});
	models.push_back({ "resources/Objects/Plane/plane.obj", "", glm::vec3(4, 10, 27), glm::vec3(0.07, 0.07, 0.07), true, 0, 0.0 });

	//		FIRST MODEL: Duck
	objModelVector.push_back({});
	models.push_back({ "resources/Objects/Duck/12248_Bird_v1_L2.obj", "resources/Objects/Duck/12248_Bird_v1_diff.png", glm::vec3(4, -50, 22), glm::vec3(0.2, 0.2, 0.2), false, -40, -190.0 });		// -40 tells us that it cant go to points higher than y=-40. This limits the duck to water and land, but not peaks of mountains.


	int objModelCounter = 0;

	for (auto iter = begin(objModelVector); iter != end(objModelVector); ++iter) {
		// Structure:		.obj file	||	texture file	 ||			Position				||		size				||
		iter->load(models[objModelCounter].obj, models[objModelCounter].tex, models[objModelCounter].pos, models[objModelCounter].size, models[objModelCounter].isFlying, models[objModelCounter].climbHeight, models[objModelCounter].rotate);
		objModelCounter++;
	}
}

void MapLoader::moveObjModels(float deltaTime, float timeCapturer){
	for (auto iter = begin(objModelVector); iter != end(objModelVector); ++iter) {
		iter->moveObjModel(deltaTime, timeCapturer, map);
	}
}

