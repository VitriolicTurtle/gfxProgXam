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

	
	int width;
	int height;
	int numElements;

	GLuint vao;
	GLuint vbo;
	GLuint ibo;
	GLuint nb;
	GLuint tb;
	std::vector<glm::vec3>  PB;				//	Positions
	std::vector<glm::vec3> vertices;
	std::vector<short> indexes;
	std::vector<glm::vec3> normals;

	glm::mat4x4 WorldMtx = glm::mat4x4(1);
	glm::mat4x4 invWorldMtx = glm::mat4x4(1);;

public:
																		//	Reads the texture and shader from file.   Gjovik_HeightMapLow
	MapLoader(){	heightMap = new ObjTexture("resources/HeightMaps/gjovikSmall.png", false); 
				//	heightMap = new ObjTexture("resources/HeightMaps/Tyrif_HeightMapLow.png", false); 
					grass = new ObjTexture("resources/Textures/Grass.png", false);
					shaProg = new ObjShader("resources/Shaders/vertex.vert", "resources/Shaders/fragment.frag"); }
	void loadMap();							//	Loads map objects
	void loadChunk();
	float normalsGenerator(const glm::vec3& position);
	void makeIB();
	void makeVD();
	void makeNB();
	void MVP();
	void render();


	inline Player* getPlayer() { return player; }						//	Returns player for use in game loop
	inline std::vector<WallObj>* getWallVector() { return &wallVector; }//	Returns vector containing walls.
};