#pragma once
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"

namespace Engine {
	struct RawModel {
		VertexArray* va;
		IndexBuffer* ib;

		RawModel(VertexArray* vertexArray, IndexBuffer* indexBuffer);
	};
}