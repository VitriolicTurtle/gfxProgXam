#include "..\include\shader.h"

ObjShader::ObjShader(const char* path_vert_shader, const char* path_frag_shader) {
	GLuint vertexShader = load_and_compile_shader(path_vert_shader, GL_VERTEX_SHADER);
	GLuint fragmentShader = load_and_compile_shader(path_frag_shader, GL_FRAGMENT_SHADER);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);
}

GLuint ObjShader::load_and_compile_shader(const char* fname, GLenum shaderType) {

	std::vector<char> buffer;
	read_shader_src(fname, buffer);
	const char* src = &buffer[0];

	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &src, nullptr);

	glCompileShader(shader);
	GLint compileOK;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileOK);
	if (!compileOK) {
		char infolog[1024];
		glGetShaderInfoLog(shader, 1024, nullptr, infolog);
		GFX_ERROR("The program failed to compile with the error: %s", infolog);
	}
	return shader;
}

void ObjShader::read_shader_src(const char* fname, std::vector<char>& buffer) {
	std::ifstream in;
	in.open(fname, std::ios::binary);

	if (in.fail()) {
		GFX_ERROR("Unable to open %s, I'm out!", fname);
	}
	// Get the number of bytes stored in this file
	in.seekg(0, std::ios::end);
	size_t length = (size_t)in.tellg();

	// Go to start of the file
	in.seekg(0, std::ios::beg);

	// Read the content of the file in a buffer
	buffer.resize(length + 1);
	in.read(&buffer[0], length);
	in.close();
	// nullterminate c-string
	buffer[length] = '\0';
}
