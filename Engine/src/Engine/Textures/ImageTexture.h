#pragma once

#include "Texture.h"

namespace Engine {

	class ImageTexture : public Texture
	{

	public:
		virtual void RenderInspectorInfo() {}

		virtual void Bind(unsigned int slot = 0) const {};
	protected:/*
		int m_Witdh;
		int m_Height;*/
	};
}