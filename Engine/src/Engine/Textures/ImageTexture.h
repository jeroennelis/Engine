#pragma once

#include "Texture_temp.h"

namespace Engine {

	class ImageTexture : public Texture_temp
	{

	public:
		virtual void RenderInspectorInfo() {}

		virtual void Bind(unsigned int slot = 0) const {};
	protected:/*
		int m_Witdh;
		int m_Height;*/
	};
}