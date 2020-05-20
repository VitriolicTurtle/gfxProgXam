#include "..\include\maploader.h"
#include <iostream>

#ifndef ENABLE_MULTITEXTURE
#define ENABLE_MULTITEXTURE 1
#endif

inline float calcPercentage(float value, float min, float max){
	value = glm::clamp(value, min, max);
	return (value - min) / (max - min);
}

void MapLoader::loadMap(){
	wallVector.clear();
	player = new Player();

	//grass->bind();
	//heightMap->bind();


	//wallVector.push_back({ GL_TRIANGLES, 6 * (VERTEXCOUNT - 1) * (VERTEXCOUNT * 1), indic, verti, norma, texco, heightMap, shaProg, GL_FILL, 1, glm::vec3(0, -130, 0), glm::vec3(0.01, 0.01, 0.01) });|
	width = this->heightMap->getSize().x;
	height = this->heightMap->getSize().y;

	std::cout << width;
	
	PB.resize(width*height);
	makeIB();
	makeVD();



	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	std::cout << normals.data() << std::endl;
	//wallVector.push_back({ GL_TRIANGLES, 2, indexes, vertices, miniUvCoords, heightMap, shaProg, GL_FILL, 1, glm::vec3(0, -130, 0), glm::vec3(1.0, 1.0, 1.0) });

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices.front(), GL_STATIC_DRAW);
	GLint positionID = glGetAttribLocation(this->shaProg->id(), "position");
	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(positionID);

	glGenBuffers(1, &(this->nb));  // VBO - Normal
	glBindBuffer(GL_ARRAY_BUFFER, this->nb); // Bind the VBO vertices
	glBufferData(GL_ARRAY_BUFFER, indexes.size() * sizeof(float), normals.data(), GL_STATIC_DRAW); // Copy the vertices into VBO
	GLint normalID = glGetAttribLocation(this->shaProg->id(), "normal");
	glVertexAttribPointer(normalID, 3, GL_FLOAT, GL_FALSE, sizeof(float), 0);
	glEnableVertexAttribArray(normalID);   //<-- Enable normalID attribute


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
}





void MapLoader::loadChunk(){

}

float MapLoader::normalsGenerator(const glm::vec3& position){
	float retHeight = -FLT_MAX;
	float scale = 1.0f;
	if (width < 2 || height < 2) return retHeight;

	// Width and height of the terrain in world units
	float terrainWidth = (width - 1) * scale;
	float terrainHeight = (height - 1) * scale;
	float halfWidth = terrainWidth * 0.5f;
	float halfHeight = terrainHeight * 0.5f;

	glm::vec3 terrainPos = glm::vec3(invWorldMtx * glm::vec4(position, 1.0f));
	glm::vec3 invBlockScale(1.0f / scale, 0.0f, 1.0f / scale);
	glm::vec3 offset(halfWidth, 0.0f, halfHeight);
	glm::vec3 vertexIndices = (terrainPos + offset) * invBlockScale;

	int u0 = (int)floorf(vertexIndices.x);
	int u1 = u0 + 1;
	int v0 = (int)floorf(vertexIndices.z);
	int v1 = v0 + 1;


	if (u0 >= 0 && u1 < (int)width && v0 >= 0 && v1 < (int)height)
	{
		glm::vec3 p00 = PB[(v0 * width) + u0];    // Top-left vertex
		glm::vec3 p10 = PB[(v0 * width) + u1];    // Top-right vertex
		glm::vec3 p01 = PB[(v1 * width) + u0];    // Bottom-left vertex
		glm::vec3 p11 = PB[(v1 * width) + u1];    // Bottom-right vertex

		// Which triangle are we over?
		float percentU = vertexIndices.x - u0;
		float percentV = vertexIndices.z - v0;

		glm::vec3 dU, dV;
		if (percentU > percentV)
		{   // Top triangle
			dU = p10 - p00;
			dV = p11 - p10;
		}
		else
		{   // Bottom triangle
			dU = p11 - p01;
			dV = p01 - p00;
		}

		glm::vec3 heightPos = p00 + (dU * percentU) + (dV * percentV);
		// Convert back to world-space by multiplying by the terrain's world matrix
		heightPos = glm::vec3(WorldMtx * glm::vec4(heightPos, 1));
		height = heightPos.y;
	}

	return height;

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
	for ( unsigned int i = 0; i < indexes.size(); i += 3 )
    {
        glm::vec3 v0 = vertices[indexes[i + 0] ];
        glm::vec3 v1 = vertices[indexes[i + 1] ];
        glm::vec3 v2 = vertices[indexes[i + 2] ];

        glm::vec3 normal = glm::normalize( glm::cross( v1 - v0, v2 - v0 ) );

		normals[indexes[i + 0] ] += normal;
		normals[indexes[i + 1] ] += normal;
		normals[indexes[i + 2] ] += normal;
    }

    const glm::vec3 UP( 0.0f, 1.0f, 0.0f );
    for ( unsigned int i = 0; i < normals.size(); ++i )
    {
		normals[i] = glm::normalize(normals[i] );
	}
}

void MapLoader::MVP(){

	GLint lightPositionID = glGetUniformLocation(shaProg->id(), "light_position");
	GLint modelLoc = glGetUniformLocation(shaProg->id(), "model");
	GLint viewLoc = glGetUniformLocation(shaProg->id(), "view");
	GLint projLoc = glGetUniformLocation(shaProg->id(), "projection");
	GLint colourID = glGetUniformLocation(shaProg->id(), "testCol");


	glm::mat4 view = player->getView();
	glm::mat4 projection = glm::perspective(3.14f / 3.0f, (GLfloat)1024 / (GLfloat)768, 0.1f, -10.0f);
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0,-100,0)) * glm::scale(glm::mat4(1), glm::vec3(100.0f, 100.0f, 100.0f));


	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniform3f(lightPositionID, player->getPos().x, player->getPos().y, player->getPos().z);
	glUniform3f(colourID, 1.0F, 1.0F, 1.0F);


}

void MapLoader::render(){

	glEnable(GL_TEXTURE_2D);
#if ENABLE_MULTITEXTURE


#else
	glEnable(GL_VERTEX_ARRAY);
#endif

	glEnable(GL_TEXTURE_2D);
	glUseProgram(this->shaProg->id());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, heightMap->id());
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
