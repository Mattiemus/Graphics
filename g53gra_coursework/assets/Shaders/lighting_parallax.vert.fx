#version 330 core
#pragma optionNV unroll all

precision highp float;

#define MAX_LIGHTS 3

layout(location = 0) in vec2 vertex_uv;
layout(location = 1) in vec3 vertex_position_modelspace;
layout(location = 2) in vec3 vertex_normal_modelspace;
layout(location = 3) in vec3 vertex_tangent_modelspace;
layout(location = 4) in vec3 vertex_bitangent_modelspace;

out vec2 uv;
out vec3 position_worldspace;
out vec3 eyeDirection_tangentspace;
out vec3 vertexToEye_tangentspace;
out vec3 lightDirection_tangentspace[MAX_LIGHTS];

uniform vec2 textureRepeat;
uniform vec3 lightPosition_worldspace[MAX_LIGHTS];
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    // Create the normal transformation matrix
    mat3 normMatrix = mat3(transpose(inverse(viewMatrix * modelMatrix)));

    // Transform and forward the inputs to the fragment shader
    uv = vertex_uv * textureRepeat;
    position_worldspace = (modelMatrix * vec4(vertex_position_modelspace, 1.0)).xyz;

    // Compute the vertex position based on the project/view/model transformation matricies
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex_position_modelspace, 1.0);

    // Transform light and eye directions into tangent space
    vec3 normal_cameraspace = normMatrix * normalize(vertex_normal_modelspace);
    vec3 tangent_cameraspace = normMatrix * normalize(vertex_tangent_modelspace);
    vec3 bitangent_cameraspace = normMatrix * normalize(vertex_bitangent_modelspace);
    mat3 cameraSpaceToTangentSpace = transpose(mat3(tangent_cameraspace, 
        bitangent_cameraspace, 
        normal_cameraspace));

    // Compute the eye position
    vec3 vertexPosition_cameraspace = (viewMatrix * modelMatrix * vec4(vertex_position_modelspace, 1.0)).xyz;
    vec3 eyeDirection_cameraspace = -vertexPosition_cameraspace;
    eyeDirection_tangentspace = cameraSpaceToTangentSpace * eyeDirection_cameraspace;

    // Compute lighting direction
    for (int i = 0; i < MAX_LIGHTS; i++) {
        vec3 lightDir_cameraspace = (viewMatrix * vec4(lightPosition_worldspace[i], 1.0)).xyz + eyeDirection_cameraspace;
        lightDirection_tangentspace[i] = cameraSpaceToTangentSpace * lightDir_cameraspace;
    }
}
