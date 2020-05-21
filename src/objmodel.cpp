#include "objmodel.h"
#include <iostream>


ObjModel::~ObjModel() noexcept
{
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
    glDeleteVertexArrays(1, &m_vao);
}

ObjModel::ObjModel(ObjModel&& other) :
    m_vbo(other.m_vbo),
    m_ebo(other.m_ebo),
    m_vao(other.m_vao),
    tempTex(std::move(other.tempTex)),
    m_index_count(other.m_index_count)
{
    other.m_vbo = 0u;
    other.m_ebo = 0u;
    other.m_vao = 0u;
    other.m_index_count = 0u;
}

ObjModel& ObjModel::operator=(ObjModel&& other)
{
    /** Protect */
    if (this == &other)
    {
        return *this;
    }

    /** Destroy */
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
    glDeleteVertexArrays(1, &m_vao);

    /** Steal */
    m_vbo = other.m_vbo;
    m_ebo = other.m_ebo;
    m_vao = other.m_vao;
    tempTex = std::move(other.tempTex);
    m_index_count = other.m_index_count;

    /** Clean */
    other.m_vbo = 0u;
    other.m_ebo = 0u;
    other.m_vao = 0u;
    other.m_index_count = 0u;

    return *this;
}


void ObjModel::load(const char* filepath_obj, const char* diffuse_path, glm::vec3 position, glm::vec3 size, bool flying, int climbBorder, float rotate) {

    tempSha = ObjShader("resources/shaders/vertex.vert", "resources/shaders/fragment.frag");
    tempTex = ObjTexture(diffuse_path, true, false);

    this->setPos(position);
    this->setSize(size);
    this->canFly = flying;
    this->yPosCap = climbBorder;
    this->rotationRadian = rotate;
    objPos = getPos();

    tinyobj::attrib_t attributes{};
    std::vector<tinyobj::shape_t> shapes{};
    std::vector<tinyobj::material_t> materials{};
    std::string warning{}, error{};

    if (!tinyobj::LoadObj(&attributes, &shapes, &materials, &error, filepath_obj)) {
        GFX_ERROR("Could not load model: W(%s) E(%s)", warning.c_str(), error.c_str());
    }


    std::vector<Vertex> out_vertices{};
    std::vector<unsigned> out_indices{};
    for (const auto& shape : shapes)
    {
        for (const auto& index : shape.mesh.indices)
        {

            out_vertices.push_back({});
            out_indices.push_back(out_indices.size());

            auto& vertex = out_vertices.back();
            vertex.position = { attributes.vertices[3 * index.vertex_index + 0],
                                   attributes.vertices[3 * index.vertex_index + 1],
                                   attributes.vertices[3 * index.vertex_index + 2] };

            vertex.normals = { attributes.normals[3 * index.normal_index + 0],
                                  attributes.normals[3 * index.normal_index + 1],
                                  attributes.normals[3 * index.normal_index + 2] };

            vertex.texcoord = { attributes.texcoords[2 * index.texcoord_index + 0],
                    attributes.texcoords[2 * index.texcoord_index + 1] };
        }
    }
    /** Set index count */
    m_index_count = out_indices.size();

    /** Create VAO / VBO / EBO */
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * out_vertices.size(), out_vertices.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * out_indices.size(), out_indices.data(), GL_STATIC_DRAW);


    GLint positionID = glGetAttribLocation(tempSha.id(), "position");
    glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(positionID);
    GLint normalID = glGetAttribLocation(tempSha.id(), "normal");
    glVertexAttribPointer(normalID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normals));
    glEnableVertexAttribArray(normalID);
    GLint textureCoordinateID = glGetAttribLocation(tempSha.id(), "uv_coord");
    glVertexAttribPointer(textureCoordinateID, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texcoord));
    glEnableVertexAttribArray(textureCoordinateID);


    this->textureProgramID = &tempTex;
    this->ShaderID = &tempSha;
    this->VertexArrayID = m_vao;
    this->VertexBuffer = m_vbo;
    this->ElementBuffer = m_ebo;
    this->NumVertices = m_index_count;


    GFX_INFO("Loaded model %s (%u vertices).", filepath_obj, out_vertices.size());
}

void ObjModel::moveObjModel(float deltaTime, float timeCapturer, WallObj* map){
    glm::vec3 tempModelPos = getPos();                       // Temporary posisiton used to check the position input before actually performing the repositioning.
    float cameraSpeed = 2.5 * deltaTime;                    //	Sets movement speed.


    if(timeCapturer >= 4.98) movementDirection = rand() % 4 + 1;


    //	Based on random INT: Move in 1 of 4 directions.  (Initially value is 2,   new random values are generated when ghost collides with a wall.) 
    switch (movementDirection) {
    case 1:		tempModelPos += cameraSpeed * modelFront;	            //z+
        directionRadian = 3.141592f;								// Radians are used in rendering function for ghost, it rotates the ghost so that it will face the direction its walking.
        break;
    case 2:		tempModelPos -= cameraSpeed * modelFront;	            //z-
        directionRadian = 0.0f;
        break;
    case 3:		tempModelPos -= glm::normalize(glm::cross(modelFront, modelUp)) * cameraSpeed;
        directionRadian = 1.570796f;
        break;
    case 4:		tempModelPos += glm::normalize(glm::cross(modelFront, modelUp)) * cameraSpeed;
        directionRadian = 4.712388f;
        break;
    }
     

    float heightOffsett = +1.0;

                                                                     // The 4 rows below turn negative pixels into positive.
    float tcpx = tempModelPos.x;                                    
    if (tcpx < 0) tcpx *= -1.0;
    float tcpz = tempModelPos.z;
    if (tcpz < 0) tcpz *= -1.0;
                                                                     // Fetched the colour which is used to calculate height of area.
    float fHeight = (((float)map->heightMap->getPixel(tcpz, tcpx) / (float)100) * 40) * (-1.09);



    if (tempModelPos.y + fallValue < (fHeight + heightOffsett)-10) {
        isGrounded = true;
        fallValue = 0;
        float groundedYpos = (float)(fHeight + heightOffsett);
    }

    //if (fallValue == 0.0f) isGrounded = false;

    if (!canFly) {                                                     // If it cant fly
        tempModelPos.y += fallValue * deltaTime;
        tempModelPos.y = fHeight-20;                                   // Sets the y position to the ground. -20 is because the "mathematical" height is not the same as the graphic shown, so its purely to make it look better.
        if(fHeight > yPosCap) movementDirection = rand() % 4 + 1;      // Limits animals to not be able to climb up high places. (Only able to walk through some walls now because the mathematical heights are not equal to the graphic). And gets new direction.
    }



     setPos(tempModelPos);
     this->objPos = tempModelPos;
     view = glm::lookAt(getPos(), getPos() + modelFront, modelUp);

}




