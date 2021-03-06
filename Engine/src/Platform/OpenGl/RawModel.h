#pragma once

#include "Engine/Renderer/VertexArray.h"
#include "FrameBuffer.h"

namespace Engine {

	struct RawModel {
		std::shared_ptr<VertexArray> va;

		RawModel();
		RawModel(const std::shared_ptr<VertexArray>& vertexArray);

		void RenderPreview();

		void RenderProjectInfo();

		FrameBuffer* m_Preview;


		
	};
}