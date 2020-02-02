#pragma once
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <glm/gtx/transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Constants.h"
#include "../Texture.h"

class Shape {

protected:
	GLuint vao;
	GLuint vbo[4];
	GLuint texture_id;

	unsigned char* texture_data;
	unsigned int texture_width;
	unsigned int texture_height;
	unsigned int texture_unit;

	glm::mat4 model_matrix;
	std::vector<float> vertrices;
	std::vector<unsigned int> indices;
	std::vector<float> normals;
	std::vector<float> textureCoordinates;

	virtual void initVertricesAndIndices() = 0;
	void setBufferData();

public:
	Shape(Texture& texture, glm::mat4 model_matrix, unsigned int texture_unit);
	void setModelMatrix(glm::mat4 model_matrix);
	glm::mat4 getModelMatrix() const;
	void draw();
	~Shape();
};