#version 330 core
#pragma optionNV unroll all

precision highp float;

#define MAX_LIGHTS 3

in vec2 uv;
in vec3 normal_tangentSpace;
in vec3 position_worldspace;
in vec3 eyeDirection_tangentspace;
in vec3 lightDirection_tangentspace[MAX_LIGHTS];

layout(location = 0) out vec4 fragColor;

uniform vec3 lightPosition_worldspace[MAX_LIGHTS];
uniform vec4 lightAmbient[MAX_LIGHTS];
uniform vec4 lightColor[MAX_LIGHTS];
uniform float lightPower[MAX_LIGHTS];
uniform sampler2D diffuseMapSampler;

vec4 computeLighting()
{
    // Get material properties
    float shininess = 0.0f;
    vec3 normEyeDirection_tangentspace = normalize(eyeDirection_tangentspace);

    // Sum all lights
    vec4 lighting = vec4(0.0, 0.0, 0.0, 0.0);
    for (int i = 0; i < MAX_LIGHTS; i++) {
        // Distance to the light
        float distance = length(lightPosition_worldspace[i] - position_worldspace);
        float distanceSquared = distance * distance;

        // Light calculation inputs
        vec3 normLightDirection_tangentspace = normalize(lightDirection_tangentspace[i]);
        vec3 reflection = reflect(-normLightDirection_tangentspace, normal_tangentSpace);

        // Lighting reflection values
        float cosTheta = max(dot(normal_tangentSpace, normLightDirection_tangentspace), 0.0);
        float cosAlpha = pow(max(dot(reflection, normLightDirection_tangentspace), 0.0), shininess);
        cosTheta = clamp(cosTheta, 0.0, 1.0);
        cosAlpha = clamp(cosAlpha, 0.0, 1.0);

        // Compute lighting terms
        float diffuseTerm = cosTheta / distanceSquared;
        float specularTerm = cosAlpha / distanceSquared;

        // Sum all the terms for each light
        lighting += lightAmbient[i] + (lightPower[i] * lightColor[i] * (diffuseTerm + specularTerm));
    }

    // Return the computed light intensity
    return texture(diffuseMapSampler, uv) * lighting;
}

void main()
{
    // Dont render this pixel if its (nearly) white
    vec4 diffuse = texture(diffuseMapSampler, uv);
    if (diffuse.r > 0.4 && diffuse.g > 0.4 && diffuse.b > 0.4) {
        discard;
    }

    // Perform the lighting calculations
    fragColor = computeLighting();
}
