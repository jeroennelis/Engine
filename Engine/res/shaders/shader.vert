#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UniformBufferObject{
	mat4 model;
	mat4 view;
	mat4 proj;
	float red;
} ubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec3 inColor;
layout(location = 3) in vec2 inTexCoord;

layout(location = 0) out vec2 fragTexCoord;
layout(location = 1) out vec3 surfaceNormal;
layout(location = 2) out vec3 toLightVector;
layout(location = 3) out vec3 toCamVector;

out gl_PerVertex{
	vec4 gl_Position;
};

void main()
{
	vec4 worldcoordinates = ubo.model * vec4(inPosition, 1.0);
	vec4 positionRelativeToCam = ubo.view * worldcoordinates;

	gl_Position = ubo.proj * positionRelativeToCam;

	surfaceNormal = (ubo.model * vec4(inNormal, 1.0)).xyz;
	toLightVector = vec3(10000, 10000, 10000) - worldcoordinates.xyz;
	toCamVector = (inverse(ubo.view) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldcoordinates.xyz;

	fragTexCoord = inTexCoord;
}
