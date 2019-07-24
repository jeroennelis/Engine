#shader vertex
#version 330 core 
  
layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

uniform mat4 u_transformationMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

float offset = 0.1;
  
void main()  
{  
	vec4 newPos = position + vec4(normal * offset,1.0);

	vec4 worldcoordinates = u_transformationMatrix * newPos;
	vec4 positionRelativeToCam = u_viewMatrix * worldcoordinates;
	gl_Position = u_projectionMatrix * positionRelativeToCam;
};


#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

void main()  
{  
	
	color = vec4(0.88, 0.44,0.05, 1.0);
	
};