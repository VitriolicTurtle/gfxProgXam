#include "..\include\window.h"

void Window::create(int width, int height) {
	winHeight = width;
	winWidth = height;

	if (!glfwInit()) {
		GFX_ERROR("Failed to initialize GLFW");
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	window = glfwCreateWindow(width, height, "NatureSim", nullptr, nullptr);


	if (!window) {
		GFX_ERROR("Failed to open GLFW window.");
	}

	glfwMakeContextCurrent(window);


	glfwSwapInterval(1);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
}
void Window::setViewport() {
	glfwGetFramebufferSize(window, &winWidth, &winHeight);
	glViewport(0, 0, winWidth, winHeight);
}
bool Window::shouldClose()
{
	return glfwWindowShouldClose(window);
}
void Window::swapBuffers() {
	glfwSwapBuffers(window);
	std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(16));
}

Window::~Window() {
	glfwDestroyWindow(window);
}



