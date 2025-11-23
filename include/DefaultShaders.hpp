// DefaultShaders.hpp
#pragma once
#include <string>

namespace Reblocked
{

namespace Shaders
{

	inline const std::string BasicVertexShader = R"(
#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec3 aColor;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec3 vColor;
out vec3 vNormal;
out vec3 vFragPos;

void main()
{
    vColor = aColor;
    vNormal = mat3(transpose(inverse(uModel))) * aNormal;
    vFragPos = vec3(uModel * vec4(aPosition, 1.0));
    gl_Position = uProjection * uView * uModel * vec4(aPosition, 1.0);
}
)";

	inline const std::string BasicFragmentShader = R"(
#version 330 core

in vec3 vColor;
in vec3 vNormal;
in vec3 vFragPos;

out vec4 FragColor;

uniform vec3 uLightPos = vec3(5.0, 10.0, 5.0);
uniform vec3 uViewPos = vec3(0.0, 5.0, 10.0);

void main()
{
    // Simple Blinn-Phong lighting
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    
    // Ambient
    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * lightColor;
    
    // Diffuse
    vec3 norm = normalize(vNormal);
    vec3 lightDir = normalize(uLightPos - vFragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // Specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(uViewPos - vFragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), 32.0);
    vec3 specular = specularStrength * spec * lightColor;
    
    vec3 result = (ambient + diffuse + specular) * vColor;
    FragColor = vec4(result, 1.0);
}
)";

} // namespace Shaders

} // namespace Reblocked
