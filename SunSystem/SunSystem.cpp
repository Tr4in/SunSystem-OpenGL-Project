#include "DebugUtils.h"
#include <GLFW/glfw3.h>
#include <list>
#include "ShaderUtils.h"
#include "camera/ArcballCamera.h"
#include "Constants.h"
#include "SceneSettings.h"
#include "glm/glm/glm.hpp"
#include "shapes/Cube.h"
#include "shapes/Cylinder.h"
#include "shapes/Planet.h"
#include "shapes/Circle.h"
#include "shapes/Annulus.h"
#include "light/DirectionalLight.h"
#include "environment/SpaceSkybox.h"
#define STB_IMAGE_IMPLEMENTATION
#include "texture_reader/stb_image.h"


/* --------------------------------------------- */
// Prototypes
/* --------------------------------------------- */
void createWindow(GLFWwindow** window, const int WIDTH, const int HEIGHT);
void key_press_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_action_callback(GLFWwindow* window, int button, int action, int mods);
void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void releaseResources();
void loadTextureResources(std::list<std::string>& textureNameList, std::vector<Texture>& textures);

/* --------------------------------------------- */
// Global variables
/* --------------------------------------------- */
struct GLResourceContainer resources;
double mouse_x = 0;
double mouse_y = 0;

ArcballCamera camera(4.0f, glm::perspective(glm::radians(FOV), float(WINDOW_WIDTH) / float(WINDOW_HEIGHT), ZNEAR, ZFAR));

bool left_mouse_clicked = false;
bool right_mouse_clicked = false;
float zoom = 50.0f;
bool wire_frame_mode = false;
bool back_face_culling_mode = true;
SceneSettings sceneSettings;

/* --------------------------------------------- */
// Main
/* --------------------------------------------- */

int main(int argc, char** argv)
{

	/* --------------------------------------------- */
	// Create Window
	/* --------------------------------------------- */
	GLFWwindow *window = nullptr;
	createWindow(&window, WINDOW_WIDTH, WINDOW_HEIGHT);

	/* --------------------------------------------- */
	// Load all OpenGL extensions
	/* --------------------------------------------- */
	glewExperimental = true;

	if (glewInit() != GLEW_OK) {
		std::cerr << "Error: Could not load glew context!" << std::endl;
		releaseResources();
		exit(EXIT_FAILURE);
	}

	#if _DEBUG
		glDebugMessageCallback(DebugCallback, NULL);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	#endif

	/* --------------------------------------------- */
	// Initialize scene and render loop
	/* --------------------------------------------- */

	GLuint vertex_shader_phong_shading = createShader("assets/shader/vertex_shader_phong.vs", GL_VERTEX_SHADER);
	GLuint fragment_shader_phong_shading = createShader("assets/shader/fragment_shader_phong.fs", GL_FRAGMENT_SHADER);

	if (vertex_shader_phong_shading == 0 || fragment_shader_phong_shading == 0) {
		releaseResources();
		exit(EXIT_FAILURE);
	}

	GLuint shader_program_phong_shading = createShaderProgram(vertex_shader_phong_shading, fragment_shader_phong_shading);

	if (shader_program_phong_shading == 0) {
		releaseResources();
		exit(EXIT_FAILURE);
	}

	resources.shaders.push_back(vertex_shader_phong_shading);
	resources.shaders.push_back(fragment_shader_phong_shading);

	resources.programs.push_back(shader_program_phong_shading);


	GLuint vertex_shader_skybox = createShader("assets/shader/vertex_shader_skybox.vs", GL_VERTEX_SHADER);
	GLuint fragment_shader_skybox = createShader("assets/shader/fragment_shader_skybox.fs", GL_FRAGMENT_SHADER);

	if (vertex_shader_skybox == 0 || fragment_shader_skybox == 0) {
		releaseResources();
		exit(EXIT_FAILURE);
	}

	GLuint shader_program_skybox = createShaderProgram(vertex_shader_skybox, fragment_shader_skybox);

	if (shader_program_skybox == 0) {
		releaseResources();
		exit(EXIT_FAILURE);
	}

	resources.shaders.push_back(vertex_shader_skybox);
	resources.shaders.push_back(fragment_shader_skybox);

	resources.programs.push_back(shader_program_skybox);


	GLuint vertex_shader_primitive = createShader("assets/shader/vertex_shader_primitive.vs", GL_VERTEX_SHADER);
	GLuint fragment_shader_primitive = createShader("assets/shader/fragment_shader_primitive.fs", GL_FRAGMENT_SHADER);

	if (vertex_shader_primitive == 0 || fragment_shader_primitive == 0) {
		releaseResources();
		exit(EXIT_FAILURE);
	}

	GLuint shader_program_primitive = createShaderProgram(vertex_shader_primitive, fragment_shader_primitive);

	if (shader_program_primitive == 0) {
		releaseResources();
		exit(EXIT_FAILURE);
	}

	resources.shaders.push_back(vertex_shader_primitive);
	resources.shaders.push_back(fragment_shader_primitive);

	resources.programs.push_back(shader_program_primitive);


	GLuint vertex_shader_sun = createShader("assets/shader/vertex_shader_sun.vs", GL_VERTEX_SHADER);
	GLuint fragment_shader_sun = createShader("assets/shader/fragment_shader_sun.fs", GL_FRAGMENT_SHADER);

	if (vertex_shader_sun == 0 || fragment_shader_sun == 0) {
		releaseResources();
		exit(EXIT_FAILURE);
	}

	GLuint shader_program_sun = createShaderProgram(vertex_shader_sun, fragment_shader_sun);

	if (shader_program_sun == 0) {
		releaseResources();
		exit(EXIT_FAILURE);
	}

	resources.shaders.push_back(vertex_shader_sun);
	resources.shaders.push_back(fragment_shader_sun);

	resources.programs.push_back(shader_program_sun);

	/* --------------------------------------------- */
	// Scene Settings
	/* --------------------------------------------- */

	glClearColor(0, 0, 0, 255);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	/* --------------------------------------------- */
	// Textures
	/* --------------------------------------------- */
	std::vector<Texture> textureVector;
	std::list<std::string> textureNames = {
		"sunmap.jpg", "mercurymap.jpg", "venusmap.jpg", "earthmap.jpg", 
		"marsmap.jpg", "jupitermap.jpg", "saturnmap.jpg", 
		"uranusmap.jpg", "neptunemap.jpg" };

	loadTextureResources(textureNames, textureVector);
	
	/* --------------------------------------------- */
	// Shapes
	/* --------------------------------------------- */

	glm::mat4 saturn_model_matrix = glm::rotate((float)rand() * 360, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::translate(glm::vec3(0.0f, 0.0f, -SATURN_DISTANCE));

	Planet sun(9.0f, 32, 64, glm::translate(glm::vec3(0.0f, 0.0f, 0.0f)), textureVector.at(0), 0);
	Planet mercury(1.0f, 32, 64, glm::rotate((float)rand() * 360, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::translate(glm::vec3(0.0f, 0.0f, -MERCURY_DISTANCE)), textureVector.at(1), 0);
	Planet venus(1.5f, 32, 64, glm::rotate((float)rand() * 360, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::translate(glm::vec3(0.0f, 0.0f, -VENUS_DISTANCE)), textureVector.at(2), 0);
	Planet earth(1.0f, 32, 64, glm::rotate((float)rand() * 360, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::translate(glm::vec3(0.0f, 0.0f, -EARTH_DISTANCE)), textureVector.at(3), 0);
	Planet mars(0.5f, 32, 64, glm::rotate((float)rand() * 360, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::translate(glm::vec3(0.0f, 0.0f, -MARS_DISTANCE)), textureVector.at(4), 0);
	Planet jupiter(4.0f, 32, 64, glm::rotate((float)rand() * 360, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::translate(glm::vec3(0.0f, 0.0f, -JUPITER_DISTANCE)), textureVector.at(5), 0);
	Planet saturn(3.0f, 32, 64, saturn_model_matrix, textureVector.at(6), 0);
	Planet uranus(2.0f, 32, 64, glm::rotate((float)rand() * 360, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::translate(glm::vec3(0.0f, 0.0f, -URANUS_DISTANCE)), textureVector.at(7), 0);
	Planet neptune(2.0f, 32, 64, glm::rotate((float)rand() * 360, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::translate(glm::vec3(0.0f, 0.0f, -NEPTUNE_DISTANCE)), textureVector.at(8), 0);

	Circle mercuryCircle(MERCURY_DISTANCE);
	Circle venusCircle(VENUS_DISTANCE);
	Circle earthCircle(EARTH_DISTANCE);
	Circle marsCircle(MARS_DISTANCE);
	Circle jupiterCircle(JUPITER_DISTANCE);
	Circle saturnCircle(SATURN_DISTANCE);
	Circle uranusCircle(URANUS_DISTANCE);
	Circle neptuneCircle(NEPTUNE_DISTANCE);

	Annulus saturn_ring(SATURN_RING_INNER_RADIUS, SATURN_RING_OUTER_RADIUS, saturn_model_matrix, glm::vec3(0.5f, 0.5f, 0.5f));

	// Release Textures and Texture-Name-List
	textureNames.clear();
	textureVector.clear();

	/* --------------------------------------------- */
	// Environment
	/* --------------------------------------------- */
	std::list<std::string> skyBoxFilenames = {
		"starfield_rt.tga",
		"starfield_lf.tga",
		"starfield_up.tga",
		"starfield_dn.tga",
		"starfield_ft.tga",
		"starfield_bk.tga"
	};

	SpaceSkybox space(skyBoxFilenames, glm::scale(glm::vec3(SKYBOX_SCALE_FACTOR)));

	// Release list-data
	skyBoxFilenames.clear();

	/* --------------------------------------------- */
	// Lights
	/* --------------------------------------------- */
	DirectionalLight directionalLight(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	PointLight pointLight(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	sceneSettings.setDirectionalLightSource(shader_program_phong_shading, directionalLight);
	sceneSettings.setPointLightSource(shader_program_phong_shading, pointLight);
	sceneSettings.setDirectionalLightSource(shader_program_sun, directionalLight);
	sceneSettings.setPointLightSource(shader_program_sun, pointLight);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		sceneSettings.setCameraPosition(shader_program_phong_shading, camera.getPosition());
		sceneSettings.setCameraPosition(shader_program_sun, camera.getPosition());
		sceneSettings.setProjViewMatrix(shader_program_skybox, camera.getProjViewMatrix());
		sceneSettings.setProjViewMatrix(shader_program_primitive, camera.getProjViewMatrix());
		sceneSettings.setProjViewMatrix(shader_program_sun, camera.getProjViewMatrix());

		glfwGetCursorPos(window, &mouse_x, &mouse_y);
		camera.updatePosition((float)mouse_x, (float)mouse_y, zoom, left_mouse_clicked, right_mouse_clicked);

		sceneSettings.setProjViewMatrix(shader_program_phong_shading, camera.getProjViewMatrix());

		sceneSettings.setLightConstants(shader_program_phong_shading, 0.1f, 0.7f, 0.3f, 8);
		double startTime = glfwGetTime();

		sceneSettings.setLightConstants(shader_program_sun, 1.0f, 1.0f, 0.3f, 8);
		glUseProgram(shader_program_sun);
		sun.draw();
		glUseProgram(0);

		glUseProgram(shader_program_phong_shading);
		mercury.draw();
		venus.draw();
		earth.draw();
		mars.draw();
		jupiter.draw();
		saturn.draw();
		uranus.draw();
		neptune.draw();
		glUseProgram(0);
		
		glUseProgram(shader_program_skybox);
		space.draw();
		glUseProgram(0);
		
		glUseProgram(shader_program_primitive);
		mercuryCircle.draw();
		venusCircle.draw();
		earthCircle.draw();
		marsCircle.draw();
		jupiterCircle.draw();
		saturnCircle.draw();
		uranusCircle.draw();
		neptuneCircle.draw();
		saturn_ring.draw();
		glUseProgram(0);

		double endTime = glfwGetTime();
		float time_diff = (float)(endTime - startTime);
		
		sun.setModelMatrix(glm::rotate(SUN_ROTATION_SPEED * time_diff * 45.0f, glm::vec3(0.0f, 1.0f, 0.0f)) * sun.getModelMatrix());
		mercury.setModelMatrix(glm::rotate(MERCURY_ROTATION_SPEED_AROUND_SUN * time_diff * 45.0f, glm::vec3(0.0f, 1.0f, 0.0f)) * mercury.getModelMatrix() * glm::rotate(MERCURY_ROTATION_SPEED * time_diff * -45.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
		venus.setModelMatrix(glm::rotate(VENUS_ROTATION_SPEED_AROUND_SUN * time_diff * 45.0f, glm::vec3(0.0f, 1.0f, 0.0f)) * venus.getModelMatrix() * glm::rotate(VENUS_ROTATION_SPEED * time_diff * -45.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
		earth.setModelMatrix(glm::rotate(EARTH_ROTATION_SPEED_AROUND_SUN * time_diff * 45.0f, glm::vec3(0.0f, 1.0f, 0.0f)) * earth.getModelMatrix() * glm::rotate(EARTH_ROTATION_SPEED * time_diff * -45.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
		mars.setModelMatrix(glm::rotate(MARS_ROTATION_SPEED_AROUND_SUN * time_diff * 45.0f, glm::vec3(0.0f, 1.0f, 0.0f)) * mars.getModelMatrix() * glm::rotate(MARS_ROTATION_SPEED * time_diff * -45.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
		jupiter.setModelMatrix(glm::rotate(JUPITER_ROTATION_SPEED_AROUND_SUN * time_diff * 45.0f, glm::vec3(0.0f, 1.0f, 0.0f)) * jupiter.getModelMatrix() * glm::rotate(JUPITER_ROTATION_SPEED * time_diff * -45.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
		saturn.setModelMatrix(glm::rotate(SATURN_ROTATION_SPEED_AROUND_SUN * time_diff * 45.0f, glm::vec3(0.0f, 1.0f, 0.0f)) * saturn.getModelMatrix() * glm::rotate(SATURN_ROTATION_SPEED * time_diff * -45.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
		uranus.setModelMatrix(glm::rotate(URANUS_ROTATION_SPEED_AROUND_SUN * time_diff * 45.0f, glm::vec3(0.0f, 1.0f, 0.0f)) * uranus.getModelMatrix() * glm::rotate(URANUS_ROTATION_SPEED * time_diff * -45.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
		neptune.setModelMatrix(glm::rotate(NEPTUNE_ROTATION_SPEED_AROUND_SUN * time_diff * 45.0f, glm::vec3(0.0f, 1.0f, 0.0f)) * neptune.getModelMatrix() * glm::rotate(NEPTUNE_ROTATION_SPEED * time_diff * -45.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
		saturn_ring.setModelMatrix(glm::rotate(SATURN_ROTATION_SPEED_AROUND_SUN * time_diff * 45.0f, glm::vec3(0.0f, 1.0f, 0.0f)) * saturn_ring.getModelMatrix());

		glfwPollEvents();
		glfwSwapBuffers(window);

	}


	/* --------------------------------------------- */
	// Destroy context and exit
	/* --------------------------------------------- */
	releaseResources();

	return EXIT_SUCCESS;
}

void key_press_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	if (key == GLFW_KEY_F1 && action == GLFW_PRESS) {
		wire_frame_mode = !wire_frame_mode;
		glPolygonMode(GL_FRONT_AND_BACK, wire_frame_mode ? GL_LINE : GL_FILL);

	}

	if (key == GLFW_KEY_F2 && action == GLFW_PRESS) {
		back_face_culling_mode = !back_face_culling_mode;
		back_face_culling_mode ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
	}
}

void mouse_action_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		left_mouse_clicked = true;
	}

	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		left_mouse_clicked = false;
	}

	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		right_mouse_clicked = true;
	}

	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
		right_mouse_clicked = false;
	}
}

void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	zoom -= float(yoffset) * 0.5f;
}

void loadTextureResources(std::list<std::string>& textureNameList, std::vector<Texture>& textures) {
	for (std::string textureMap : textureNameList) {
		std::string destination = TEXTURE_FOLDER_LOCATION + textureMap;

		int width, height, color_channels;
		unsigned char *data = stbi_load(destination.c_str() , &width, &height, &color_channels, 0);

		if (data) {
			Texture texture;
			texture.data = data;
			texture.width = width;
			texture.height = height;
			
			textures.push_back(texture);
		}
		else {
			releaseResources();
			std::cerr << "Could not load texture: " << textureMap << std::endl;
			stbi_image_free(data);
			exit(EXIT_FAILURE);
		}

	}
}

void createWindow(GLFWwindow** window, const int WIDTH, const int HEIGHT) {
	if (!glfwInit()) {
		std::cerr << "Error: Could not init GLFW!" << std::endl;
		exit(EXIT_FAILURE);
	}

	// WindowHints to configure OpenGL-Version, Core Profile and Window-Properties
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	// Create Debug Context for OpenGL error callbacks
#if _DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif

	*window = glfwCreateWindow(WIDTH, HEIGHT, WINDOW_NAME.c_str(), nullptr, nullptr);

	if (!window) {
		std::cerr << "Error: Could not create window!" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// Add key press callback to Window
	glfwSetKeyCallback(*window, key_press_callback);
	glfwSetMouseButtonCallback(*window, mouse_action_callback);
	glfwSetScrollCallback(*window, mouse_scroll_callback);

	// Set Context
	glfwMakeContextCurrent(*window);
}

void releaseResources() {
	resources.releaseResources();
	glfwTerminate();
}