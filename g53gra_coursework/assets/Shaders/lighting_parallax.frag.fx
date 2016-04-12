#version 330 core
#pragma optionNV unroll all

precision highp float;

#define MAX_LIGHTS 3

in vec2 uv;
in vec3 position_worldspace;
in vec3 eyeDirection_tangentspace;
in vec3 lightDirection_tangentspace[MAX_LIGHTS];

layout(location = 0) out vec4 fragColor;

uniform vec3 lightPosition_worldspace[MAX_LIGHTS];
uniform vec4 lightAmbient[MAX_LIGHTS];
uniform vec4 lightColor[MAX_LIGHTS];
uniform float lightPower[MAX_LIGHTS];
uniform sampler2D diffuseMapSampler;
uniform sampler2D normalMapSampler;
uniform sampler2D specularMapSampler;
uniform sampler2D heightMapSampler;

vec2 parallaxMapping()
{
    // Parallax calculation inputs
    vec3 normEyeDirection_tangentspace = normalize(eyeDirection_tangentspace);
    vec2 currentUVs = uv;

    // Compute layer properties
    float numLayers = mix(15.0, 10.0, abs(dot(vec3(0.0, 0.0, 1.0), normEyeDirection_tangentspace)));
    float layerHeight = 1.0 / numLayers;
    float curLayerHeight = 0.0;

    // Shift of texture coordinates for each layer
    vec2 texStep = -0.02 * normEyeDirection_tangentspace.xy / normEyeDirection_tangentspace.z / numLayers;

    // Move down layers while the point is still above the heightmap
    float heightFromTexture = texture(heightMapSampler, currentUVs).r;
    while (heightFromTexture > curLayerHeight) {
        curLayerHeight += layerHeight;
        currentUVs -= texStep;
        heightFromTexture = texture(heightMapSampler, currentUVs).r;
    }

    // Used to interpolate between heights
    vec2 prevUVs = currentUVs + texStep;
    float nextHeight = heightFromTexture - curLayerHeight;
    float prevHeight = texture(heightMapSampler, prevUVs).r - curLayerHeight + layerHeight;
    float weight = nextHeight / (nextHeight - prevHeight);

    // Interpolate the UV coordinates
    return prevUVs * weight + currentUVs * (1.0 - weight);
}

vec4 computeLighting(in vec2 parallaxUVs)
{
    // Get material properties
    float shininess = texture2D(specularMapSampler, parallaxUVs).r * 255.0f;
    vec3 normal_tangentSpace = 2.0 * texture(normalMapSampler, parallaxUVs).xyz - 1.0;
    vec3 normEyeDirection_tangentspace = normalize(eyeDirection_tangentspace);

    // Sum all lights
    vec4 lighting = vec4(0.0, 0.0, 0.0, 0.0);
    for (int i = 0; i < MAX_LIGHTS; i++) {
        // Distance to the light
        float distance = length(lightPosition_worldspace[i] - position_worldspace);
        float distanceSquared = (distance * distance) * 0.2;

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
    return texture(diffuseMapSampler, parallaxUVs) * lighting;
}

void main()
{
    // Perform parallax occlusion mapping
    vec2 newUVs = parallaxMapping();

    // Perform the lighting calculations
    fragColor = computeLighting(newUVs);
}
