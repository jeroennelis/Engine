#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec2 fragTexCoord;
layout(location = 1) in vec3 surfaceNormal;
layout(location = 2) in vec3 toLightVector;
layout(location = 3) in vec3 toCamVector;

layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) out vec4 outColor;

void main()
{
	vec3 unitNormal = normalize(surfaceNormal);
	vec3 unitLightVector = normalize(toLightVector);

	float nDot = dot(unitNormal, unitLightVector);
	float brightness = max(nDot, 0.2); // 0.2 ambient lighting, future uniform
	vec3 diffuse = brightness * vec3(0.8, 0.8, 0.8); //lightcolor

	vec4 textureColour = texture(texSampler, fragTexCoord);

	outColor = vec4(diffuse, 1.0) * textureColour ;
}