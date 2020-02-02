#pragma once

class PointLight {
private:
	glm::vec3 position;
	glm::vec3 intensity;
	glm::vec3 attenuation;

public:
	PointLight(glm::vec3 position, glm::vec3 intensity, glm::vec3 attenuation) {
		this->position = position;
		this->intensity = intensity;
		this->attenuation = attenuation;
	}

	glm::vec3 getPosition() {
		return this->position;
	}

	glm::vec3 getIntesity() {
		return this->intensity;
	}

	glm::vec3 getAttenuation() {
		return this->attenuation;
	}
};