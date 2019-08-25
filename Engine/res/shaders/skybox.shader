#shader vertex
#version 400 core 
  
layout(location = 0) in vec4 position;

uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

out vec3 texCoords;
  
void main()  
{  
	gl_Position = u_projectionMatrix * u_viewMatrix * vec4(position);

	texCoords = position.xyz;
};


#shader fragment
#version 400 core

in vec3 texCoords;

layout(location = 0) out vec4 color;

uniform samplerCube cubeMap;

void main()  
{  
	color = texture(cubeMap, texCoords);
};