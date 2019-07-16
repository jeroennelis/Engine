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

const vec3 lightPos = vec3(0, 100, 100);

out vec3 surfaceNormal;
out vec3 toLightVector;
out float phongFactor;
  
void main()  
{  
	vec4 worldcoordinates = u_transformationMatrix * position;
	vec4 positionRelativeToCam = u_viewMatrix * worldcoordinates;
	gl_Position = u_projectionMatrix * positionRelativeToCam;

	surfaceNormal = normalize((u_transformationMatrix * vec4(normal,0)).xyz);
	toLightVector = worldcoordinates.xyz - lightPos;
	toLightVector = normalize(-toLightVector);

	// phong
	vec3 toCameraDir = (inverse(u_viewMatrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldcoordinates.xyz;
	vec3 reflectedLightDir = reflect(-toLightVector, surfaceNormal);
	phongFactor = dot(reflectedLightDir, toCameraDir);
	phongFactor = phongFactor, 0.1;
};


#shader fragment
#version 330 core
#define PI 3.1415926535897932384626433832795

layout(location = 0) out vec4 color;

uniform float u_Kd;			//reflectivity of surface
uniform vec4 u_Cd;			//color of surface

uniform float u_Ka;

uniform float u_Ks;
uniform float u_epsilon;

in vec3 surfaceNormal;
in vec3 toLightVector;
in float phongFactor;

const vec3 lightColor = vec3(0.9, 0.9, 0.9);
const float lightIntensity = 1.0;

const vec3 ambientColor = vec3(0.9, 0.9, 0.9);
const float ambientIntensity = 1.0;



void main()  
{  
	// diffuse shading
	float nDotWi = dot(surfaceNormal, toLightVector);
	float reflectivity = u_Kd / PI;
	vec3 diffuse = reflectivity * u_Cd.xyz * lightIntensity * lightColor * nDotWi;
	
	// ambient shading
	vec3 ambient = u_Ka * u_Cd.xyz * ambientIntensity * ambientColor;

	// phong shading
	float cosToCam = pow(phongFactor, u_epsilon);
	vec3 phong = u_Ks * cosToCam *  lightIntensity * lightColor;

	// total color
	color = vec4(diffuse + ambient /*+ phong*/, 1.0);
	/*color = clamp(color, 0.0, 1.0);*/
};