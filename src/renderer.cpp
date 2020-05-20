#include "..\include\renderer.h"


void loadMap(std::vector<WallObj>* wallVector, Player* player) {
	for (auto iter = begin(*wallVector); iter != end(*wallVector); ++iter) {


		/*
		*	Only applies changes to and renders the relevant chunks. 
		*/
		/*if (iter->getPos().x < player->getPos().x + 100
			&& iter->getPos().x > player->getPos().x - 100
			&& iter->getPos().z < player->getPos().z + 100
			&& iter->getPos().z > player->getPos().z - 100) {
		*/
			glUseProgram(iter->textureProgramID->id());

			glBindTexture(GL_TEXTURE_2D, iter->textureProgramID->id());
			glBindVertexArray(iter->VertexArrayID);

			/*
			*	UNIFORM variables from the shaders that we fetct to edit
			*/
			GLint modelID = glGetUniformLocation(iter->ShaderID->id(), "model");
			GLint viewID = glGetUniformLocation(iter->ShaderID->id(), "view");
			GLint projectionID = glGetUniformLocation(iter->ShaderID->id(), "projection");
			GLint normalMatrixID = glGetUniformLocation(iter->ShaderID->id(), "normal_matrix");
			GLint lightPositionID = glGetUniformLocation(iter->ShaderID->id(), "light_position");
			GLint colourID = glGetUniformLocation(iter->ShaderID->id(), "testCol");


			/*
			*	Prepare changes that are to be applied to the UNIFORM shader variables
			*/
			//glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
			glm::mat4 proj = glm::perspective(3.14f / 3.0f, (GLfloat)1024 / (GLfloat)768, 0.1f, -10.0f);
			glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(iter->getPos().x* iter->getSize().x, iter->getPos().y* iter->getSize().y, iter->getPos().z* iter->getSize().z)) * glm::scale(glm::mat4(1.0f), glm::vec3(iter->getSize().x, iter->getSize().y, iter->getSize().z));
			//glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(iter->pos.x * 18, iter->pos.y, iter->pos.z * 18));
			/*
			*	Apply the changes to the UNIFORM shader variables
			*/
			glUniformMatrix4fv(projectionID, 1, GL_FALSE, glm::value_ptr(proj));
			glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(model));


			glUniformMatrix4fv(viewID, 1, GL_FALSE, glm::value_ptr(player->getView()));
			glUniform3f(lightPositionID, player->getPos().x, player->getPos().y, player->getPos().z);
			glUniform3f(colourID, 1.0, 1.0f, 1.0f);
			/*
			*	Draws the cube
			*/
			//glDrawArrays(iter->PrimitiveMode, 0, iter->NumVertices);
			glDrawElements(GL_TRIANGLES, iter->NumVertices, GL_UNSIGNED_SHORT, 0);
		//}
	}

}
