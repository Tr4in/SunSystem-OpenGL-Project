#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "../Constants.h"

class Circle {
private:
	unsigned int vbo, vao;
	float radius;
	std::vector<float> vertrices;
	void generateVertrices();
	void setBufferData();
public:
	Circle(float radius);
	void draw();
};