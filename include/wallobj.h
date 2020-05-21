#pragma once
#include "constants.h"
#include "mapobj.h"





class WallObj : public MapObj {
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
	float getHeight(const glm::vec3& position);
	void makeIB();
	void makeVD();
	void makeNB();

	inline int getID() { return getId(); }
	glm::vec3 getPOS() { return getPos(); }
	inline void bind() { glBindVertexArray(this->VertexArrayID); }
	inline void unbind() { glBindVertexArray(0); }
};