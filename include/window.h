#pragma once

#include "constants.h"
#include <thread>
#include <chrono>


class Window {
private:
	int winHeight;
	int winWidth;
public:
	GLFWwindow* window;
	//Window() {}
	~Window();
	void create(int width, int height);
	void setViewport();
	bool shouldClose();
	void swapBuffers();

};