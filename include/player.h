#pragma once
#include "constants.h"
#include "mapobj.h"
#include "window.h"


class Player : public MapObj{
private:
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 view;
public:
	Player() : MapObj(0, glm::vec3(0,0,0), glm::vec3(1, 1, 1)){		}
	void move(Window* window, float deltaTime);
	

	glm::mat4 getView() { return view; }
};