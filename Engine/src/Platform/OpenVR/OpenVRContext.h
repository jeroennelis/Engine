#pragma once

#include "openvr.h"
#include "Engine/Maths.h"

namespace Engine {

	class OpenVRContext
	{
	public:
		OpenVRContext();
		~OpenVRContext();

		bool Init();
		void Shutdown();
		void Update();

		inline const glm::mat4* GetDevicePoses() { return m_DevicePoses; }

	private:
		void UpdateProjections();

	private:

		//interface to access display config info, tracking date, 
		//distortion functions, controller states, events and device props
		vr::IVRSystem* m_System;

		vr::IVRRenderModels* m_RenderModels;

		//access to the compositor subsystem.
		//simplifies the process of drawing images (distortion, prediction, sync, ...)
		vr::IVRCompositor* m_Compositor;

		//projection matrices
		glm::mat4 m_ProjectionMatrixLeft;
		glm::mat4 m_ProjectionMatrixRight;
		glm::mat4 m_EyePosLeft;
		glm::mat4 m_EyePosRight;

		//Holds the poses for the devices, including the velocity
		vr::TrackedDevicePose_t m_TrackedDevicePoses[vr::k_unMaxTrackedDeviceCount];

		int m_ValidPoseCount;
		int m_ValidPoseCount_Last;

		//holds the transformation matrix for the devices
		glm::mat4 m_DevicePoses[vr::k_unMaxTrackedDeviceCount];
		glm::mat4 m_HMDPose;

		char m_DevClassChar[vr::k_unMaxTrackedDeviceCount];


	};
}