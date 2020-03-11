#include "Circle.h"

Circle::Circle(float radius)
{
	glGenBuffers(1, &this->vbo);
	glGenVertexArrays(1, &this->vao);
	this->radius = radius;
	generateVertrices();
	setBufferData();
}

void Circle::generateVertrices() {

	for (float angle = 0.0f; angle > -359.0f; angle-=2) {
		this->vertrices.insert(
			this->vertrices.end(),
			{
				this->radius * glm::cos(glm::radians(angle)),
				0.0f,
				this->radius * glm::sin(glm::radians(angle))
			}
		);
	}
}

void Circle::setBufferData() {
	glBindVertexArray(this->vao);

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, this->vertrices.size() * sizeof(float), this->vertrices.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Circle::draw()
{
	glBindVertexArray(this->vao);
	glUniformMatrix4fv(MODEL_MATRIX_LOCATION, 1, false, glm::value_ptr(glm::mat4(1.0f)));
	glUniform3fv(COLOR_LOCATION, 1, glm::value_ptr(glm::vec3(1.0f)));
	glDrawArrays(GL_LINE_LOOP, 0, this->vertrices.size() / 3);
	glBindVertexArray(0);
}
