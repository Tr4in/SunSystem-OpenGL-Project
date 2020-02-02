#include "Annulus.h"

Annulus::Annulus(float innerRadius, float outerRadius, glm::mat4 model_matrix, glm::vec3 color)
{
	glGenBuffers(1, &this->vbo_vertrices);
	glGenBuffers(1, &this->vbo_indices);
	glGenVertexArrays(1, &this->vao);
	this->innerRadius = innerRadius;
	this->outerRadius = outerRadius;
	this->model_matrix = model_matrix;
	this->color = color;
	generateVertricesAndIndices();
	setBufferData();
}

void Annulus::generateVertricesAndIndices() {

	// Inner and Outer Circle Vertrices
	for (float angle = 0.0f; angle < 360.0f; angle++) {
		
		float cos_value = glm::cos(glm::radians(angle));
		float sin_value = glm::sin(glm::radians(angle));

		this->vertrices.insert(
			this->vertrices.end(),
			{
				this->innerRadius * cos_value,
				0.0f,
				this->innerRadius * sin_value
			}
		);

		this->vertrices.insert(
			this->vertrices.end(),
			{
				this->outerRadius * cos_value,
				0.0f,
				this->outerRadius * sin_value
			}
		);
	}

	unsigned int vertrices_count = this->vertrices.size() / 3;

	// Indices
	for (unsigned int index = 0; index < vertrices_count - 2; index += 2) {
		this->indices.insert(
			this->indices.end(),
			{
				index, index + 3, index + 1,
				index, index + 2, index + 3
			}
		);
	}

	this->indices.insert(
		this->indices.end(),
		{
			0, vertrices_count - 1, vertrices_count - 2,
			0, 1, vertrices_count - 1
		}
	);


	for (unsigned int index = 0; index < vertrices_count - 2; index += 2) {
		this->indices.insert(
			this->indices.end(),
			{
				index, index + 1, index + 3,
				index, index + 3, index + 2
			}
		);
	}

	this->indices.insert(
		this->indices.end(),
		{
			0, vertrices_count - 2, vertrices_count - 1,
			0, vertrices_count - 1, 1
		}
	);
}

void Annulus::setBufferData() {
	glBindVertexArray(this->vao);

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo_vertrices);
	glBufferData(GL_ARRAY_BUFFER, this->vertrices.size() * sizeof(float), this->vertrices.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->vbo_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), this->indices.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Annulus::draw()
{
	glBindVertexArray(this->vao);
	glUniformMatrix4fv(MODEL_MATRIX_LOCATION, 1, false, glm::value_ptr(this->model_matrix));
	glUniform3fv(COLOR_LOCATION, 1, glm::value_ptr(this->color));
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

glm::mat4 Annulus::getModelMatrix() const
{
	return this->model_matrix;
}

void Annulus::setModelMatrix(glm::mat4 model_matrix)
{
	this->model_matrix = model_matrix;
}
