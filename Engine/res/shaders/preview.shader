#properties
{
	Color{"u_texColor"} = ();
	float{"u_shineDamper"};
	float{"u_reflectivity"};
	float{"test"};
}

#shader vertex
#version 330 core 
  
layout(location = 0) in vec4 position;
layout(location = 1) in vec4 normal;
layout(location = 2) in vec2 texCoord;

out vec2 v_TexCoord;

out vec3 surfaceNormal;
out vec3 toLightVector;
out vec3 toCamVector;

uniform mat4 u_transformationMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;
  
void main()  
{  
	vec4 worldcoordinates = u_transformationMatrix * position;
	vec4 positionRelativeToCam = u_viewMatrix * worldcoordinates;

	
	gl_Position = u_projectionMatrix * positionRelativeToCam;

	surfaceNormal = (u_transformationMatrix * normal).xyz;
	toLightVector = vec3(10000, 10000, 10000) - worldcoordinates.xyz;
	toCamVector = (inverse(u_viewMatrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldcoordinates.xyz;

	v_TexCoord = texCoord;
};


#shader fragment
#version 330 core

layout(location = 0) out vec4 color;  

vec4 u_texColor = vec4(0.75, 0.75, 0.75, 1.0);
float u_shineDamper = 0.5;
float u_reflectivity = 0.5;

in vec2 v_TexCoord;

in vec3 surfaceNormal;
in vec3 toLightVector;
in vec3 toCamVector;

void main()  
{  
	vec3 unitNormal = normalize(surfaceNormal);
	vec3 unitLightVector = normalize(toLightVector);

	float nDot = dot(unitNormal, unitLightVector);
	float brightness = max(nDot, 0.2); // 0.2 ambient lighting, future uniform
	vec3 diffuse = brightness * vec3(0.8, 0.8, 0.8); //lightcolor

	vec3 unitVectorToCam = normalize(toCamVector);
	vec3 lightDirection = -unitLightVector;
	vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);

	float specularFactor = dot(reflectedLightDirection, unitVectorToCam);
	specularFactor = max(specularFactor, 0.0);
	float dampedFactor = pow(specularFactor, u_shineDamper);
	vec3 finalSpecular = dampedFactor * u_reflectivity * vec3(0.8, 0.8, 0.8);

	//vec4 textureColour = texture(textureSampler, pass_textureCoords);
	vec4 textureColour = u_texColor;

	color = u_texColor;
};