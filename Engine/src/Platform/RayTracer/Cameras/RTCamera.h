#pragma once

namespace Engine {


	class World;

	class RTCamera
	{
	public:
		RTCamera();
		virtual ~RTCamera() {}
		
		void compute_uvw(void);

		virtual void render_scene(World* world) = 0;
		virtual void RenderStereo(World* world, float x, int offset) = 0;

		inline void SetEye(const glm::vec3& eye) { m_Eye = eye; }
		inline void SetLookat(const glm::vec3& lookat) { m_Lookat = lookat; }

	protected:

		glm::vec3 m_Eye;
		glm::vec3 m_Lookat;
		glm::vec3 m_Up;
		glm::vec3 m_U, m_V, m_W;
		float m_ExposureTime;

	};
}