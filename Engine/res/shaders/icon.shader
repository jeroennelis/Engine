#shader vertex
#version 330 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec2 a_TexCoords;

uniform mat4 u_projectionMatrix;
uniform mat4 u_modelViewMatrix;

out vec2 passTexCoords;

void main(void) 
{
	gl_Position = u_projectionMatrix * u_modelViewMatrix * vec4(a_Position, 0.0, 1.0);

	passTexCoords = a_TexCoords;
}


#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform sampler2D textureSampler;

uniform vec4 u_colour;

in vec2 passTexCoords;

void main(void) 
{

	color = texture(textureSampler, passTexCoords);
	if (color.a < 0.5f)
	{
		discard;
	}

	color = u_colour * color.r;
}