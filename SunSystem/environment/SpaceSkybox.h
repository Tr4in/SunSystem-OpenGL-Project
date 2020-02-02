#pragma once
#include <GL/glew.h>
#include <list>
#include "../texture_reader/stb_image.h"
#include "../Constants.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class SpaceSkybox {

private:
	unsigned int vbo;
	unsigned int vao;
	std::vector<float> vertrices;
	unsigned int textureID;
	glm::mat4 model_matrix;
public:
	SpaceSkybox(std::list<std::string> filenames, glm::mat4 model_matrix);
	void draw();
};