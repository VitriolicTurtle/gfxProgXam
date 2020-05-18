#include "..\include\wallobj.h"

WallObj::WallObj(GLenum primitive_mode, int numVertices, const GLfloat* vertices, const GLfloat* normal, const GLfloat* tex, ObjTexture* texProg, ObjShader* shaProg, GLenum fill_mode, int id, glm::vec3 pos, glm::vec3 size) : MapObj(id, pos, size) {
	// Fill inn data into VAO struct
	this->ShaderID = shaProg;
	this->textureProgramID = texProg;
	this->NumVertices = numVertices;
	this->PrimitiveMode = primitive_mode;

	this->FillMode = fill_mode;

	// Create Vertex Array Object
	// Should be done after CreateWindow and before any other GL calls
	glGenVertexArrays(1, &(this->VertexArrayID)); // VAO
	glBindVertexArray(this->VertexArrayID); // Bind the VAO

	glGenBuffers(1, &(this->VertexBuffer)); // VBO - vertices
	glBindBuffer(GL_ARRAY_BUFFER, this->VertexBuffer); // Bind the VBO vertices
	glBufferData(GL_ARRAY_BUFFER, 6 * 6 * 3 * sizeof(GLfloat), vertices, GL_STATIC_DRAW); // Copy the vertices into VBO
	GLint positionID = glGetAttribLocation(this->ShaderID->id(), "position");
	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(positionID);

	glGenBuffers(1, &(this->NormalBuffer));  // VBO - Normal
	glBindBuffer(GL_ARRAY_BUFFER, this->NormalBuffer); // Bind the VBO vertices
	glBufferData(GL_ARRAY_BUFFER, 6 * 6 * 3 * sizeof(GLfloat), normal, GL_STATIC_DRAW); // Copy the vertices into VBO
	GLint normalID = glGetAttribLocation(this->ShaderID->id(), "normal");
	glVertexAttribPointer(normalID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(normalID);   //<-- Enable normalID attribute

	glGenBuffers(1, &(this->TextureBuffer));  // VBO - textures
	glBindBuffer(GL_ARRAY_BUFFER, this->TextureBuffer); // Bind the VBO textures
	glBufferData(GL_ARRAY_BUFFER, 6 * 6 * 2 * sizeof(GLfloat), tex, GL_STATIC_DRAW);  // Copy the vertex into VBO
	GLint textureCoordinateID = glGetAttribLocation(this->ShaderID->id(), "uv_coord");
	glVertexAttribPointer(textureCoordinateID, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(textureCoordinateID);

	GLint ColourID = glGetAttribLocation(this->ShaderID->id(), "aColour");
	glVertexAttribPointer(textureCoordinateID, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(textureCoordinateID);



	glActiveTexture(GL_TEXTURE0);
}
