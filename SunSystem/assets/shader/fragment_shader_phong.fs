#version 430

layout(location = 3) uniform sampler2D colorTexture;
layout(location = 5) uniform vec3 directional_light_direction;
layout(location = 6) uniform vec3 directional_light_intensity;
layout(location = 7) uniform vec3 point_light_source;
layout(location = 8) uniform vec3 point_light_intensity;
layout(location = 9) uniform vec3 point_light_attenuation;
layout(location = 10) uniform vec3 camera_position;
layout(location = 11) uniform float ambient_reflection_constant;
layout(location = 12) uniform float diffuse_reflection_constant;
layout(location = 13) uniform float specular_reflection_constant;
layout(location = 14) uniform float shininess_constant;

in mat4 model_matrix;
in vec3 pos;
in vec3 normal;
in vec2 texCoordinate;
out vec4 outColor;

vec3 ambient_point_light;
vec3 ambient_directional_light;
vec3 diffuse_point_light;
vec3 diffuse_directional_light;
vec3 specular_point_light;
vec3 specular_directional_light;

void main() {
    
    vec3 position_transformed = pos;
    vec3 normal_transformed = normalize(normal);
    vec3 directional_light_direction_transformed = normalize(directional_light_direction);
    vec3 directionToViewer = camera_position - position_transformed;

    // AMBIENT
    vec3 ambient_light = vec3(1.0f, 1.0f, 1.0f) * ambient_reflection_constant;

    // DIFFUSE
    vec3 positionToPointLight = point_light_source - position_transformed;
    float distanceToPointLightSource = length(positionToPointLight);
    float attenuation = point_light_attenuation.x + distanceToPointLightSource * point_light_attenuation.y + pow(distanceToPointLightSource, 2.0f) * point_light_attenuation.z;

    float brightness_point_light = dot(normalize(positionToPointLight), normal_transformed);
    brightness_point_light = max(brightness_point_light, 0.0f);

    float brightness_directional_light = dot(-directional_light_direction_transformed, normal_transformed);
    brightness_directional_light = max(brightness_directional_light, 0.0f);

    diffuse_point_light = diffuse_reflection_constant * brightness_point_light * point_light_intensity;
    diffuse_directional_light = diffuse_reflection_constant * brightness_directional_light * directional_light_intensity;

    vec3 diffuse_light = diffuse_point_light * (1 / attenuation) + diffuse_directional_light;

    // SPECULAR
    vec3 reflectDir = reflect(-normalize(positionToPointLight), normal_transformed);
    float spec = pow(max(dot(normalize(directionToViewer), reflectDir), 0.0), shininess_constant);

    specular_point_light = specular_reflection_constant * point_light_intensity * spec;

    reflectDir = reflect(directional_light_direction_transformed, normal_transformed);
    spec = pow(max(dot(normalize(directionToViewer), reflectDir), 0.0), shininess_constant);

    specular_directional_light = specular_reflection_constant * directional_light_intensity * spec;

    vec3 specular_light = specular_point_light * (1/attenuation) + specular_directional_light;
    vec3 light = ambient_light + diffuse_light + specular_light;
    outColor = vec4(light * texture(colorTexture, texCoordinate).rgb, 1);

}