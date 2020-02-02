#version 430

layout(location = 0) in vec3 position;
layout(location = 1) uniform mat4 model_matrix1;
layout(location = 2) uniform mat4 proj_view_matrix;
layout(location = 4) in vec3 normal1;
layout(location = 15) in vec2 texCoord;
out mat4 model_matrix;
out vec3 pos;
out vec3 normal;
out vec2 texCoordinate;

void main() {
    gl_Position = proj_view_matrix * model_matrix1 * vec4(position, 1);
    model_matrix = model_matrix1;
    pos = vec3(model_matrix * vec4(position, 1));
    normal = transpose(inverse(mat3(model_matrix))) * normal1;
    texCoordinate = texCoord;
}