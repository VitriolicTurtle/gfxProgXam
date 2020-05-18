#pragma once
#include "constants.h"
#include "mapobj.h"



struct VAO {
	GLuint VertexArrayID;
	GLuint VertexBuffer;
	GLuint EBO;
	GLuint ColorBuffer;
	GLuint TextureBuffer;
	GLuint TextureID;
	GLuint ElementBuffer;
	GLuint NormalBuffer;

	ObjShader* ShaderID;
	ObjTexture* textureProgramID;

	GLenum PrimitiveMode; // GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES, GL_LINE_STRIP_ADJACENCY, GL_LINES_ADJACENCY, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES, GL_TRIANGLE_STRIP_ADJACENCY and GL_TRIANGLES_ADJACENCY
	GLenum FillMode;	  // GL_FILL, GL_LINE
	int NumVertices;
};


class WallObj : public VAO, public MapObj {
public:
	WallObj(GLenum primitive_mode, int numVertices, const GLfloat* vertices, const GLfloat* normal, const GLfloat* tex, ObjTexture* texProg, ObjShader* shaProg, GLenum fill_model, int id, glm::vec3 pos, glm::vec3 size);
	//void update(const GLfloat * vertices_position);



	//GLuint id() const { return VertexArrayID; }
	//shader getVshader() const { return *ShaderID; }
	void bind() { glBindVertexArray(this->VertexArrayID); }
	void unbind() { glBindVertexArray(0); }
};