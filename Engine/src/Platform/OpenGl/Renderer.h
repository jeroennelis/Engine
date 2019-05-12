#pragma once

#include "GL.h"

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

namespace Engine {

	class Renderer
	{
	public:
		virtual void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
		void Clear() const;
	};
}
