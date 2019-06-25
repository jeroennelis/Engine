#pragma once

#include "RTCamera.h"

namespace Engine { 
	class RTFishEye : public RTCamera 
	{
	
	public:
		RTFishEye();
		~RTFishEye();

		glm::vec3 RayDirection(const glm::vec2& pp, const int hres, const int vres, const float s, float& r) const;

		virtual void render_scene(World * world) override;
		virtual void RenderStereo(World* world, float x, int offset);
	
	private:
		float m_PSIMax;
	};
}