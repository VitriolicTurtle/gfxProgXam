#pragma once
#include "constants.h"
#include "shader.h"
#include "texture.h"


class MapObj {
private:
	GLint id;
	glm::vec3 pos;
	glm::vec3 size;
	bool visible;
public:

	MapObj() {}
	MapObj(int i, glm::vec3 p, glm::vec3 s) { id = 0; pos = p; size = s; visible = true; }




	inline void setPos(glm::vec3 nuPos) { pos = nuPos; }
	inline void setSize(glm::vec3 nuSize) { size = nuSize; }
	inline glm::vec3 getPos() { return pos; }
	inline glm::vec3 getSize() { return size; }
	inline int getId() { return id; }
};