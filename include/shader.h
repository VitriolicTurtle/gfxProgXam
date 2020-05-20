#pragma once
#include "constants.h"
#include <unordered_map>


class ObjShader {
private:
	std::unordered_map<std::string, int> uniformsCache;
	GLuint shaderProgram;
public:
	ObjShader() {}
	~ObjShader() { unbind(); }
	ObjShader(const char* path_vert_shader, const char* path_frag_shader);
	GLuint load_and_compile_shader(const char* fname, GLenum shaderType);
	void read_shader_src(const char* fname, std::vector<char>& buffer);



	GLuint id() const { return shaderProgram; }
	void bind() { glUseProgram(shaderProgram); }
	void unbind() { glUseProgram(0); }

};