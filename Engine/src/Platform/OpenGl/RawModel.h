#pragma once

#include "Engine/Renderer/VertexArray.h"
#include "FrameBuffer.h"

#include "Platform/RayTracer/Utilities/BBox.h"

namespace Engine {

	struct RawModel {
		std::shared_ptr<VertexArray> va;

		std::string path;

		RawModel();
		RawModel(const std::shared_ptr<VertexArray>& vertexArray);

		void RenderPreview();

		void RenderProjectInfo();

		FrameBuffer* m_Preview;

		BBox bBox;
		
	};
}