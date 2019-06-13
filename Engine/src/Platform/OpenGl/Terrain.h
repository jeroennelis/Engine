#pragma once

#include "Engine/Components/Component.h"
#include "Engine/Components/Transform.h"
#include "RawModel.h"
#include "Texture.h"
#include "Loader.h"

namespace Engine {

	class Terrain
	{
	public:
		Terrain(int gridX, int gridZ, Texture * texure, Loader* loader);
		~Terrain();

	private:

		const float SIZE;
		const int VERTEX_COUNT;

		float x;
		float z;
		RawModel m_Model;
		Texture * texture;

		RawModel GenerateTerrain(Loader* loader);


	};
}