#pragma once

#include "Shader.h"
#include "Loader.h"

namespace Engine {
	
	class TerrainRenderer
	{
	private:
		Shader * m_Shader;

	public:
		TerrainRenderer();
		~TerrainRenderer();

		void Render();
	};
}
