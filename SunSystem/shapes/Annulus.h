#pragma once

#include "Shape.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "../Constants.h"

class Annulus {
private:
	unsigned int vbo_vertrices, vbo_indices, vao;
	float innerRadius;
	float outerRadius;
	std::vector<float> vertrices;
	std::vector<unsigned int> indices;
	glm::mat4 model_matrix;
	glm::vec3 color;
	void generateVertricesAndIndices();
	void setBufferData();

public:
	Annulus(float innerRadius, float outerRadius, glm::mat4 model_matrix, glm::vec3 color);
	void draw();
	glm::mat4 getModelMatrix() const;
	void setModelMatrix(glm::mat4 model_matrix);
};