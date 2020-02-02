#pragma once
#include "Shape.h"
#include <glm/gtx/transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Constants.h"

class Cube : public Shape {

private:
	float width;
	float height;
	float depth;
	void initVertricesAndIndices();

public:
	Cube(float width, float height, float depth, glm::mat4 model_matrix, Texture& texture, unsigned int texture_unit);
	
};