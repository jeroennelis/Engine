#properties
{
}

#shader vertex
#version 330 core 
  
layout(location = 0) in vec4 position;
layout(location = 1) in vec3 colour;

uniform mat4 u_transformationMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

out vec3 out_colour;
  
void main()  
{  
	vec4 worldcoordinates = u_transformationMatrix * position;
	vec4 positionRelativeToCam = u_viewMatrix * worldcoordinates;
	gl_Position = u_projectionMatrix * positionRelativeToCam;

	out_colour = colour;
};


#shader fragment
#version 330 core

in vec3 out_colour;

out vec4 color;

void main()
{
	color = vec4(out_colour, 1.0);
};