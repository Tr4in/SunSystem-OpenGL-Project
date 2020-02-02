#pragma once
#include "Shape.h"

class Cylinder : public Shape {

private:
	float height;
	float radius;
	unsigned int segments;
public:
	Cylinder(float height, float radius, unsigned int segments, glm::mat4 model_matrix, Texture& texture, unsigned int texture_unit);
	void initVertricesAndIndices();
};