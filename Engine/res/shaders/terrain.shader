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

uniform sampler2D backgroundTexture;
uniform sampler2D RTexture;
uniform sampler2D GTexture;
uniform sampler2D BTexture;
uniform sampler2D BlendMap;

uniform vec4 u_texColor;
uniform float u_shineDamper;
uniform float u_reflectivity;

in vec2 v_TexCoord;

in vec3 surfaceNormal;
in vec3 toLightVector;
in vec3 toCamVector;

void main()  
{  

	vec4 blendMapColour = texture(BlendMap, v_TexCoord);

	float backTextureAmount = 1 - (blendMapColour.r + blendMapColour.g + blendMapColour.b);
	vec2 tiledCoords = v_TexCoord * 40.0;
	vec4 backgroundTextureColour = texture(backgroundTexture, tiledCoords) * backTextureAmount;
	vec4 rTextureColour = texture(RTexture, tiledCoords) * blendMapColour.r;
	vec4 gTextureColour = texture(GTexture, tiledCoords) * blendMapColour.g;
	vec4 bTextureColour = texture(BTexture, tiledCoords) * blendMapColour.b;

	vec4 totalColour = backgroundTextureColour + rTextureColour + gTextureColour + bTextureColour;

	color = totalColour;

	//color = vec4(1.0, 1.0, 1.0, 1.0);
};