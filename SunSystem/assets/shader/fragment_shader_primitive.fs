#version 430

layout(location = 16) uniform vec3 color;
out vec4 output_color;

void main() {
    output_color = vec4(color, 1.0f);
}