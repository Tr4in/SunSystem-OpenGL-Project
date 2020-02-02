#pragma once
#include <iostream>

/* --------------------------------------------- */
// WINDOW SETTINGS
/* --------------------------------------------- */
const std::string EVC_EXERCISE_NAME = "Sun System";
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const float FOV = 60.0f;
const float ZNEAR = 0.1f;
const float ZFAR = 500.0f; 

/* --------------------------------------------- */
// RESOURCES
/* --------------------------------------------- */
const std::string TEXTURE_FOLDER_LOCATION = "./assets/textures/";
const std::string CUBEMAP_FOLDER_LOCATION = "./assets/textures/cubemap/";

/* --------------------------------------------- */
// PLANET SETTINGS
/* --------------------------------------------- */
const float MERCURY_DISTANCE = 15.0f;
const float VENUS_DISTANCE = 40.0f;
const float EARTH_DISTANCE = 65.0f;
const float MARS_DISTANCE = 90.0f;
const float JUPITER_DISTANCE = 115.0f;
const float SATURN_DISTANCE = 140.0f;
const float URANUS_DISTANCE = 165.0f;
const float NEPTUNE_DISTANCE = 190.0f;

const float SATURN_RING_INNER_RADIUS = 4.0f;
const float SATURN_RING_OUTER_RADIUS = 7.0f;

const float SUN_ROTATION_SPEED = 0.05f;
const float MERCURY_ROTATION_SPEED_AROUND_SUN = 0.05f;
const float VENUS_ROTATION_SPEED_AROUND_SUN = MERCURY_ROTATION_SPEED_AROUND_SUN / 3;
const float EARTH_ROTATION_SPEED_AROUND_SUN = 0.01f;
const float MARS_ROTATION_SPEED_AROUND_SUN = EARTH_ROTATION_SPEED_AROUND_SUN / 2;
const float JUPITER_ROTATION_SPEED_AROUND_SUN = 0.005f;
const float SATURN_ROTATION_SPEED_AROUND_SUN = JUPITER_ROTATION_SPEED_AROUND_SUN / 2;
const float URANUS_ROTATION_SPEED_AROUND_SUN = SATURN_ROTATION_SPEED_AROUND_SUN / 3;
const float NEPTUNE_ROTATION_SPEED_AROUND_SUN = URANUS_ROTATION_SPEED_AROUND_SUN / 2;

const float EARTH_ROTATION_SPEED = 0.15f;
const float MERCURY_ROTATION_SPEED = EARTH_ROTATION_SPEED / 58.0f;
const float VENUS_ROTATION_SPEED = EARTH_ROTATION_SPEED / 117.0f;
const float MARS_ROTATION_SPEED = EARTH_ROTATION_SPEED;
const float JUPITER_ROTATION_SPEED = EARTH_ROTATION_SPEED * 4;
const float SATURN_ROTATION_SPEED = EARTH_ROTATION_SPEED * 2;
const float URANUS_ROTATION_SPEED = EARTH_ROTATION_SPEED * (4/3);
const float NEPTUNE_ROTATION_SPEED = EARTH_ROTATION_SPEED * (4 / 3);

/* --------------------------------------------- */
// SKYBOX SETTING
/* --------------------------------------------- */
const float SKYBOX_SCALE_FACTOR = 200.0f;

/* --------------------------------------------- */
// SHADER LOCATIONS
/* --------------------------------------------- */
const unsigned int POSITION_LOCATION = 0;
const unsigned int MODEL_MATRIX_LOCATION = 1;
const unsigned int PROJ_VIEW_MATRIX_LOCATION = 2;
const unsigned int SAMPLER_LOCATION = 3;
const unsigned int NORMALS_LOCATION = 4;
const unsigned int DIRECTIONAL_LIGHT_SOURCE_DIRECTION_LOCATION = 5;
const unsigned int DIRECTIONAL_LIGHT_INTENSITY_LOCATION = 6;
const unsigned int POINT_LIGHT_SOURCE_POSITION_LOCATION = 7;
const unsigned int POINT_LIGHT_INTENSITY_LOCATION = 8;
const unsigned int POINT_LIGHT_ATTENUATION_LOCATION = 9;
const unsigned int CAMERA_POSITION_LOCATION = 10;
const unsigned int AMBIENT_REFLECTION_LOCATION = 11;
const unsigned int DIFFUSE_REFLECTION_LOCATION = 12;
const unsigned int SPECULAR_REFLECTION_LOCATION = 13;
const unsigned int SHININESS_LOCATION = 14;
const unsigned int TEXTURE_COORDINATE_LOCATION = 15;
const unsigned int COLOR_LOCATION = 16;