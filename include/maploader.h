#pragma once
#include "constants.h"
#include "wallobj.h"
#include "player.h"

class MapLoader {
private:
	std::vector<WallObj> wallVector;
	Player* player;

	ObjTexture* heightMap;												//	Holds texture that will be used many times. This way it only has to be read from file once.
	ObjTexture* grass;												//	Holds texture that will be used many times. This way it only has to be read from file once.
	ObjShader* shaProg;													//	Holds shader that will be used for all objects. Only needs to be read once.
public:
																		//	Reads the texture and shader from file.
	MapLoader(){	heightMap = new ObjTexture("resources/HeightMaps/Tyrif_HeightMapLow.png", false); 
					grass = new ObjTexture("resources/Textures/Grass.jpg", false);
					shaProg = new ObjShader("resources/Shaders/vertex.vert", "resources/Shaders/fragment.frag"); }
	void loadMap(const char* levelFilePath);							//	Loads map objects



	inline Player* getPlayer() { return player; }						//	Returns player for use in game loop
	inline std::vector<WallObj>* getWallVector() { return &wallVector; }//	Returns vector containing walls.
};