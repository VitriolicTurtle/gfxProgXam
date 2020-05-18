#pragma once
#include "constants.h"
#include "mapobj.h"
#include "window.h"


/*
*	Struct for camera movement variables made for structure in Player class. 
*/
struct camMovementVariables {
	const float mouseSens = 1.80F;		
	float yaw = -90.0F;
	float pitch = 0.0F;
	double xoffset = 0.0F;
	double yoffset = 0.0F;
	float lastX = 512;
	float lastY = 384;
	bool mouseMoved = false;
};




class Player : public MapObj{
private:
	camMovementVariables camMovement;
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 view;
public:
	Player() : MapObj(0, glm::vec3(0,0,0), glm::vec3(1, 1, 1)){		}
	void movePlayer(Window* window, float deltaTime);
	void moveView(Window* window, float deltaTime);
	

	glm::mat4 getView() { return view; }
};