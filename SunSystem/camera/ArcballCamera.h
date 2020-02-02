#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <glm/glm.hpp>
#include "../Constants.h"
#include <glm/gtx/transform.hpp>

class ArcballCamera {

private:
	float radius;
	float currentPhi = 0.0f;
	float currentTheta = 0.0f;
	float currentStrafeX = 0.0f;
	float currentStrafeY = 0.0f;
	float strafeX = 0.0f;
	float strafeY = 0.0f;
	float phi = 0.0f;
	float theta = 0.0f;

	glm::vec2 origin = glm::vec2(0.0f, 0.0f);
	glm::vec3 position;
	glm::mat4 viewMatrix;
	glm::mat4 projMatrix;
	glm::mat4 cameraMatrix = glm::mat4(1.0f);

public:
	ArcballCamera(const float RADIUS, glm::mat4 projMatrix);
	void updatePosition(float mouseX, float mouseY, float zoom, bool left_mouse_clicked, bool right_mouse_clicked);
	glm::vec3 getPosition();

	glm::mat4 getViewMatrix() const;
	glm::mat4 getProjViewMatrix() const;


};