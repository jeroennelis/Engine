#properties
{
	float{"u_Kd"}
	Color{"u_Cd"} = ();
	float{"u_Ka"};
	float{"u_Ks"};
	float{"u_epsilon"};
}

#shader vertex
#version 330 core 
  
layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

uniform mat4 u_transformationMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;
uniform vec3 u_lightPosition[10];
uniform int u_nrOfLights;

out vec3 surfaceNormal;
out vec3 toLightVector[10];
out vec3 toCamVector;

out vec2 passTexCoord;
  
void main()  
{  
	vec4 worldcoordinates = u_transformationMatrix * position;
	vec4 positionRelativeToCam = u_viewMatrix * worldcoordinates;
	gl_Position = u_projectionMatrix * positionRelativeToCam;

	surfaceNormal = (u_transformationMatrix * vec4(normal, 0)).xyz;

	for (int i = 0; i < u_nrOfLights; i++)
	{
		toLightVector[i] =  u_lightPosition[i] - worldcoordinates.xyz;
	}

	toCamVector = worldcoordinates.xyz - (inverse(u_viewMatrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz;

	passTexCoord = texCoord;
};


#shader fragment
#version 330 core
#define PI 3.1415926535897932384626433832795

layout(location = 0) out vec4 color;

uniform sampler2D textureSampler;

uniform vec3 u_lightColour[10];
uniform vec3 u_attenuation[10];
uniform int u_nrOfLights;

uniform float u_Kd;			//reflectivity of surface
uniform vec4 u_Cd;			//color of surface

uniform float u_Ka;

uniform float u_Ks;
uniform float u_epsilon;


in vec2 passTexCoord;

in vec3 surfaceNormal;
in vec3 toLightVector[10];
in vec3 toCamVector;

const float lightIntensity = 1.0;

const vec3 ambientColor = vec3(0.9, 0.9, 0.9);
const float ambientIntensity = 1.0;



void main()  
{  
	vec3 unitNormal = normalize(surfaceNormal);
	vec3 unitVectorToCam = normalize(toCamVector);
	

	// ambient shading
	vec3 ambient = u_Ka * u_Cd.xyz * ambientIntensity * ambientColor;
	
	vec3 totalDiffuse = vec3(0.0);
	vec3 totalPhong = vec3(0.0);

	for (int i = 0; i < u_nrOfLights; i++)
	{
		float distance = length(toLightVector[i]);
		float attFactor = u_attenuation[i].x + (u_attenuation[i].y * distance) + (u_attenuation[i].z * distance * distance);
		vec3 unitLightVector = normalize(toLightVector[i]);

		// diffuse shading
		float nDotWi = dot(unitNormal, unitLightVector);
		float reflectivity = u_Kd / PI;
		totalDiffuse = totalDiffuse + (reflectivity * u_Cd.xyz * lightIntensity * u_lightColour[i] * nDotWi) / attFactor;

		// phong shading
		vec3 reflectedLightDir = reflect(unitLightVector, unitNormal);
		float phongFactor = dot(reflectedLightDir, unitVectorToCam);
		phongFactor = max(phongFactor, 0.1);
		float cosToCam = pow(phongFactor, u_epsilon);
		totalPhong = totalPhong + (u_Ks * cosToCam * lightIntensity * u_lightColour[i])/ attFactor;

	}
	
	// total color
	color = vec4(totalDiffuse + ambient + totalPhong, 1.0);
	color = clamp(color, 0.0, 1.0);

	color = texture(textureSampler, passTexCoord) * color;
	
};