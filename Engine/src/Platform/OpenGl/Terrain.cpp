#include "enpch.h"

#include "Terrain.h"

namespace Engine {

	Terrain::Terrain(int gridX, int gridZ, Texture* texure, Loader* loader)
		:SIZE(800), VERTEX_COUNT(128)
	{
		m_Model = GenerateTerrain(loader);
	}

	Terrain::~Terrain()
	{
	}

	RawModel Terrain::GenerateTerrain(Loader* loader)
	{
		return RawModel();
	}
}


