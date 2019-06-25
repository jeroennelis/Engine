#pragma once

#include "RTCamera.h"

namespace Engine {

	typedef enum ViewingType {
		parallel,
		transverse
	};

	class RTStereoCamera : public RTCamera
	{
	public:
		RTStereoCamera();
		~RTStereoCamera();

		inline void SetLeftCamera(RTCamera* cam) { m_LeftCamera = cam; }
		inline void SetRightCamera(RTCamera* cam) { m_RightCamera = cam; }

		inline void UseParallelViewing() { m_Viewing = parallel; }
		inline void UseTransverseViewing() { m_Viewing = transverse; }

		inline void SetPixelGap(const int gap) { m_PixelGap = gap; }
		inline void SetStereoAngle(const float angle) { m_Beta = angle; }

		void SetUpCameras();

		virtual void render_scene(World* world) override;
		virtual void RenderStereo(World * world, float x, int offset) override;


	private:
		ViewingType m_Viewing;
		int m_PixelGap;
		float m_Beta;
		RTCamera* m_LeftCamera;
		RTCamera* m_RightCamera;
	};
}