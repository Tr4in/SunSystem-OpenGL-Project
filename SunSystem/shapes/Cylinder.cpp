#include "Cylinder.h"

Cylinder::Cylinder(float height, float radius, unsigned int segments, glm::mat4 model_matrix, Texture& texture, unsigned int texture_unit) : Shape(texture, model_matrix, texture_unit) {
	this->height = height;
	this->radius = radius;
	this->segments = segments;
	this->model_matrix = model_matrix;
	initVertricesAndIndices();
	this->setBufferData();
}

void Cylinder::initVertricesAndIndices() {
	float alpha = glm::radians(360.0f / this->segments);
	float halfCylinderHeight = this->height / 2;

	// DOUBLE THE VERTRICES CIRCLE
	for (int turn = 0; turn < 2; turn++) {
		for (unsigned int segment = 0; segment < this->segments; segment++) {
			float xPos = this->radius * cosf(alpha * -(int)segment);
			float zPos = this->radius * sinf(alpha * -(int)segment);

			this->vertrices.insert(
				this->vertrices.end(),
				{ xPos, halfCylinderHeight, zPos }
			);

			if (turn == 0) {
				this->textureCoordinates.insert(
					this->textureCoordinates.end(),
					{ (float)segment / (float)this->segments , 1.0f }
				);
			}
			else {
				this->textureCoordinates.insert(
					this->textureCoordinates.end(),
					{ 0.5f + 0.5f * cosf(alpha * -(int)segment), 0.5f + 0.5f * sinf(alpha * -(int)segment) }
				);
			}
		}


		for (unsigned int segment = 0; segment < this->segments; segment++) {
			float xPos = this->radius * cosf(alpha * -(int)segment);
			float zPos = this->radius * sinf(alpha * -(int)segment);

			this->vertrices.insert(
				this->vertrices.end(),
				{ xPos, -halfCylinderHeight, zPos }
			);

			if (turn == 0) {
				this->textureCoordinates.insert(
					this->textureCoordinates.end(),
					{ (float)segment / (float)this->segments , 0.0f }
				);
			}
			else {
				this->textureCoordinates.insert(
					this->textureCoordinates.end(),
					{ 0.5f + 0.5f * cosf(alpha * -(int)segment), 0.5f + 0.5f * sinf(alpha * -(int)segment) }
				);
			}
		}
	}

	/* INDICES MANTEL */
	for (unsigned int segment = 0; segment < this->segments; segment++) {
		this->indices.insert(this->indices.end(),
			{ segment, (segment + this->segments), (this->segments + ((segment + this->segments + 1) % this->segments)) }
		);
	}

	for (unsigned int segment = 0; segment < this->segments; segment++) {
		this->indices.insert(this->indices.end(),
			{ segment, this->segments + ((segment + this->segments + 1) % this->segments), (segment + 1) % this->segments }
		);
	}

	unsigned int circleTopIndex = this->vertrices.size() / 3; // Index: 64
	unsigned int circleBottomIndex = circleTopIndex + 1; // Index: 65

	this->vertrices.insert(this->vertrices.end(),
		{ 0.0f, halfCylinderHeight, 0.0f }
	);

	this->vertrices.insert(this->vertrices.end(),
		{ 0.0f, -halfCylinderHeight, 0.0f }
	);

	// INDICES KREISE OBEN UND UNTEN
	for (unsigned int segment = 0; segment < this->segments; segment++) {
		this->indices.insert(this->indices.end(),
			{ circleTopIndex, segment, (segment + 1) % this->segments }
		);
	}
	
	for (unsigned int segment = 0; segment < this->segments; segment++) {
		this->indices.insert(this->indices.end(),
			{ circleBottomIndex, this->segments + ((segment + this->segments + 1) % this->segments), segment + this->segments }
		);
	}

	this->textureCoordinates.insert(
		this->textureCoordinates.end(),
		{ 0.5f, 0.5f }
	);

	this->textureCoordinates.insert(
		this->textureCoordinates.end(),
		{ 0.5f, 0.5f }
	);

	
	std::vector<unsigned int> indices_doubled;

	// INSERT THE DOUBLED INDICES
	for (unsigned int index = 0; index < indices.size(); index++) {
		if (indices.at(index) == circleTopIndex || indices.at(index) == circleBottomIndex)
			indices_doubled.push_back(indices.at(index));

		else if (index >= circleTopIndex + 2 * this->segments)
			indices_doubled.push_back(2 * this->segments + indices.at(index));

		else
			indices_doubled.push_back(indices.at(index));
	}

	indices.clear();
	for (unsigned int index = 0; index < indices_doubled.size(); index++)
		indices.push_back(indices_doubled.at(index));
	
	
	// NORMAL CIRCULAR SURFACE TOP
	for (unsigned int segment = 0; segment < this->segments; segment++) {

		this->normals.insert(
			this->normals.end(),
			{ this->radius * cosf(alpha * -(int)segment), 0.0f,  this->radius * sinf(alpha * -(int)segment) }
		);
	}
	
	// NORMAL CIRCULAR SURFACE BOTTOM
	for (unsigned int segment = 0; segment < this->segments; segment++) {

		this->normals.insert(
			this->normals.end(),
			{ this->radius * cosf(alpha * -(int)segment), 0.0f,  this->radius * sinf(alpha * -(int)segment) }
		);
	}
	
	// NORMALS TOP
	for (unsigned int segment = 0; segment < this->segments; segment++) {

		this->normals.insert(
			this->normals.end(),
			{ 0.0f, halfCylinderHeight, 0.0f }
		);
	}

	// NORMALS BOTTOM
	for (unsigned int segment = 0; segment < this->segments; segment++) {

		this->normals.insert(
			this->normals.end(),
			{ 0.0f, -halfCylinderHeight, 0.0f }
		);
	}

	// NORMAL TOP CIRCLE MIDDLE
	this->normals.insert(
		this->normals.end(),
		{ 0.0f, halfCylinderHeight, 0.0f }
	);

	// NORMAL BOTTOM CIRCLE MIDDLE
	this->normals.insert(
		this->normals.end(),
		{ 0.0f, -halfCylinderHeight, 0.0f }
	);
}
