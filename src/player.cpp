#include "player.h"

void Player::move(Window* window, float deltaTime){
    
    glm::vec3 tempCamPos = this->getPos();
    float cameraSpeed = 2.5 * deltaTime;                   // Sets movement speed.
    bool move = true;

    if (glfwGetKey(window->window, GLFW_KEY_W) == GLFW_PRESS)      // If you press W
        tempCamPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window->window, GLFW_KEY_S) == GLFW_PRESS)      // If you press S
        tempCamPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window->window, GLFW_KEY_A) == GLFW_PRESS)       // If you press A
        tempCamPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;   // Normalize and multiply
    if (glfwGetKey(window->window, GLFW_KEY_D) == GLFW_PRESS) {      // If you press D
        tempCamPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if (glfwGetKey(window->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {      // Close if you press ESC
        window->shouldClose();
    }

    this->setPos(tempCamPos);                                                            
    view = glm::lookAt(this->getPos(), this->getPos() + cameraFront, cameraUp);

}
