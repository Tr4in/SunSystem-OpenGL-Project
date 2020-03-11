#include "Planet.h"

Planet::Planet(float radius, unsigned int latitude_segments, unsigned int longitude_segments, glm::mat4 model_matrix, Texture& texture, unsigned int texture_unit) : Shape(texture, model_matrix, texture_unit) {
	this->radius = radius;
	this->latitude_segments = latitude_segments;
	this->longitude_segments = longitude_segments;
	this->model_matrix = model_matrix;
	initVertricesAndIndices();
	setBufferData();
}

void Planet::initVertricesAndIndices() {
	float latitude_angle = glm::radians(180.0f / this->latitude_segments);
	float longitude_angle = glm::radians(360.0f / this->longitude_segments);

	for (unsigned int latitude_segment = 1; latitude_segment < this->latitude_segments; latitude_segment++) {
		for (unsigned int longitude_segment = 0; longitude_segment < this->longitude_segments; longitude_segment++) {
			this->vertrices.insert(
				this->vertrices.end(),
				{
					this->radius * sinf(latitude_angle * latitude_segment) * cosf(longitude_angle * -(int)longitude_segment),
					this->radius * cosf(latitude_angle * latitude_segment),
					this->radius * sinf(latitude_angle * latitude_segment) * sinf(longitude_angle * -(int)longitude_segment)
				}
			);

			this->normals.insert(
				this->normals.end(),
				{
					this->radius * sinf(latitude_angle * latitude_segment) * cosf(longitude_angle * -(int)longitude_segment),
					this->radius * cosf(latitude_angle * latitude_segment),
					this->radius * sinf(latitude_angle * latitude_segment) * sinf(longitude_angle * -(int)longitude_segment)
				}
			);

			this->textureCoordinates.insert(
				this->textureCoordinates.end(),
				{
					(float)longitude_segment / (float)this->longitude_segments, (float)latitude_segment / (float)this->latitude_segments
				}
			);
		}
	}

	unsigned int overlapped_vertex_start_index = this->vertrices.size() / 3;

	for (unsigned int latitude_segment = 1; latitude_segment < this->latitude_segments; latitude_segment++) {
		for (int longitude_segment = this->longitude_segments - 1; longitude_segment >= 0; longitude_segment--) {

			if (longitude_segment == 0 || longitude_segment == (this->longitude_segments - 1)) {
				this->vertrices.insert(
					this->vertrices.end(),
					{
						this->radius * sinf(latitude_angle * latitude_segment) * cosf(longitude_angle * -(int)longitude_segment),
						this->radius * cosf(latitude_angle * latitude_segment),
						this->radius * sinf(latitude_angle * latitude_segment) * sinf(longitude_angle * -(int)longitude_segment)
					}
				);

				this->normals.insert(
					this->normals.end(),
					{
						this->radius * sinf(latitude_angle * latitude_segment) * cosf(longitude_angle * -(int)longitude_segment),
						this->radius * cosf(latitude_angle * latitude_segment),
						this->radius * sinf(latitude_angle * latitude_segment) * sinf(longitude_angle * -(int)longitude_segment)
					}
				);

				if (longitude_segment == 0) {
					this->textureCoordinates.insert(
						this->textureCoordinates.end(),
						{
							0.01f,  (float)latitude_segment / (float)this->latitude_segments
						}
					);
				}

				else {
					this->textureCoordinates.insert(
						this->textureCoordinates.end(),
						{
							0.0f, (float)latitude_segment / (float)this->latitude_segments
						}
					);
				}
			}
		}
	}

	unsigned int overlapped_vertex_end_index = this->vertrices.size() / 3;

	for (unsigned int latitude_segment = 0; latitude_segment < this->latitude_segments - 2; latitude_segment++) {

		unsigned int longitude_segment;

		for (longitude_segment = latitude_segment * this->longitude_segments; longitude_segment < this->longitude_segments * (latitude_segment + 1) - 1; longitude_segment++) {
			this->indices.insert(
				this->indices.end(),
				{
					longitude_segment,
					longitude_segment + this->longitude_segments,
					longitude_segment + this->longitude_segments + 1
				}
			);
		}

	}

	for (unsigned int latitude_segment = 0; latitude_segment < this->latitude_segments - 2; latitude_segment++) {

		unsigned int longitude_segment;

		for (longitude_segment = latitude_segment * this->longitude_segments; longitude_segment < this->longitude_segments * (latitude_segment + 1) - 1; longitude_segment++) {
			this->indices.insert(
				this->indices.end(),
				{
					longitude_segment,
					longitude_segment + this->longitude_segments + 1,
					longitude_segment + 1
				}
			);

		}
	}

	// ADDITIONAL INDICES SETUP FOR TEXTURE
	for (unsigned int index = overlapped_vertex_start_index; index < overlapped_vertex_end_index - 3; index += 2) {
		this->indices.insert(
			this->indices.end(),
			{ index + 1, index, index + 3 }
		);
	}

	for (unsigned int index = overlapped_vertex_start_index; index < overlapped_vertex_end_index - 3; index += 2) {
		this->indices.insert(
			this->indices.end(),
			{ index, index + 2, index + 3 }
		);
	}

	unsigned int PlanetTopIndex = this->vertrices.size() / 3;
	
	for (unsigned int segment = 0; segment < this->longitude_segments; segment++) {
		this->vertrices.insert(
			this->vertrices.end(),
			{ 0.0f, this->radius, 0.0f }
		);

		this->normals.insert(
			this->normals.end(),
			{ 0.0f, this->radius, 0.0f }
		);

		this->textureCoordinates.insert(
			this->textureCoordinates.end(),
			{ (float)segment / (float)this->longitude_segments, 0.0f }
		);

	}

	unsigned int PlanetBottomIndex = this->vertrices.size() / 3;

	for (unsigned int segment = 0; segment < this->longitude_segments; segment++) {
		this->vertrices.insert(
			this->vertrices.end(),
			{ 0.0f, -this->radius, 0.0f }
		);

		this->normals.insert(
			this->normals.end(),
			{ 0.0f, -this->radius, 0.0f }
		);

		this->textureCoordinates.insert(
			this->textureCoordinates.end(),
			{ (float)segment / (float)this->longitude_segments, 1.0f }
		);
	}

	// TOP Planet POINT
	for (unsigned int index = PlanetTopIndex; index < PlanetBottomIndex; index++) {
		for (unsigned int segment = 0; segment < this->longitude_segments; segment++) {
			this->indices.insert(this->indices.end(),
				{ index, segment, (segment + 1) % this->longitude_segments }
			);
		}
	}

	// BOTTOM Planet POINT
	for (unsigned int index = PlanetBottomIndex; index < this->vertrices.size() / 3; index++) {
		for (unsigned int segment = (this->latitude_segments - 2) * this->longitude_segments; segment < this->longitude_segments * (this->latitude_segments - 1); segment++) {
			this->indices.insert(this->indices.end(),
				{
					index,
					((segment + 1) % (this->longitude_segments * (this->latitude_segments - 1))) == 0 ? (this->latitude_segments - 2) * this->longitude_segments : segment + 1,
					segment
				}
			);
		}
	}

}