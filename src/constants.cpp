#include "constants.h"





// Function had to be global for fetching to work.
glm::vec2 mouseData(0);
void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	mouseData = glm::vec2(xpos, ypos);
}










GLfloat miniVertices[] = {
	// positions         
	-0.5f,  0.5f, -0.5f,           //Top Face
	 0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f,  0.9f,
	-0.5f,  0.5f,  0.9f,
	-0.5f,  0.1f, -0.9f,

};

GLfloat miniUvCoords[] = {
	1.0f, 1.0f,
	1.0f, 0.0f,
	0.0f, 0.0f,
	0.0f, 1.0f
};

GLfloat indices[] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
};






GLfloat vertices[] = {              // Vert. coords
			-0.5f, -0.5f, -0.5f,                    //Back Face
			 0.5f, -0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f, -0.5f,  0.5f,                  //Front Face
			 0.5f, -0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,

			-0.5f,  0.5f,  0.5f,           //Left Face
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,

			 0.05f,  0.05f,  0.05f,           //Right Face
			 0.05f,  0.05f, -0.05f,
			 0.05f, -0.05f, -0.05f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,

			-0.5f, -0.5f, -0.5f,           //Bottom Face
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f,  0.5f, -0.5f,           //Top Face
			 0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f,
};

GLfloat normal[] = {
	 0.0f,  0.0f, -1.0f,
	 0.0f,  0.0f, -1.0f,
	 0.0f,  0.0f, -1.0f,
	 0.0f,  0.0f, -1.0f,
	 0.0f,  0.0f, -1.0f,
	 0.0f,  0.0f, -1.0f,

	 0.0f,  0.0f,  1.0f,
	 0.0f,  0.0f,  1.0f,
	 0.0f,  0.0f,  1.0f,
	 0.0f,  0.0f,  1.0f,
	 0.0f,  0.0f,  1.0f,
	 0.0f,  0.0f,  1.0f,

	-1.0f,  0.0f,  0.0f,
	-1.0f,  0.0f,  0.0f,
	-1.0f,  0.0f,  0.0f,
	-1.0f,  0.0f,  0.0f,
	-1.0f,  0.0f,  0.0f,
	-1.0f,  0.0f,  0.0f,

	 1.0f,  0.0f,  0.0f,
	 1.0f,  0.0f,  0.0f,
	 1.0f,  0.0f,  0.0f,
	 1.0f,  0.0f,  0.0f,
	 1.0f,  0.0f,  0.0f,
	 1.0f,  0.0f,  0.0f,

	 0.0f, -1.0f,  0.0f,
	 0.0f, -1.0f,  0.0f,
	 0.0f, -1.0f,  0.0f,
	 0.0f, -1.0f,  0.0f,
	 0.0f, -1.0f,  0.0f,
	 0.0f, -1.0f,  0.0f,

	 0.0f,  1.0f,  0.0f,
	 0.0f,  1.0f,  0.0f,
	 0.0f,  1.0f,  0.0f,
	 0.0f,  1.0f,  0.0f,
	 0.0f,  1.0f,  0.0f,
	 0.0f,  1.0f,  0.0f,
};


GLfloat uvCoordinates[] = {            //Tex. coords
	 0.0f,  0.0f,
	 1.0f,  0.0f,
	 1.0f,  1.0f,
	 1.0f,  1.0f,
	 0.0f,  1.0f,
	 0.0f,  0.0f,

	 0.0f,  0.0f,
	 1.0f,  0.0f,
	 1.0f,  1.0f,
	 1.0f,  1.0f,
	 0.0f,  1.0f,
	 0.0f,  0.0f,

	 1.0f,  1.0f,
	 0.0f,  1.0f,
	 0.0f,  0.0f,
	 0.0f,  0.0f,
	 1.0f,  0.0f,
	 1.0f,  1.0f,

	 1.0f,  1.0f,
	 0.0f,  1.0f,
	 0.0f,  0.0f,
	 0.0f,  0.0f,
	 1.0f,  0.0f,
	 1.0f,  1.0f,

	 0.0f,  0.0f,
	 1.0f,  0.0f,
	 1.0f,  1.0f,
	 1.0f,  1.0f,
	 0.0f,  1.0f,
	 0.0f,  0.0f,

	 0.0f,  0.0f,
	 1.0f,  0.0f,
	 1.0f,  1.0f,
	 1.0f,  1.0f,
	 0.0f,  1.0f,
	 0.0f,  0.0f,
};

