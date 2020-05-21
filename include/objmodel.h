#include "constants.h"
#include "wallobj.h"
#include <tiny_obj_loader.h>

class ObjModel : public MapObj {
public:
    glm::vec3 objPos;
    glm::vec3 modelFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 modelUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 view;
    bool isGrounded = false;
    float groundedYpos = 0;                             //  Holds what Y value will be once model is on the grouns
    float fallValue = -10.0;                            //  Falling speed
    bool canFly = false;
    int yPosCap = 0;		                        	//	Border for how far up the map a model can go. (e.g. fish cant go out of water & duck cant fly) 
    float rotationRadian;                               //  The duck is flipped on load so this is used to flip exclusively that one back to normal


    int movementDirection = 0;
    float directionRadian = 0.0f;

    uint32_t m_vbo{};
    uint32_t m_ebo{};
    uint32_t m_vao{};

    uint32_t m_index_count;


    ObjTexture tempTex{};
    ObjShader tempSha{};
    ObjModel() { }
    ~ObjModel() noexcept;
    ObjModel(const ObjModel&) {}
    ObjModel& operator=(const ObjModel&) = delete;
    ObjModel(ObjModel&& other);
    ObjModel& operator=(ObjModel&& other);

    /**
     * The vertex type used by a model
     */
    struct Vertex
    {
        glm::vec3 position{};
        glm::vec3 normals{};
        glm::vec2 texcoord{};
    };

    void load(const char* filepath_obj, const char* diffuse_path, glm::vec3 position, glm::vec3 size, bool flying, int climbBorder, float rotate);
    void moveObjModel(float deltaTime, float animationTimer, WallObj* map);
};
