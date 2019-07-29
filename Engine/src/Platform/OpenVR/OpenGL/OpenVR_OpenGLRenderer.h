#pragma once

#include "Engine/Renderer/Renderer.h"
#include "Platform/OpenGl/Renderer/OpenGLRenderer.h"

#include "Engine/Maths.h"
#include "openvr.h"

namespace Engine {

	//TEMP

	struct VRFramebuffer
	{
		GLuint m_nDepthBufferId;
		GLuint m_nRenderTextureId;
		GLuint m_nRenderFramebufferId;
		GLuint m_nResolveTextureId;
		GLuint m_nResolveFramebufferId;
	};

	class OpenVR_OpenGLRenderer : public OpenGLRenderer
	{
	public:
		OpenVR_OpenGLRenderer();
		virtual ~OpenVR_OpenGLRenderer();

		void Shutdown();

		virtual bool Init() override;
		virtual void Render() override;
		virtual void CleanUp() override;

		void Update();

		virtual void* GetSceneFrameBufferTexture() override { return OpenGLRenderer::GetSceneFrameBufferTexture(); }
		virtual void* GetGameFrameBufferTexture() override { return OpenGLRenderer::GetGameFrameBufferTexture(); };

		inline const glm::mat4* GetDevicePoses() { return m_DevicePoses; }

		inline const VRFramebuffer& GetLeftEyeFrameBuffer() { return m_LeftEyeFrameBuffer; }
		inline const VRFramebuffer& GetRightEyeFrameBuffer() { return m_RightEyeFrameBuffer; }

		inline const uint32_t GetRenderWidth() { return m_Width; }
		inline const uint32_t GetRenderHeight() { return m_Height; }

		glm::mat4& GetCurrentViewProjectionMatrix(vr::Hmd_Eye eye);

	private:
		void UpdateProjections();

		bool CreateVRFrameBuffer(int nWidth, int nHeight, VRFramebuffer& framebufferDesc);

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

		uint32_t m_Width, m_Height;

		VRFramebuffer m_LeftEyeFrameBuffer;
		VRFramebuffer m_RightEyeFrameBuffer;
	};


}
