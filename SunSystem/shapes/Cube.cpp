#include "Cube.h"

Cube::Cube(float width, float height, float depth, glm::mat4 model_matrix, Texture& texture, unsigned int texture_unit) : Shape(texture, model_matrix, texture_unit) {
	this->width = width;
	this->height = height;
	this->depth = depth;
	this->model_matrix = model_matrix;
	initVertricesAndIndices();
	this->setBufferData();
}

void Cube::initVertricesAndIndices() {
	
	float halfWidth = this->width / 2;
	float halfHeight = this->height / 2;
	float halfDepth = this->depth / 2;

	this->vertrices = {
		-halfWidth, -halfHeight, halfDepth, // 0
		halfWidth, -halfHeight, halfDepth,  // 1
		-halfWidth, halfHeight, halfDepth, // 2
		halfWidth, halfHeight, halfDepth, // 3
		halfWidth, halfHeight, -halfDepth, // 4
		-halfWidth, halfHeight, -halfDepth, // 5
		-halfWidth, -halfHeight, -halfDepth, // 6
		halfWidth, -halfHeight, -halfDepth, // 7

		-halfWidth, -halfHeight, halfDepth, // 8
		halfWidth, -halfHeight, halfDepth,  // 9
		-halfWidth, halfHeight, halfDepth, // 10
		halfWidth, halfHeight, halfDepth, // 11
		halfWidth, halfHeight, -halfDepth, // 12
		-halfWidth, halfHeight, -halfDepth, // 13
		-halfWidth, -halfHeight, -halfDepth, // 14
		halfWidth, -halfHeight, -halfDepth, // 15

		-halfWidth, -halfHeight, halfDepth, // 16
		halfWidth, -halfHeight, halfDepth,  // 17
		-halfWidth, halfHeight, halfDepth, // 18
		halfWidth, halfHeight, halfDepth, // 19
		halfWidth, halfHeight, -halfDepth, // 20
		-halfWidth, halfHeight, -halfDepth, // 21
		-halfWidth, -halfHeight, -halfDepth, // 22
		halfWidth, -halfHeight, -halfDepth  // 23
	};

	this->indices = {
		0, 1, 3,
		0, 3, 2,

		17, 7, 4,
		17, 4, 19,

		23, 6, 5,
		23, 5, 20,

		22, 16, 18,
		22, 18, 21,

		10, 11, 12,
		10, 12, 13,

		8, 15, 9,
		8, 14, 15
	};

	std::vector<unsigned int> indices_for_normals = {

		0, 1, 2, 3, // 0
		0, 1, 2, 3, // 1
		0, 1, 2, 3, // 2
		0, 1, 2, 3, // 3
		1, 7, 3, 4, // 4
		7, 6, 4, 5, // 5
		7, 6, 4, 5, // 6
		1, 7, 3, 4, // 7

		0, 6, 1, 7, // 8
		0, 6, 1, 7, // 9
		2, 3, 5, 4, // 10
		2, 3, 5, 4, // 11
		2, 3, 5, 4, // 12
		2, 3, 5, 4, // 13
		0, 6, 1, 7, // 14
		0, 6, 1, 7, // 15

		0, 2, 6, 5, // 16
		1, 7, 3, 4, // 17
		0, 2, 6, 5, // 18
		1, 7, 3, 4, // 19
		7, 6, 4, 5, // 20
		0, 2, 6, 5, // 21
		0, 2, 6, 5, // 22
		7, 6, 4, 5, // 23
	};

	glm::vec3 cross_vector;
	
	for (unsigned int index = 0; index < (indices_for_normals.size() / 4); index++) {
		
		unsigned int vertex_pos1 = indices_for_normals.at(index * 4) * 3;
		unsigned int vertex_pos2 = indices_for_normals.at(index * 4 + 1) * 3;
		unsigned int vertex_pos3 = indices_for_normals.at(index * 4 + 2) * 3;

		float* vertex1 = &this->vertrices.at(vertex_pos1);
		float* vertex2 = &this->vertrices.at(vertex_pos2);
		float* vertex3 = &this->vertrices.at(vertex_pos3);

		glm::vec3 v1 = glm::vec3(*vertex1, *(vertex1 + 1), *(vertex1 + 2));
		glm::vec3 v2 = glm::vec3(*vertex2, *(vertex2 + 1), *(vertex2 + 2));
		glm::vec3 v3 = glm::vec3(*vertex3, *(vertex3 + 1), *(vertex3 + 2));

		glm::vec3 v1ToV2 = v2 - v1;
		glm::vec3 v1ToV3 = v3 - v1;

		cross_vector = glm::cross(v1ToV2, v1ToV3);

		this->normals.insert(this->normals.end(), { cross_vector.x, cross_vector.y, cross_vector.z });
	}

	/* UV KOORDINATEN */
	this->textureCoordinates.insert(
		this->textureCoordinates.end(),
		{	
			0.0f, 0.0f, // 0
			1.0f, 0.0f, // 1
			0.0f, 1.0f, // 2
			1.0f, 1.0f, // 3
			1.0f, 1.0f, // 4
			1.0f, 1.0f, // 5
			1.0f, 0.0f, // 6
			1.0f, 0.0f, // 7

			0.0f, 0.0f, // 8
			1.0f, 0.0f, // 9
			0.0f, 0.0f, // 10
			1.0f, 0.0f, // 11
			1.0f, 1.0f, // 12
			0.0f, 1.0f, // 13
			0.0f, 1.0f, // 14
			1.0f, 1.0f, // 15

			0.0f, 0.0f, // 16
			0.0f, 0.0f, // 17
			0.0f, 1.0f, // 18
			0.0f, 1.0f, // 19
			0.0f, 1.0f, // 20
			1.0f, 1.0f, // 21
			1.0f, 0.0f, // 22
			0.0f, 0.0f  // 23
		}
	);
	
}
