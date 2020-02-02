#include "ShaderUtils.h"

/* SOURCE: https://badvertex.com/2012/11/20/how-to-load-a-glsl-shader-in-opengl-using-c.html */
void readShaderFile(const std::string filePath, std::string* code) {
	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);

	if (!fileStream.is_open()) {
		std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
		*code = "";
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}
	
	fileStream.close();
	*code = content;
}

const GLuint createShader(std::string source, GLenum shader_type) {
	GLuint handle = glCreateShader(shader_type);

	std::unique_ptr<std::string> code = std::make_unique<std::string>();
	readShaderFile(source, code.get());

	if (*code == "") {
		return 0;
	}

	const char* code_ptr = (*code).c_str();

	glShaderSource(handle, 1, &code_ptr, NULL);
	glCompileShader(handle);

	GLint succeded;
	glGetShaderiv(handle, GL_COMPILE_STATUS, &succeded);

	if (succeded == GL_FALSE) {
		GLint logSize;
		glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &logSize);

		std::unique_ptr<GLchar> message = std::make_unique<GLchar>();
		glGetShaderInfoLog(handle, logSize, NULL, message.get());
		
		std::cerr << (shader_type == GL_VERTEX_SHADER ? "VERTEX_SHADER: " : "FRAGMENT_SHADER: ") << "Compile error" << std::endl;
		return 0;
	}

	return handle;
}

const GLuint createShaderProgram(GLuint vertex_shader, GLuint fragment_shader) {
	GLuint shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);


	return shader_program;
}

