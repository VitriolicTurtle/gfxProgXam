#pragma once
#include "constants.h"
#include "wallobj.h"
#include "window.h"
#include "objmodel.h"


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
	bool isGrounded;

	glm::vec3   force;
	glm::vec3   velocity;
	glm::vec3   translate;
public:
	Player() : MapObj(0, glm::vec3(4.0f,-66.0f,18.0f), glm::vec3(1, 1, 1)){		}
	void movePlayer(Window* window, float deltaTime, WallObj* map, ObjModel* objModelPosition);
	void moveView(Window* window, float deltaTime);
	

	glm::vec3 getFront() { return cameraFront; }
	glm::mat4 getView() { return view; }
};