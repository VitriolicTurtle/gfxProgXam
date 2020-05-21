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
    glfwSetCursorPosCallback(gameWindow.window, mouseCallback);

    // Defaults
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glLineWidth(3);              
}



void Game::startGame() {
    GFX_INFO("starting app...");
    
    MapLoader loader;                                                               // Holds all objects rendered & player (Map, Animals, Trees, Sun and Player) 
    Renderer renderer;                                                              // Takes care of the drawing of objects as well as the changing of uniform variables

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    float timeCapturer = 0.0f;

    do {
        //  DELTATIME FUNCTIONALITY 
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        timeCapturer += deltaTime;
        if (timeCapturer >= 5.0f) timeCapturer = 0.0f;                               // For initialising actions after a set time (E.g. generate new model walking direction)
        //////////////////////////////////////////////////////
        gameWindow.setViewport();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /*
        *    Everything game related
        */
        //////////////////////////////////////////////////////

        loader.getPlayer()->movePlayer(&gameWindow, deltaTime, loader.getMap(), &loader.getObjModels()[0].back());
        renderer.drawMap(&loader);
        renderer.drawObjModel(&loader);
        loader.moveObjModels(deltaTime, timeCapturer);



        //////////////////////////////////////////////////////
        gameWindow.swapBuffers();         
        glfwPollEvents();               
    } while (!gameWindow.shouldClose());

    glfwTerminate();             
}
