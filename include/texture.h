#pragma once
#include "constants.h"


class ObjTexture {
private:
    GLuint textureID;
public:
    ObjTexture() {}
    ~ObjTexture();
    ObjTexture(const char* filename);
    ObjTexture(const char* filename, bool flipImage);                          // Standard texture loading constructor
    ObjTexture(ObjTexture&& other);
    ObjTexture(const ObjTexture&) = delete;
    ObjTexture& operator=(const ObjTexture&) = delete;
    ObjTexture& operator=(ObjTexture&& other) noexcept;
    void update(int width, int height, void* data);
    void setTex(GLuint tempTex);

    GLuint id() const { return textureID; }
    void bind() { glActiveTexture(GL_TEXTURE0 + 0); glBindTexture(GL_TEXTURE_2D, textureID); }
    void unbind() { glBindTexture(GL_TEXTURE_2D, 0); }
};