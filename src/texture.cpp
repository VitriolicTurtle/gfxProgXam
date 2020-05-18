#include "..\include\texture.h"

ObjTexture::~ObjTexture() {
    unbind();
    glDeleteTextures(1, &textureID);
}

ObjTexture::ObjTexture(const char* filename) {
    stbi_set_flip_vertically_on_load(false);									// OpenGL starts textures from bottom left, so we need to turn it upside down


    //  Allocate Memory on the GPU
    int twidth, theight, nrComponents;
    unsigned char* image = stbi_load(filename, &twidth, &theight, &nrComponents, 4);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    glActiveTexture(GL_TEXTURE0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, twidth, theight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    if (image) { stbi_image_free(image); }
}

ObjTexture::ObjTexture(const char* filename, bool flipImage) {
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    //  Allocate Memory on the GPU
    int twidth, theight, nrComponents;
    stbi_set_flip_vertically_on_load(flipImage);
    unsigned char* image = stbi_load(filename, &twidth, &theight, &nrComponents, STBI_default);
    if (!image) {
        GFX_WARN("stb_image cannot load image: %s", filename);
        glBindTexture(GL_TEXTURE_2D, 0);
        return;
    }
    GLenum format;
    if (nrComponents == 1)
        format = GL_RED;
    else if (nrComponents == 3)
        format = GL_RGB;
    else if (nrComponents == 4)
        format = GL_RGBA;
    // target | lod | internal_format | width | height | border | format | type | data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, twidth, theight, 0, format, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D); // Generate MipMaps to use
    stbi_image_free(image); // Free the data read from file after creating OpenGL texture 

    // Set these parameters to avoid a black screen caused by improperly mipmapped textures
    glActiveTexture(GL_TEXTURE0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
}

ObjTexture::ObjTexture(ObjTexture&& other) : textureID(std::move(other.textureID)) {     }

ObjTexture& ObjTexture::operator=(ObjTexture&& other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    glDeleteTextures(1, &textureID);
    textureID = std::move(other.textureID);
    other.textureID = 0u;

    return *this;
}

void ObjTexture::update(int width, int height, void* data) {
    bind();
    // target | lod | xoffset | yoffset | width | height | format | type | data
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_FLOAT, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    unbind();
}

void ObjTexture::setTex(GLuint tempTex) {
    textureID = tempTex;
}
