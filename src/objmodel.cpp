#include "objmodel.h"



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


void ObjModel::load(const char* filepath_obj, const char* diffuse_path, glm::vec3 position, glm::vec3 size) {

    tempSha = ObjShader("resources/shaders/vertex.vert", "resources/shaders/fragment.frag");
    tempTex = ObjTexture(diffuse_path, true, false);

    this->setPos(position);
    this->setSize(size);
    objPos = getPos();

    //--------------------------------------------------comment out here
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



