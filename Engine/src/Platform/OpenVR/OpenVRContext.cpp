#include "enpch.h"

#include "OpenVRContext.h"

#include "Platform/ZED/ZedTest.h"

//#include "Platform/ZED/ZedTest.h"

namespace Engine {

	//Constructor

	OpenVRContext::OpenVRContext()
		:m_System(nullptr)
	{
	}


	//Destructor

	OpenVRContext::~OpenVRContext()
	{
		Shutdown();
	}

	void OpenVRContext::Shutdown()
	{
		if (m_System)
		{
			vr::VR_Shutdown();
			m_System = nullptr;
		}
	}



	bool OpenVRContext::Init()
	{
		vr::EVRInitError eError = vr::VRInitError_None;
		m_System = vr::VR_Init(&eError, vr::VRApplication_Scene);

		//Check if the OpenVR runtime is installed
		if(!vr::VR_IsRuntimeInstalled())
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
		m_RenderModels = (vr::IVRRenderModels *)vr::VR_GetGenericInterface(vr::IVRRenderModels_Version, &eError);
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

		//ZED
		
		
		m_System->GetRecommendedRenderTargetSize(&m_Width, &m_Height);


		zedTest.Init(m_Width, m_Height);

		return true;
	}

	void OpenVRContext::Update()
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

		vr::Texture_t leftEyeTexture = { (void*)(uintptr_t)14, vr::TextureType_OpenGL, vr::ColorSpace_Gamma };
		vr::VRTextureBounds_t boundsLeft{ -0.0f,-0.0f,0.5f, 1.00f };
		vr::VRCompositor()->Submit(vr::Eye_Left, &leftEyeTexture, &boundsLeft);
		vr::Texture_t rightEyeTexture = { (void*)(uintptr_t)14, vr::TextureType_OpenGL, vr::ColorSpace_Gamma };
		vr::VRTextureBounds_t boundsRight{ 0.5f,-0.00f,1.00f, 1.00f };
		vr::EVRCompositorError error = vr::VRCompositor()->Submit(vr::Eye_Right, &rightEyeTexture, &boundsRight);
		std::cout << error << std::endl;



		zedTest.Update();
	}

	void OpenVRContext::UpdateProjections()
	{
		m_ProjectionMatrixLeft = Maths::GLMMat4(m_System->GetProjectionMatrix(vr::Eye_Left, 0.1f, 1000.0f));
		m_ProjectionMatrixRight = Maths::GLMMat4(m_System->GetProjectionMatrix(vr::Eye_Right, 0.1f, 1000.0f));
		m_EyePosLeft = glm::inverse(Maths::GLMMat4(m_System->GetEyeToHeadTransform(vr::Eye_Left)));
		m_EyePosRight = glm::inverse(Maths::GLMMat4(m_System->GetEyeToHeadTransform(vr::Eye_Right)));
	}

	
}