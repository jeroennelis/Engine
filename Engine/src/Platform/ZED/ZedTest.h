#pragma once
#include <iostream>

#include <Platform/OpenGl/GL.h>




#include "Platform/OpenGl/GL.h"

#include <openvr.h>


#include "ZedShader.hpp"
#include "GLObject.hpp"

#include <sl/Camera.hpp>

class ZedTest
{
public:
	ZedTest();
	~ZedTest();

	void Init(int width, int height);
	void Update();

private:
	sl::Camera zed;

	GLuint imageTex;            //OpenGL texture mapped with a cuda array (opengl gpu interop)


	const char* IMAGE_FRAGMENT_SHADER =
		"#version 330 core\n"
		" in vec2 UV;\n"
		" out vec4 color;\n"
		" uniform sampler2D texImage;\n"
		" uniform bool revert;\n"
		" uniform bool rgbflip;\n"
		" void main() {\n"
		"    vec2 scaler  =revert?vec2(UV.x,1.f - UV.y):vec2(UV.x,UV.y);\n"
		"    vec3 rgbcolor = rgbflip?vec3(texture(texImage, scaler).zyx):vec3(texture(texImage, scaler).xyz);\n"
		"    color = vec4(rgbcolor,1);\n"
		"}";

	const char* IMAGE_VERTEX_SHADER =
		"#version 330\n"
		"layout(location = 0) in vec3 vert;\n"
		"out vec2 UV;"
		"void main() {\n"
		"   UV = (vert.xy+vec2(1,1))/2;\n"
		"	gl_Position = vec4(vert, 1);\n"
		"}\n";

	sl::Mat image; // sl::Mat to hold images
	cudaGraphicsResource* cuda_gl_ressource;
	ZedShader* shader_image = NULL;

	int m_CamWidth;
	int m_CamHeight;

	int m_VRWidth;
	int m_VRHeight;

	GLuint fbo = 0;             //FBO

	GLuint texID;               //Shader variable loc (sampler/texture)

	GLuint quad_vb;             //buffer for vertices/coords for image

	GLuint renderedTexture = 0; //Render Texture for FBO
};

