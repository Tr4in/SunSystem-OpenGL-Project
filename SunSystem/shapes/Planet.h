#pragma once
#include "Shape.h"

class Planet : public Shape {

private:
	float radius;
	unsigned int latitude_segments;
	unsigned int longitude_segments;
	void initVertricesAndIndices();

public:
	Planet(float radius, unsigned int latitude_segments, unsigned int longitude_segments, glm::mat4 model_matrix, Texture& texture, unsigned int texture_unit);
	glm::vec3 getPosition();
};