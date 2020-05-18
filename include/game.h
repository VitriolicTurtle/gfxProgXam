#include "constants.h"
#include "window.h"
#include "renderer.h"
#include "texture.h"
#include "shader.h"


class Game {
private:
	Window gameWindow;
public:
	Game(int w = 1024, int h = 768);        // Constructor that initialises game window and defaults
	~Game() { glfwTerminate(); }
	void startGame();
};

