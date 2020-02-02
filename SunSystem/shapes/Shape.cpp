#include "Shape.h"

Shape::Shape(Texture& texture, glm::mat4 model_matrix, unsigned int texture_unit) {
	glGenBuffers(4, this->vbo);
	glGenTextures(1, &this->texture_id);
	glGenVertexArrays(1, &this->vao);
	this->model_matrix = model_matrix;
	this->texture_data = texture.data;
	this->texture_width = texture.width;
	this->texture_height = texture.height;
	this->texture_unit = texture_unit;
}

void Shape::setBufferData() {
	
	glBindTexture(GL_TEXTURE_2D, this->texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->texture_width, this->texture_height, 0, GL_RGB, GL_UNSIGNED_BYTE, this->texture_data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	
	glBindVertexArray(this->vao);

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, this->vertrices.size() * sizeof(float), this->vertrices.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, this->normals.size() * sizeof(float), this->normals.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(NORMALS_LOCATION);
	glVertexAttribPointer(NORMALS_LOCATION, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, this->textureCoordinates.size() * sizeof(float), this->textureCoordinates.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(TEXTURE_COORDINATE_LOCATION);
	glVertexAttribPointer(TEXTURE_COORDINATE_LOCATION, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->vbo[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), this->indices.data(), GL_STATIC_DRAW);
	
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Shape::draw() {
	glActiveTexture(GL_TEXTURE0 + this->texture_unit);
	glBindTexture(GL_TEXTURE_2D, this->texture_id);
	glUniformMatrix4fv(MODEL_MATRIX_LOCATION, 1, false, glm::value_ptr(this->model_matrix));
	glBindVertexArray(this->vao);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0 + this->texture_unit);
	glBindTexture(GL_TEXTURE_2D, this->texture_id);
}

void Shape::setModelMatrix(glm::mat4 model_matrix) {
	this->model_matrix = model_matrix;
}

glm::mat4 Shape::getModelMatrix() const {
	return this->model_matrix;
}

Shape::~Shape() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(3, vbo);
	this->vertrices.~vector();
	this->indices.~vector();
	this->normals.~vector();
}