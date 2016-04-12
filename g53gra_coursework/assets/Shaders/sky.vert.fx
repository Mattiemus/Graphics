#version 330 core
#pragma optionNV unroll all

precision highp float;

layout(location = 0) in vec2 vertex_uv;
layout(location = 1) in vec3 vertex_position_modelspace;
layout(location = 2) in vec3 vertex_normal_modelspace;
layout(location = 3) in vec3 vertex_tangent_modelspace;
layout(location = 4) in vec3 vertex_bitangent_modelspace;

out vec2 uv;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    // Transform and forward the inputs to the fragment shader
    uv = vertex_uv;

    // Compute the vertex position based on the project/view/model transformation matricies
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex_position_modelspace, 1.0);
}
