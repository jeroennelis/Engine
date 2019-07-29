#pragma once

#include "RTCamera.h"

#include "Platform/RayTracer/World/ViewPlane.h"

namespace Engine {

	class RTPinhole : public RTCamera
	{
	public:
		RTPinhole() :RTCamera(), m_Zoom(1.0), m_Distance(0.1f), m_FOV(90.0f) {}

		virtual ~RTPinhole() {}

		virtual void render_scene(World * world) override;
		virtual void RenderStereo(World* world, float x, int offset);

		glm::vec3 ray_direction(const glm::vec2& p, const ViewPlane& vp) const;

		inline void SetViewDistance(const float distance) { m_Distance = distance; }
		inline void SetZoom(const float zoom) { m_Zoom = zoom; }
		inline void SetFOV(const float fov) { m_FOV = fov; }

	private:
		float m_Distance;		// view-plane distance
		float m_Zoom;			// zoom factor
		float m_FOV;			// field of view
	};
}