#pragma once
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
#include "FrameBuffer.h"

namespace Engine {
	struct RawModel {
		VertexArray* va;
		IndexBuffer* ib;

		RawModel(VertexArray* vertexArray, IndexBuffer* indexBuffer);

		void RenderPreview();

		void RenderProjectInfo();

		FrameBuffer* m_Preview;


		
	};
}