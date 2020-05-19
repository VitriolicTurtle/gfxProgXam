#pragma once
#include "constants.h"


class ObjTexture {
private:
    GLuint textureID;
    unsigned char* image;
    std::vector<unsigned char> pixelData;
    //  Allocate Memory on the GPU
    int twidth, theight, nrComponents;
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
    int getPixel(int x, int y); 

    GLuint id() const { return textureID; }
    void bind() { glActiveTexture(GL_TEXTURE0 + 0); glBindTexture(GL_TEXTURE_2D, textureID); }
    void unbind() { glBindTexture(GL_TEXTURE_2D, 0); }
};