#include "enpch.h"
#include "TerrainRenderer.h"

Engine::TerrainRenderer::TerrainRenderer()
{
	m_Shader = Loader::Get()->GetShader("terrain");
}

Engine::TerrainRenderer::~TerrainRenderer()
{
}
