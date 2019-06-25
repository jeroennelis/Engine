#pragma once

#include "RTCamera.h"

namespace Engine {

	class RTPinhole : public RTCamera
	{
	public:
		RTPinhole() :RTCamera(), m_Zoom(1.0) {}

		virtual ~RTPinhole() {}

		virtual void render_scene(World * world) override;
		virtual void RenderStereo(World* world, float x, int offset);

		glm::vec3 ray_direction(const glm::vec2& p) const;

		inline void SetViewDistance(const float distance) { m_Distance = distance; }

	private:
		float m_Distance;		// view-plane distance
		float m_Zoom;			// zoom factor
	};
}