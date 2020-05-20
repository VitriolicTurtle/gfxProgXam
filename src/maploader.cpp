#include "..\include\maploader.h"
#include <iostream>

inline float calcPercentage(float value, float min, float max){
	value = glm::clamp(value, min, max);
	return (value - min) / (max - min);
}

void MapLoader::loadMap(){
	wallVector.clear();
	player = new Player();
	//int pixelColour;

	/*
	const int size = 500;

	int VERTEXCOUNT = 200;

	int count = VERTEXCOUNT * VERTEXCOUNT;
	float* verti = new float[count * 3];
	float* norma = new float[count * 3];
	float* texco = new float[count * 2];
	int* indic = new int[6 * (VERTEXCOUNT - 1) * (VERTEXCOUNT * 1)];
	int vertexPointer = 0;
	for (int i = 0; i < VERTEXCOUNT; i++) {
		for (int j = 0; j < VERTEXCOUNT; j++) {
			verti[vertexPointer * 3] = (float)j / ((float)VERTEXCOUNT - 1) * size;
			verti[vertexPointer * 3 + 1] = this->heightMap->getPixel(j, i)-100;
			verti[vertexPointer * 3 + 2] = (float)i / ((float)VERTEXCOUNT - 1) * size;
			norma[vertexPointer * 3] = 0;
			norma[vertexPointer * 3 + 1] = 1;
			norma[vertexPointer * 3 + 2] = 0;
			texco[vertexPointer * 2] = (float)j / ((float)VERTEXCOUNT - 1);
			texco[vertexPointer * 2 + 1] = (float)i / ((float)VERTEXCOUNT - 1);
			vertexPointer++;
		}
	}
	int pointer = 0;
	for (int z = 0; z < VERTEXCOUNT - 1; z++) {
		for (int x = 0; x < VERTEXCOUNT - 1; x++) {
			int topLeft = (z * VERTEXCOUNT) + x;
			int topRight = topLeft + 1;
			int bottomLeft = ((z + 1) * VERTEXCOUNT) + x;
			int bottomRight = bottomLeft + 1;
			indic[pointer++] = topLeft;
			indic[pointer++] = bottomLeft;
			indic[pointer++] = topRight;
			indic[pointer++] = topRight;
			indic[pointer++] = bottomLeft;
			indic[pointer++] = bottomRight;
		}
	}

	std::cout << " :  " << pointer << std::endl;
	std::cout << " :  " << sizeof(indic) << std::endl;


	wallVector.push_back({ GL_TRIANGLES, 6 * (VERTEXCOUNT - 1) * (VERTEXCOUNT * 1), indic, verti, norma, texco, heightMap, shaProg, GL_FILL, 1, glm::vec3(0, -130, 0), glm::vec3(0.01, 0.01, 0.01) });|
	*/
	width = this->heightMap->getSize().x;
	height = this->heightMap->getSize().y;

	std::cout << width;
	

	makeIB();
	makeVD();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);


	//wallVector.push_back({ GL_TRIANGLES, 2, indexes, vertices, miniUvCoords, heightMap, shaProg, GL_FILL, 1, glm::vec3(0, -130, 0), glm::vec3(1.0, 1.0, 1.0) });

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices.front(), GL_STATIC_DRAW);
	GLint positionID = glGetAttribLocation(this->shaProg->id(), "position");
	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(positionID);

	glGenBuffers(1, &(this->tb));  // VBO - textures
	glBindBuffer(GL_ARRAY_BUFFER, this->tb); // Bind the VBO textures
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), miniUvCoords, GL_STATIC_DRAW);  // Copy the vertex into VBO
	GLint textureCoordinateID = glGetAttribLocation(this->shaProg->id(), "uv_coord");
	glVertexAttribPointer(textureCoordinateID, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(textureCoordinateID);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(short), &indexes.front(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	glEnable(GL_TEXTURE0);
	//4320
	/*
	for (int y = player->getPos().z-50; y <= player->getPos().z + 50; y++) {
		for (int x = player->getPos().x-50; x <= player->getPos().x + 50; x += 1) {
			pixelColour = this->heightMap->getPixel(x, y);
			//wallVector.push_back({ GL_TRIANGLES, 36, vertices, normal, uvCoordinates, grass, shaProg, GL_FILL, 1, glm::vec3(x+40, pixelColour - 110, y+100), glm::vec3(0.7, 0.7, 0.7) });
		}
	}
	*/
}





void MapLoader::loadChunk(){

}

void MapLoader::normalsGenerator(int Cx, int Cz){
	
	//WallObj tempWall(GL_TRIANGLES, numIndices, indices, data, normals, uvCoordinates, heightMap, shaProg, GL_FILL, 1, glm::vec3(player->getPos().x, -2, player->getPos().z), glm::vec3(1, 1, 1));

	//wallVector.push_back({ GL_TRIANGLES, numIndices, indices, data, normals, uvCoordinates, heightMap, shaProg, GL_FILL, 1, glm::vec3(player->getPos().x, -2, player->getPos().z), glm::vec3(1, 1, 1) });

	//wallVector.push_back({ GL_TRIANGLES, 36, vertices, normal, uvCoordinates, grass, shaProg, GL_FILL, 1, glm::vec3(player->getPos().x, -2, player->getPos().z), glm::vec3(1, 1, 1) });
}

/////			GET INDEX BUFFERS
void MapLoader::makeIB(){

	for (int row = 0; row < height - 1; row++) {
		for (int col = 0; col < width - 1; col++) {
			short topLeftIndexNum = (short)(row * width + col);
			short topRightIndexNum = (short)(row * width + col + 1);
			short bottomLeftIndexNum = (short)((row + 1) * width + col);
			short bottomRightIndexNum = (short)((row + 1) * width + col + 1);

			// write out two triangles
			indexes.push_back(topLeftIndexNum);
			indexes.push_back(bottomLeftIndexNum);
			indexes.push_back(topRightIndexNum);

			indexes.push_back(topRightIndexNum);
			indexes.push_back(bottomLeftIndexNum);
			indexes.push_back(bottomRightIndexNum);
		}
	}
}
///// GET VERTEX DATA
void MapLoader::makeVD(){
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			float xpos = ((float)col / (float)(width - 1)) - 0.5f;
			float ypos = (float)this->heightMap->getPixel(row, col) / (float)255;
			float zpos = ((float)row / (float)(height - 1)) - 0.5f;

			vertices.push_back(glm::vec3(xpos, ypos, zpos));
		}
	}
}

void MapLoader::makeNB(){
	/*
	for (unsigned int i = 0; i < indexes.size(); i += 3)
	{
		glm::vec3 v0 = m_IndexBuffer[i + 0];
		glm::vec3 v1 = m_IndexBuffer[i + 1];
		glm::vec3 v2 = m_IndexBuffer[i + 2];

		glm::vec3 normal = glm::normalize(glm::cross(v1 - v0, v2 - v0));

		m_NormalBuffer[m_IndexBuffer[i + 0]] += normal;
		m_NormalBuffer[m_IndexBuffer[i + 1]] += normal;
		m_NormalBuffer[m_IndexBuffer[i + 2]] += normal;
	}

	const glm::vec3 UP(0.0f, 1.0f, 0.0f);
	for (unsigned int i = 0; i < m_NormalBuffer.size(); ++i)
	{
		m_NormalBuffer[i] = glm::normalize(m_NormalBuffer[i]);

	}
	*/
}

void MapLoader::MVP(){
	GLint colourID = glGetUniformLocation(shaProg->id(), "testCol");
	glUniform3f(colourID, 1.0F, 1.0F, 1.0F);
	glm::mat4 view = player->getView();
	glm::mat4 projection = glm::perspective(3.14f / 3.0f, (GLfloat)1024 / (GLfloat)768, 0.1f, -10.0f);
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0,-100,0)) * glm::scale(glm::mat4(1), glm::vec3(100.0f, 100.0f, 100.0f));

	GLint modelLoc = glGetUniformLocation(shaProg->id(), "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	//pass view matrix
	GLint viewLoc = glGetUniformLocation(shaProg->id(), "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	GLint projLoc = glGetUniformLocation(shaProg->id(), "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


	//wallVector.push_back({ GL_TRIANGLES, IB.size(), indic, verti, norma, grass, heightMap, shaProg, GL_FILL, 1, glm::vec3(0, -130, 0), glm::vec3(0.01, 0.01, 0.01) })

}

void MapLoader::render(){

	glUseProgram(this->shaProg->id());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, grass->id());

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	GLint positionID = glGetAttribLocation(this->shaProg->id(), "position");
	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
	glEnableVertexAttribArray(positionID);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	

	glDrawElements(GL_TRIANGLES, indexes.size(), GL_UNSIGNED_SHORT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
}
