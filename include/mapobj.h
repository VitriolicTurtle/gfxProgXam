#pragma once
#include "constants.h"
#include "shader.h"
#include "texture.h"


class MapObj {
private:
	GLint id;
	glm::vec3 pos;
	glm::vec2 size;
	bool visible;
public:

	MapObj() {}
	MapObj(int i, glm::vec3 p, glm::vec2 s) { id = 0; pos = p; size = s; visible = true; }
	//mapObj(GLenum primitive_mode, int numVertices, const GLfloat* vertices, const GLfloat* normal, const GLfloat* tex, texture* texProg, shader* shaProg, GLenum fill_mode, int i, glm::vec3 p, glm::vec2 s) : gameObj(primitive_mode, numVertices, vertices, normal, tex, texProg, shaProg, fill_mode) { id = i; pos = p; size = s; visible = true; }
	int getId() { return id; }
};