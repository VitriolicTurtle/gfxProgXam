#include "..\include\renderer.h"

void Renderer::loadMap(WallObj* wallObj, Player player) {
	glUseProgram(wallObj->textureProgramID->id());

	glBindTexture(GL_TEXTURE_2D, wallObj->textureProgramID->id());
	glBindVertexArray(wallObj->VertexArrayID);

	/*
	*	UNIFORM variables from the shaders that we fetct to edit
	*/
	GLint modelID = glGetUniformLocation(wallObj->ShaderID->id(), "model");
	GLint viewID = glGetUniformLocation(wallObj->ShaderID->id(), "view");
	GLint projectionID = glGetUniformLocation(wallObj->ShaderID->id(), "projection");
	GLint normalMatrixID = glGetUniformLocation(wallObj->ShaderID->id(), "normal_matrix");
	GLint lightPositionID = glGetUniformLocation(wallObj->ShaderID->id(), "light_position");
	GLint colourID = glGetUniformLocation(wallObj->ShaderID->id(), "testCol");



	/*
	*	Prepare changes that are to be applied to the UNIFORM shader variables
	*/
	//glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 proj = glm::perspective(3.14f / 3.0f, (GLfloat)1024 / (GLfloat)768, 0.1f, -10.0f);
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -4));
	//glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(iter->pos.x * 18, iter->pos.y, iter->pos.z * 18));
	/*
	*	Apply the changes to the UNIFORM shader variables
	*/
	glUniformMatrix4fv(projectionID, 1, GL_FALSE, glm::value_ptr(proj));
	glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(model));


	glUniformMatrix4fv(viewID, 1, GL_FALSE, glm::value_ptr(player.getView()));
	glUniform3f(lightPositionID, player.getPos().x, player.getPos().y, player.getPos().z);
	glUniform3f(colourID, 1.0, 1.0f, 1.0f);
	/*
	*	Draws the cube
	*/
	glDrawArrays(wallObj->PrimitiveMode, 0, wallObj->NumVertices);
}
