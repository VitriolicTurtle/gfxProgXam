#pragma once
#include "constants.h"
#include "mapobj.h"
#include "player.h"



struct VAO {
	GLuint VertexArrayID;
	GLuint VertexBuffer;
	GLuint TextureBuffer;
	GLuint TextureID;
	GLuint ElementBuffer;
	GLuint NormalBuffer;

	ObjShader* ShaderID;
	ObjTexture* heightMap;					//	Height map 
	ObjTexture* textureProgramID;
	std::vector<short> indexes;

};


class WallObj : public VAO, public MapObj {
private:
	int width;
	int height;
	std::vector<glm::vec3>  PB;				//	Positions
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	glm::mat4x4 WorldMtx = glm::mat4x4(1);
	glm::mat4x4 invWorldMtx = glm::mat4x4(1);;


public:
	WallObj();
	~WallObj() { glBindVertexArray(0); }

	float normalsGenerator(const glm::vec3& position);
	void makeIB();
	void makeVD();
	void makeNB();

	int getID() { return getId(); }
	void bind() { glBindVertexArray(this->VertexArrayID); }
	void unbind() { glBindVertexArray(0); }
};