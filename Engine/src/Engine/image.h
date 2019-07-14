#pragma once

#include <string>
#include <fstream>

namespace Engine {
	class Image
	{
	protected:
		int m_Width;
		int m_Height;
		int m_BPP;
		glm::vec3* data;
		unsigned char* imgData;

	public:
		Image(int width, int height);
		Image(const std::string& path);

		virtual ~Image();

		unsigned int getWidth() const;
		unsigned int getHeight() const;

		glm::vec3 GetColor(int row, int column);

		glm::vec3* getPixel(int x, int y);
		void setPixel(int x, int y, const glm::vec3& color);

		void saveImage(std::string filename) const;
	};
}
