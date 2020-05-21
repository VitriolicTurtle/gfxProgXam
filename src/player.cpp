#include "player.h"
#include <iostream>

void Player::movePlayer(Window* window, float deltaTime, WallObj* map, ObjModel* posModel){
    
    glm::vec3 tempCamPos = this->getPos();
    float cameraSpeed = 10.5 * deltaTime;                   
    bool isGrounded = true;
    float heightOffsett = 5.0f;

    float fallValue = 0;//-3.8f;


    //      If you press E you get to see from ducks position.
    if (glfwGetKey(window->window, GLFW_KEY_E) == GLFW_PRESS) {
        tempCamPos = posModel->getPos();
    }
    //      If you press Q you see from perspective above.
    else if (glfwGetKey(window->window, GLFW_KEY_Q) == GLFW_PRESS) {
        tempCamPos = glm::vec3(4.0f, 0.0f, 18.0f);;
    }
    if (glfwGetKey(window->window, GLFW_KEY_W) == GLFW_PRESS)
        tempCamPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window->window, GLFW_KEY_S) == GLFW_PRESS)
        tempCamPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window->window, GLFW_KEY_A) == GLFW_PRESS)
        tempCamPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window->window, GLFW_KEY_D) == GLFW_PRESS) {
        tempCamPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }


    //      After moving you then set the position of the model.
    //      NB! Moving the duck into an area outside of where its walking borders are can cause it to glitch in spasms.
    if (glfwGetKey(window->window, GLFW_KEY_E) == GLFW_PRESS) {
        posModel->setPos(tempCamPos);
    }

    float tcpx = tempCamPos.x;
    if (tcpx < 0) tcpx *= -1.0;
    float tcpz = tempCamPos.z;
    if (tcpz < 0) tcpz *= -1.0;

    float fHeight = (((float)map->heightMap->getPixel(tcpz, tcpx) / (float)100) * 40) * (-1.09);

    //std::cout << getPos().x << " " << getPos().y << " " << getPos().z << std::endl;
    //std::cout << fHeight + heightOffsett << "                            " << fallValue << std::endl;

    float groundedYpos = 0;
    if (tempCamPos.y + fallValue < (fHeight + heightOffsett)) {
        isGrounded = true;
        fallValue = 0;
        float groundedYpos = (float)(fHeight + heightOffsett);
    }
    tempCamPos.y += fallValue * deltaTime;

    if (fallValue == 0.0f) isGrounded = false;

    if (isGrounded) {
        tempCamPos.y = fHeight;
    }


    moveView(window, deltaTime);                                    // Mouse input handler
    this->setPos(tempCamPos);                                                            
    view = glm::lookAt(this->getPos(), this->getPos() + cameraFront, cameraUp);

}

void Player::moveView(Window* window, float deltaTime){

    /*
    *   Gets mouse input from global variable, and processes it
    */
    if (!camMovement.mouseMoved) {
        camMovement.lastX = mouseData.x;
        camMovement.lastY = mouseData.y;
        camMovement.mouseMoved = true;
    }
    camMovement.xoffset = mouseData.x - camMovement.lastX;
    camMovement.yoffset = camMovement.lastY - mouseData.y;
    camMovement.lastX = mouseData.x;
    camMovement.lastY = mouseData.y;
    //////////////////////////////////////////////////////////////////

    float adjustedMove = camMovement.mouseSens * deltaTime;
    camMovement.xoffset *= adjustedMove;
    camMovement.yoffset *= adjustedMove;

    camMovement.yaw += camMovement.xoffset;
    camMovement.pitch += camMovement.yoffset;

    if (camMovement.pitch > 89.0f) {
        camMovement.pitch = 89.0f;
    }
    if (camMovement.pitch < -89.0f) {
        camMovement.pitch = -89.0f;
    }

    glm::vec3 direction;
    direction.x = cos(glm::radians(camMovement.yaw)) * cos(glm::radians(camMovement.pitch));
    direction.y = sin(glm::radians(camMovement.pitch));
    direction.z = sin(glm::radians(camMovement.yaw)) * cos(glm::radians(camMovement.pitch));
    cameraFront = glm::normalize(direction);


    camMovement.xoffset = 0.0f;       
    camMovement.yoffset = 0.0f;
}
