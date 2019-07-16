#properties
{
}

#shader vertex
#version 330 core 
  
layout(location = 0) in vec4 position;
layout(location = 1) in int colour;

uniform mat4 u_transformationMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

out vec3 out_colour;
  
void main()  
{  
	vec4 worldcoordinates = u_transformationMatrix * position;
	vec4 positionRelativeToCam = u_viewMatrix * worldcoordinates;
	gl_Position = u_projectionMatrix * positionRelativeToCam;

	if (colour == 0)
	{
		out_colour = vec3(0.9, 0.1, 0.1);
	}
	else
	{
		out_colour = vec3(0.1, 0.9, 0.1);
	}
};


#shader fragment
#version 330 core

in vec3 out_colour;

out vec4 color;

void main()
{
	color = vec4(out_colour,1.0);
	color.a = 0.5;
};