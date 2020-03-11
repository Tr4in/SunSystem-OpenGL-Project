#include "ArcballCamera.h"

ArcballCamera::ArcballCamera(float radius, glm::mat4 projMatrix) : radius(radius), projMatrix(projMatrix) { 
	this->cameraMatrix = glm::translate(glm::vec3(0.0f, 0.0f, radius));
	this->viewMatrix = glm::inverse(this->cameraMatrix);
}

void ArcballCamera::updatePosition(float mouseX, float mouseY, float zoom, bool left_mouse_clicked, bool right_mouse_clicked) {

	this->radius = zoom;

	if (left_mouse_clicked) {
		glm::vec2 drag_vec = glm::vec2(mouseX, mouseY);

		float x_diff = drag_vec.x - origin.x;
		float y_diff = drag_vec.y - origin.y;
	

		float tempPhi = (x_diff / WINDOW_WIDTH) * 2 * (float)M_PI;
		float tempTheta = (float)(y_diff / WINDOW_HEIGHT) * (float)M_PI;

		this->currentPhi = this->phi + tempPhi;
		this->currentTheta = this->theta + tempTheta;

		if (this->currentPhi >= 2 * M_PI)
			this->currentPhi -= 2 * (float)M_PI;

		if (glm::abs(this->currentTheta) >= M_PI/2)
			this->currentTheta = this->currentTheta < 0 ? (float)-M_PI/2 : (float)M_PI/2;

		this->position = glm::vec3(
			this->radius * glm::sin(this->currentTheta) * glm::cos(this->currentPhi),
			this->radius * glm::sin(this->currentTheta) * glm::sin(this->currentPhi),
			this->radius * glm::cos(this->currentTheta)
		);
	}
	
	if(!left_mouse_clicked && !right_mouse_clicked) {
		this->origin = glm::vec2(mouseX, mouseY);
		this->phi = this->currentPhi;
		this->theta = this->currentTheta;
	}

	if (right_mouse_clicked) {
		this->strafeX = this->currentStrafeX - (mouseX - this->origin.x);
		this->strafeY = this->currentStrafeY + (mouseY - this->origin.y);
	}

	if (!right_mouse_clicked) {
		this->currentStrafeX = strafeX;
		this->currentStrafeY = strafeY;
	}
		
}

glm::vec3 ArcballCamera::getPosition() {
	return this->cameraMatrix * glm::vec4(this->position, 1.0f);
}

glm::mat4 ArcballCamera::getViewMatrix() const {
	return glm::inverse(
		glm::rotate(this->currentPhi, glm::vec3(0, 1, 0)) 
		* glm::rotate(this->currentTheta, glm::vec3(1, 0, 0)) 
		* glm::translate(glm::vec3(strafeX, strafeY, this->radius))
	);
}

glm::mat4 ArcballCamera::getProjViewMatrix() const {
	return this->projMatrix * getViewMatrix();
}
