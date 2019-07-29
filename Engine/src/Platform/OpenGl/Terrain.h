#pragma once

#include "Engine/Components/Component.h"
#include "Engine/Components/Transform.h"
#include "RawModel.h"
#include "GLTexture.h"
#include "Loader.h"

namespace Engine {

	class Terrain
	{
	public:
		Terrain(int gridX, int gridZ, const std::string& heightMap);
		~Terrain();

		inline RawModel* GetModel() { return &m_Model; }

	private:

		const float SIZE;
		const float MAX_HEIGHT;
		const int VERTEX_COUNT;
		const int MAX_PIXEL_COLOUR;

		float m_X;
		float m_Z;
		RawModel m_Model;


		std::vector<std::vector<float>> m_Heights;

	private:
		RawModel GenerateTerrain(const std::string& heightMap);
		float GetHeigt(int x, int y, unsigned char* localBuffer, int height);
		glm::vec3 CalculateNormal(int x, int y, unsigned char* localBuffer, int height);


	};
}