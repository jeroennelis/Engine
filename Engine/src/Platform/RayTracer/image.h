#pragma once

#include <string>
#include <fstream>

namespace Engine {
	class Image
	{
	protected:
		int width, height;
		glm::vec3* data;
		unsigned char* imgData;

	public:
		Image(int width, int height);

		virtual ~Image();

		int getWidth() const;
		int getHeight() const;

		glm::vec3* getPixel(int x, int y);
		void setPixel(int x, int y, glm::vec3& color);

		void saveImage(std::string filename) const;
	};
}
