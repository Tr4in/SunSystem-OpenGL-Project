#include "SceneSettings.h"
#include "Constants.h"

void SceneSettings::setTransform(GLuint shader_program, glm::mat4 matrix) {
	glUseProgram(shader_program);
	glUniformMatrix4fv(MODEL_MATRIX_LOCATION, 1, false, glm::value_ptr(matrix));
	glUseProgram(0);
}

void SceneSettings::setProjViewMatrix(GLuint shader_program, glm::mat4 matrix) {
	glUseProgram(shader_program);
	glUniformMatrix4fv(PROJ_VIEW_MATRIX_LOCATION, 1, false, glm::value_ptr(matrix));
	glUseProgram(0);

	projViewMatrix = matrix;
}

void SceneSettings::setCameraPosition(GLuint shader_program, glm::vec3 camera_position) {
	glUseProgram(shader_program);
	glUniform3fv(CAMERA_POSITION_LOCATION, 1, glm::value_ptr(camera_position));
	glUseProgram(0);
}

void SceneSettings::setDirectionalLightSource(GLuint shader_program, DirectionalLight& directionalLight) {
	glUseProgram(shader_program);
	glUniform3fv(DIRECTIONAL_LIGHT_SOURCE_DIRECTION_LOCATION, 1, glm::value_ptr(directionalLight.getDirection()));
	glUniform3fv(DIRECTIONAL_LIGHT_INTENSITY_LOCATION, 1, glm::value_ptr(directionalLight.getIntesity()));
	glUseProgram(0);
}

void SceneSettings::setPointLightSource(GLuint shader_program, PointLight& pointLight) {
	glUseProgram(shader_program);
	glUniform3fv(POINT_LIGHT_SOURCE_POSITION_LOCATION, 1, glm::value_ptr(pointLight.getPosition()));
	glUniform3fv(POINT_LIGHT_INTENSITY_LOCATION, 1, glm::value_ptr(pointLight.getIntesity()));
	glUniform3fv(POINT_LIGHT_ATTENUATION_LOCATION, 1, glm::value_ptr(pointLight.getAttenuation()));
	glUseProgram(0);
}

void SceneSettings::setLightConstants(GLuint shader_program, float ambient, float diffuse, float specular, float shininess) {
	glUseProgram(shader_program);
	glUniform1f(AMBIENT_REFLECTION_LOCATION, ambient);
	glUniform1f(DIFFUSE_REFLECTION_LOCATION, diffuse);
	glUniform1f(SPECULAR_REFLECTION_LOCATION, specular);
	glUniform1f(SHININESS_LOCATION, shininess);
	glUseProgram(0);
}