#include "player.h"

void Player::movePlayer(Window* window, float deltaTime){
    
    glm::vec3 tempCamPos = this->getPos();
    float cameraSpeed = 6.5 * deltaTime;                   
    bool move = true;


    // Add the force of gravity
    force += glm::vec3(0.0f, -98.1f, 0.0f);
    velocity += (force * deltaTime);
    translate += (velocity * deltaTime);

    // Make sure we don't fall through the terrain
    /*
    if (1 != NULL)
    {
        float fHeight = m_pTerrain->GetHeightAt(m_Translate);
        if (m_Translate.y < (fHeight + m_fHeightOffset))
        {
            m_bIsOnGround = true;
            m_Translate.y = fHeight + m_fHeightOffset;
        }
    }
    */
    // Reset the force vector
   // m_Force = glm::vec3(0);
    // Slow down our movement by friction amount
  //  const float fTargetFrameRate = 60.0f;
//    m_Velocity *= powf(m_fFriction, fTargetFrameRate * fDeltaTime);




    if (glfwGetKey(window->window, GLFW_KEY_W) == GLFW_PRESS)      
        tempCamPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window->window, GLFW_KEY_S) == GLFW_PRESS)      
        tempCamPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window->window, GLFW_KEY_A) == GLFW_PRESS)      
        tempCamPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;   
    if (glfwGetKey(window->window, GLFW_KEY_D) == GLFW_PRESS) {      
        tempCamPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    

    moveView(window, deltaTime);



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
