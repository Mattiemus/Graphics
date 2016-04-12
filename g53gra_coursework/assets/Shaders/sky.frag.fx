#version 330 core
#pragma optionNV unroll all

precision highp float;

in vec2 uv;

layout(location = 0) out vec4 fragColor;

uniform sampler2D diffuseMapSampler;

void main()
{
    // Get the color from the diffuse map
    fragColor = texture(diffuseMapSampler, uv);
}
