#pragma once

#include "RTCamera.h"

namespace Engine {

	class RTSpherical : public RTCamera
	{

	public:
		RTSpherical();
		~RTSpherical();

		glm::vec3 RayDirection(const glm::vec2 pp, const int hres, const int vres, const float s)const;

		virtual void render_scene(World * world) override;
		void RenderStereo(World * world, float x, int offset) override;

	private:
		float m_LambdaMax;
		float m_PSIMax;
		

	};
}