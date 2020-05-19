#include "..\include\maploader.h"
#include <iostream>

void MapLoader::loadMap(const char* levelFilePath){
	wallVector.clear();
	
	int pixelColour;
	int count = 0;
	//4320
	for (int y = 0; y <= 300; y++) {
		for (int x = 0; x <= 300; x += 1) {
			pixelColour = this->heightMap->getPixel(x, y);
			glm::vec3 ppp(x, pixelColour-150, y);
			glm::vec3 sss(1, 1, 1);


			wallVector.push_back({ GL_TRIANGLES, 36, vertices, normal, uvCoordinates, grass, shaProg, GL_FILL, 1, ppp, sss });

			count++;





		}
	}

	
	std::cout << " " << count;



	player = new Player();

	glm::vec3 ppp(0, 0, 3);
	glm::vec3 sss(1, 1, 1);
	//	WallObj* wall = new WallObj(GL_TRIANGLES, 36, vertices, normal, uvCoordinates, texProgBrick, shaProg, GL_FILL, 1, ppp, sss);
	//wallVector.push_back({ GL_TRIANGLES, 36, vertices, normal, uvCoordinates, texProgBrick, shaProg, GL_FILL, 1, ppp, sss });
}
