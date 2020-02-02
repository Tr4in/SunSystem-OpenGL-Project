#pragma once
#include <GL/glew.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "light/DirectionalLight.h"
#include "light/PointLight.h"

class SceneSettings {

private:
	glm::mat4 projViewMatrix;
public:	
	SceneSettings() {}
	void setTransform(GLuint shader_program, glm::mat4 matrix);
	void setProjViewMatrix(GLuint shader_program, glm::mat4 matrix);
	void setCameraPosition(GLuint shader_program, glm::vec3 camera_position);
	void setDirectionalLightSource(GLuint shader_program, DirectionalLight& directionalLight);
	void setPointLightSource(GLuint shader_program, PointLight& pointLight);
	void setLightConstants(GLuint shader_program, float ambient, float diffuse, float specular, float shininess);
};

