#include "..\include\wallobj.h"
#include <iostream>

#ifndef ENABLE_MULTITEXTURE
#define ENABLE_MULTITEXTURE 1
#endif


WallObj::WallObj() {

	// Create height map, texture, and shader.
	this->heightMap = new ObjTexture("resources/HeightMaps/xGjovikSmall.png", false, true);
	this->textureProgramID = new ObjTexture("resources/Textures/xGjovikSmallTex.png", false, false);
	this->ShaderID = new ObjShader("resources/Shaders/vertex.vert", "resources/Shaders/fragment.frag");

	// Get width for future use.
	width = this->heightMap->getSize().x;
	height = this->heightMap->getSize().y;
	PB.resize(width * height);

	this->setPos(glm::vec3(0, 0, 0));

	makeIB();
	makeVD();


	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	std::cout << normals.data() << std::endl;

	glGenVertexArrays(1, &this->VertexArrayID);
	glBindVertexArray(this->VertexArrayID);
	glGenBuffers(1, &this->VertexBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, this->VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices.front(), GL_STATIC_DRAW);
	GLint positionID = glGetAttribLocation(this->ShaderID->id(), "position");
	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(positionID);

	glGenBuffers(1, &(this->NormalBuffer));  // VBO - Normal
	glBindBuffer(GL_ARRAY_BUFFER, this->NormalBuffer); // Bind the VBO vertices
	glBufferData(GL_ARRAY_BUFFER, indexes.size() * sizeof(float), normals.data(), GL_STATIC_DRAW); // Copy the vertices into VBO
	GLint normalID = glGetAttribLocation(this->ShaderID->id(), "normal");
	glVertexAttribPointer(normalID, 3, GL_FLOAT, GL_FALSE, sizeof(float), 0);
	glEnableVertexAttribArray(normalID);   //<-- Enable normalID attribute


	glGenBuffers(1, &(this->TextureBuffer));  // VBO - textures
	glBindBuffer(GL_ARRAY_BUFFER, this->TextureBuffer); // Bind the VBO textures
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), miniUvCoords, GL_STATIC_DRAW);  // Copy the vertex into VBO
	GLint textureCoordinateID = glGetAttribLocation(this->ShaderID->id(), "uv_coord");
	glVertexAttribPointer(textureCoordinateID, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(textureCoordinateID);

	glGenBuffers(1, &this->ElementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ElementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(short), &indexes.front(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glEnable(GL_TEXTURE0);
}


/////			GET INDEX BUFFERS
void WallObj::makeIB() {

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
void WallObj::makeVD() {
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			float xpos = ((float)col / (float)(width - 1)) - 0.5f;
			float ypos = (float)this->heightMap->getPixel(row, col) / (float)255;
			float zpos = ((float)row / (float)(height - 1)) - 0.5f;

			vertices.push_back(glm::vec3(xpos, ypos, zpos));
		}
	}
}

void WallObj::makeNB() {
	for (unsigned int i = 0; i < indexes.size(); i += 3)
	{
		glm::vec3 v0 = vertices[indexes[i + 0]];
		glm::vec3 v1 = vertices[indexes[i + 1]];
		glm::vec3 v2 = vertices[indexes[i + 2]];

		glm::vec3 normal = glm::normalize(glm::cross(v1 - v0, v2 - v0));

		normals[indexes[i + 0]] += normal;
		normals[indexes[i + 1]] += normal;
		normals[indexes[i + 2]] += normal;
	}

	for (unsigned int i = 0; i < normals.size(); ++i)
	{
		normals[i] = glm::normalize(normals[i]);
	}
}
