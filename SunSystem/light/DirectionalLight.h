#pragma once
#include <glm/gtx/transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Constants.h"

class DirectionalLight {

private:
	glm::vec3 direction;
	glm::vec3 intensity;

public:
	DirectionalLight(glm::vec3 direction, glm::vec3 intensity) {
		this->direction = direction;
		this->intensity = intensity;
	}

	glm::vec3 getDirection() {
		return this->direction;
	}

	glm::vec3 getIntesity() {
		return this->intensity;
	}
};