#version 430

in vec3 texCoord;
out vec4 color;
layout(location = 3) uniform samplerCube skybox;

void main() {
    color = texture(skybox, texCoord);
}