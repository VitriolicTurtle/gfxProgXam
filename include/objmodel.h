#include "constants.h"
#include "mapobj.h"
#include <tiny_obj_loader.h>

class ObjModel : public MapObj {
public:
    glm::vec3 objPos;


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

    void load(const char* filepath_obj, const char* diffuse_path, glm::vec3 position, glm::vec3 size);
    void moveObjModel(float deltaTime);
};
