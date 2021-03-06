#version 430

layout(location = 0) in vec3 position;
layout(location = 1) uniform mat4 model_matrix;
layout(location = 2) uniform mat4 projection_view_matrix;


void main() {
    gl_Position = projection_view_matrix * model_matrix * vec4(position, 1.0f);
}