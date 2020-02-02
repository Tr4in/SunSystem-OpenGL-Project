#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <GL/glew.h>
#include <vector>

void readShaderFile(const std::string filePath, std::string* code);
const GLuint createShader(std::string source, GLenum shader_type);
const GLuint createShaderProgram(GLuint vertex_shader, GLuint fragment_shader);

struct GLResourceContainer {
	std::vector<GLuint> shaders;
	std::vector<GLuint> programs;

	void releaseResources() {

		for (GLuint program : programs) {
			glDeleteProgram(program);
		}

		for (GLuint shader : shaders) {
			glDeleteShader(shader);
		}

		glDisable(GL_DEPTH_TEST);
	}
};