#include "enpch.h"

#include "image.h"
#include <algorithm>
#include "vendor/lodepng/lodepng.h"
#include <glad/glad.h>+
#include <gl/GL.h>

namespace Engine {
	Image::Image(int width, int height)
		: width(width), height(height)
	{
		data = new glm::vec3[width * height];
		imgData = new unsigned char[4 * width * height];
	}

	Image::~Image()
	{
		delete[] data;
		delete[] imgData;
	}

	int Image::getWidth() const
	{
		return width;
	}

	int Image::getHeight() const
	{
		return height;
	}

	glm::vec3* Image::getPixel(int x, int y)
	{
		return data + (x + y * width);
	}

	void Image::setPixel(int x, int y, const glm::vec3& color)
	{
		data[y + x * width] = color;
		imgData[4 * (x *width + y) + 0] =
			(unsigned char)(color.r * 255.0f);
		imgData[4 * (x * width + y) + 1] =
			(unsigned char)(color.g * 255.0f);
		imgData[4 * (x * width + y) + 2] =
			(unsigned char)(color.b * 255.0f);
		imgData[4 * (x * width + y) + 3] = 255;
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
		//std::reverse(imgData, (unsigned char*)(imgData + 300 * 300 * 4));

		/*Encode the image*/
		unsigned error = lodepng_encode32_file(filename.c_str(), imgData, width, height);

		/*if there's an error, display it*/
		if (error) printf("error %u: %s\n", error, lodepng_error_text(error));

		delete[] imgData;
	}
}