#include "enpch.h"

#include "Engine/image.h"
#include <algorithm>
#include "vendor/lodepng/lodepng.h"
#include <glad/glad.h>+
#include <gl/GL.h>
#include "stb_image.h"

#include "Engine/Application.h"

namespace Engine {
	Image::Image(int width, int height)
		: m_Width(width), m_Height(height)
	{
		data = new glm::vec3[width * height];
		imgData = new unsigned char[4 * width * height];
	}

	Image::Image(const std::string& path)
	{
		std::vector<unsigned char> image;
		imgData = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);
		
	
		std::cout << "width: " << m_Width << std::endl;
		std::cout << "height: " << m_Height << std::endl;
	}

	Image::~Image()
	{
		delete [] imgData;
		delete[] data;
	}

	unsigned int Image::getWidth() const
	{
		return m_Width;
	}

	unsigned int Image::getHeight() const
	{
		return m_Height;
	}

	glm::vec3* Image::getPixel(int x, int y)
	{
		return data + (x + y * m_Width);
	}

	void Image::setPixel(int x, int y, const glm::vec3& color)
	{
		data[y + x * m_Width] = color;
		imgData[4 * ((m_Width - x-1) * m_Height + y) + 0] =
			(unsigned char)(color.r * 255.0f);
		imgData[4 * ((m_Width - x-1) * m_Height + y) + 1] =
			(unsigned char)(color.g * 255.0f);
		imgData[4 * ((m_Width - x-1) * m_Height + y) + 2] =
			(unsigned char)(color.b * 255.0f);
		imgData[4 * ((m_Width - x-1) * m_Height + y) + 3] = 255;
	}

	glm::vec3 Image::GetColor(int row, int column)
	{

		return glm::vec3((float)imgData[4 * ( column + m_Width * row) + 0]/255, 
							(float)imgData[4 * (column + m_Width * row) + 1]/255,
							(float)imgData[4 * (column + m_Width * row) + 2]/255);
	}

	void Image::saveImage(std::string filename) const
	{

		//unsigned char* imgData = new unsigned char[4 * width * height];

		//int newY = height - 1;
		//for (int y = 0; y < height; y++, newY--)
		//{
		//	for (int x = 0; x < width; x++)
		//	{
		//		RGBColor curColor = data[x + y * width];

		//		imgData[4 * (x + y * width) + 0] = 255;
		//		imgData[4 * (x + y * width) + 1] =
		//		(unsigned char)(curColor.b * 255.0f);
		//		imgData[4 * (x + y * width) + 2] =
		//		(unsigned char)(curColor.g * 255.0f);
		//		imgData[4 * (x + y * width) + 3] =
		//		(unsigned char)(curColor.r * 255.0f);
		//	}
		//	/*glDrawPixels(300, y, GL_ABGR_EXT, GL_UNSIGNED_BYTE, imgData);
		//	Window::Update();*/
		//}

		/*glTexSubImage2D(GL_TEXTURE_2D, 0,0,0,300,300,GL_RGB, GL_FLOAT, imgData)
		glDrawPixels(300, 300, GL_ABGR_EXT, GL_UNSIGNED_BYTE, imgData);

		
*/
		//Application::Get().RTTexture->Update(imgData, width, height);

		//std::reverse(imgData, (unsigned char*)(imgData + width * height * 4));

		/*Encode the image*/
		unsigned error = lodepng::encode(filename.c_str(), imgData, m_Height, m_Width);

		/*if there's an error, display it*/
		if (error) printf("error %u: %s\n", error, lodepng_error_text(error));
	}
}