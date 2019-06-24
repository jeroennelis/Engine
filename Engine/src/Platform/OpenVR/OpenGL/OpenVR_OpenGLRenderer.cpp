#include "enpch.h"
#include "OpenVR_OpenGLRenderer.h"

#include "glad/glad.h"
#include "Engine/Application.h"

namespace Engine {

	OpenVR_OpenGLRenderer::OpenVR_OpenGLRenderer()
	{
	}

	OpenVR_OpenGLRenderer::~OpenVR_OpenGLRenderer()
	{
	}

	void OpenVR_OpenGLRenderer::Shutdown()
	{
		if (m_System)
		{
			vr::VR_Shutdown();
			m_System = nullptr;
		}
	}

	bool OpenVR_OpenGLRenderer::Init()
	{
		vr::EVRInitError eError = vr::VRInitError_None;
		m_System = vr::VR_Init(&eError, vr::VRApplication_Scene);

		//Check if the OpenVR runtime is installed
		if (!vr::VR_IsRuntimeInstalled())
		{
			EN_CORE_ERROR("the OpenVR runtime is not installed!");
			return false;
		}

		//Check if a HMD is connected
		if (!vr::VR_IsHmdPresent())
		{
			EN_CORE_ERROR("No HMD present!");
			return false;
		}

		//Initialize the connection with the VR hardware
		if (eError != vr::VRInitError_None)
		{
			Shutdown();
			EN_CORE_ERROR("Unable te init VR runtime: {0}", vr::VR_GetVRInitErrorAsEnglishDescription(eError));
			return false;
		}

		//initialize the IVRRenderModels interface
		m_RenderModels = (vr::IVRRenderModels*)vr::VR_GetGenericInterface(vr::IVRRenderModels_Version, &eError);
		if (eError != vr::VRInitError_None)
		{
			Shutdown();
			EN_CORE_ERROR("Unable to init render models interface: {0}", vr::VR_GetVRInitErrorAsEnglishDescription(eError));
			return false;
		}

		//Initialize the IVRCompositor interface
		m_Compositor = vr::VRCompositor();
		if (!m_Compositor)
		{
			Shutdown();
			EN_CORE_ERROR("Unable te init the IVRCompositor");
			return false;
		}


		// Set Up projection matrices
		UpdateProjections();

		//ToDo render models (controllers)



		m_System->GetRecommendedRenderTargetSize(&m_Width, &m_Height);


		//TEMP
		CreateVRFrameBuffer(m_Width, m_Height, m_LeftEyeFrameBuffer);
		CreateVRFrameBuffer(m_Width, m_Height, m_RightEyeFrameBuffer);

		//ZED
		//zedTest.Init(m_Width, m_Height);

		OpenGLRenderer::Init();

		return true;
	}

	void OpenVR_OpenGLRenderer::Update()
	{
		if (!m_System)
			return;

		m_Compositor->WaitGetPoses(m_TrackedDevicePoses, vr::k_unMaxTrackedDeviceCount, nullptr, 0);

		m_ValidPoseCount = 0;

		for (int devIndex = 0; devIndex < vr::k_unMaxTrackedDeviceCount; devIndex++)
		{
			if (m_TrackedDevicePoses[devIndex].bPoseIsValid)
			{
				m_ValidPoseCount++;

				m_DevicePoses[devIndex] = Maths::GLMMat4(m_TrackedDevicePoses[devIndex].mDeviceToAbsoluteTracking);

				if (m_DevClassChar[devIndex] == 0)
				{
					switch (m_System->GetTrackedDeviceClass(devIndex))
					{
					case vr::TrackedDeviceClass_Controller:			m_DevClassChar[devIndex] = 'C'; break;		//controller
					case vr::TrackedDeviceClass_HMD:				m_DevClassChar[devIndex] = 'H'; break;		//Head Mounted Device
					case vr::TrackedDeviceClass_Invalid:			m_DevClassChar[devIndex] = 'I'; break;
					case vr::TrackedDeviceClass_GenericTracker:		m_DevClassChar[devIndex] = 'G';	break;		//tracker
					case vr::TrackedDeviceClass_TrackingReference:	m_DevClassChar[devIndex] = 'T'; break;		//lighthouse
					default:										m_DevClassChar[devIndex] = '?'; break;
					}
				}
			}
		}
		if (m_TrackedDevicePoses[vr::k_unTrackedDeviceIndex_Hmd].bPoseIsValid)
		{
			m_HMDPose = glm::inverse(m_DevicePoses[vr::k_unTrackedDeviceIndex_Hmd]);
		}

		/*vr::Texture_t leftEyeTexture = { (void*)(uintptr_t)14, vr::TextureType_OpenGL, vr::ColorSpace_Gamma };
		vr::VRTextureBounds_t boundsLeft{ -0.0f,-0.0f,0.5f, 1.00f };
		vr::VRCompositor()->Submit(vr::Eye_Left, &leftEyeTexture, &boundsLeft);
		vr::Texture_t rightEyeTexture = { (void*)(uintptr_t)14, vr::TextureType_OpenGL, vr::ColorSpace_Gamma };
		vr::VRTextureBounds_t boundsRight{ 0.5f,-0.00f,1.00f, 1.00f };
		vr::EVRCompositorError error = vr::VRCompositor()->Submit(vr::Eye_Right, &rightEyeTexture, &boundsRight);
		std::cout << error << std::endl;*/



		//zedTest.Update();
	}

	void OpenVR_OpenGLRenderer::Render()
	{
		Update();


		glEnable(GL_MULTISAMPLE);
		//render left eye
		glBindFramebuffer(GL_FRAMEBUFFER, GetLeftEyeFrameBuffer().m_nRenderFramebufferId);
		glViewport(0, 0,  m_Width, m_Height);

		//Render Eye
		// set projection
		glm::mat4 temp = GetCurrentViewProjectionMatrix(vr::Eye_Left);
		SetProjectionMatrix(temp);
		RenderFrame();				//TODO
		// ----- Render Model rendering -----
		// TODO

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glDisable(GL_MULTISAMPLE);

		glBindFramebuffer(GL_READ_FRAMEBUFFER, GetLeftEyeFrameBuffer().m_nRenderFramebufferId);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, GetLeftEyeFrameBuffer().m_nResolveFramebufferId);

		glBlitFramebuffer(0, 0, m_Width, m_Height,
			0, 0, m_Width, m_Height,
			GL_COLOR_BUFFER_BIT,
			GL_LINEAR);

		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

		glEnable(GL_MULTISAMPLE);

		//render right eye
		glBindFramebuffer(GL_FRAMEBUFFER, GetRightEyeFrameBuffer().m_nRenderFramebufferId);
		glViewport(0, 0, m_Width, m_Height);
		SetProjectionMatrix(GetCurrentViewProjectionMatrix(vr::Eye_Right));
		RenderFrame();				//TODO

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glDisable(GL_MULTISAMPLE);

		glBindFramebuffer(GL_READ_FRAMEBUFFER, GetRightEyeFrameBuffer().m_nRenderFramebufferId);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, GetRightEyeFrameBuffer().m_nResolveFramebufferId);

		glBlitFramebuffer(0, 0, m_Width, m_Height,
			0, 0, m_Width, m_Height,
			GL_COLOR_BUFFER_BIT,
			GL_LINEAR);

		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

		//submit

		vr::Texture_t leftEyeTexture = { (void*)(uintptr_t)GetLeftEyeFrameBuffer().m_nResolveTextureId, vr::TextureType_OpenGL, vr::ColorSpace_Gamma };
		vr::VRCompositor()->Submit(vr::Eye_Left, &leftEyeTexture);
		vr::Texture_t rightEyeTexture = { (void*)(uintptr_t)GetRightEyeFrameBuffer().m_nResolveTextureId, vr::TextureType_OpenGL, vr::ColorSpace_Gamma };
		vr::VRCompositor()->Submit(vr::Eye_Right, &rightEyeTexture);

		OpenGLRenderer::Render();
	}

	void OpenVR_OpenGLRenderer::CleanUp()
	{
	}

	glm::mat4& OpenVR_OpenGLRenderer::GetCurrentViewProjectionMatrix(vr::Hmd_Eye eye)
	{
		glm::mat4 matMVP;
		if (eye == vr::Eye_Left)
		{
			matMVP = m_ProjectionMatrixLeft * m_HMDPose;
		}
		else if (eye == vr::Eye_Right)
		{
			matMVP = m_ProjectionMatrixRight * m_HMDPose;
		}

		return matMVP;
	}

	void OpenVR_OpenGLRenderer::UpdateProjections()
	{
		m_ProjectionMatrixLeft = Maths::GLMMat4(m_System->GetProjectionMatrix(vr::Eye_Left, 0.1f, 1000.0f));
		m_ProjectionMatrixRight = Maths::GLMMat4(m_System->GetProjectionMatrix(vr::Eye_Right, 0.1f, 1000.0f));
		m_EyePosLeft = glm::inverse(Maths::GLMMat4(m_System->GetEyeToHeadTransform(vr::Eye_Left)));
		m_EyePosRight = glm::inverse(Maths::GLMMat4(m_System->GetEyeToHeadTransform(vr::Eye_Right)));
	}

	bool OpenVR_OpenGLRenderer::CreateVRFrameBuffer(int nWidth, int nHeight, VRFramebuffer& framebufferDesc)
	{
		glGenFramebuffers(1, &framebufferDesc.m_nRenderFramebufferId);
		glBindFramebuffer(GL_FRAMEBUFFER, framebufferDesc.m_nRenderFramebufferId);

		glGenRenderbuffers(1, &framebufferDesc.m_nDepthBufferId);
		glBindRenderbuffer(GL_RENDERBUFFER, framebufferDesc.m_nDepthBufferId);
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH_COMPONENT, nWidth, nHeight);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, framebufferDesc.m_nDepthBufferId);

		glGenTextures(1, &framebufferDesc.m_nRenderTextureId);
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, framebufferDesc.m_nRenderTextureId);
		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGBA8, nWidth, nHeight, true);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, framebufferDesc.m_nRenderTextureId, 0);

		glGenFramebuffers(1, &framebufferDesc.m_nResolveFramebufferId);
		glBindFramebuffer(GL_FRAMEBUFFER, framebufferDesc.m_nResolveFramebufferId);

		glGenTextures(1, &framebufferDesc.m_nResolveTextureId);
		glBindTexture(GL_TEXTURE_2D, framebufferDesc.m_nResolveTextureId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth, nHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebufferDesc.m_nResolveTextureId, 0);

		// check FBO status
		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (status != GL_FRAMEBUFFER_COMPLETE)
		{
			return false;
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		return true;
	}



}

