#include "..\include\game.h"

Game::Game(int w, int h) {
    if (!glfwInit()) {
        GFX_ERROR("GLFW failed to initialize");
    }
    gameWindow.create(w, h);
    GFX_INFO("glfw window created");

    if (!gladLoadGL()) {
        GFX_ERROR("glad init error.");
    }

    // glfwSetInputMode(myWindow.window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetInputMode(gameWindow.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //glfwSetCursorPosCallback(myWindow.window, mouseCallback);      

    // Defaults
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glLineWidth(3);              
}


#include "wallobj.h"
glm::vec3 ppp(0, 0, 3);
glm::vec3 sss(1, 1, 1);

void Game::startGame() {
    GFX_INFO("starting app...");
    ObjTexture* texProgBrick = new ObjTexture("resources/Textures/BrickWall.jpg", false);
    ObjShader* shaProg = new ObjShader("resources/Shaders/vertex.vert", "resources/Shaders/fragment.frag");
    WallObj* wall = new WallObj(GL_TRIANGLES, 36, vertices, normal, uvCoordinates, texProgBrick, shaProg, GL_FILL, 1, ppp, sss);
    Renderer renderer;
    Player player;



    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    do {
        //  DELTATIME FUNCTIONALITY 
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        //////////////////////////////////////////////////////

        gameWindow.setViewport();
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        renderer.loadMap(wall, player);
        player.move(&gameWindow, deltaTime);



        gameWindow.swapBuffers();         
        glfwPollEvents();               
    } while (!gameWindow.shouldClose());

    glfwTerminate();             
}
