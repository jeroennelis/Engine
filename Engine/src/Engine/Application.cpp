#include  "enpch.h" 
#include  "Application.h" 

#include "Input.h" 

#include "Logic/LogicLayer.h"
#include "Renderer/Renderer.h"
#include "Renderer/Buffer.h"
#include "image.h"
#include "Platform/OpenGl/Materials/OpenGLTerrainMaterial.h"
#include "Platform/OpenGl/Loader.h"
#include "Platform/OpenGl/TerrainRenderer.h"
#include "Platform/OpenGl/Terrain.h"

#include "PxPhysicsAPI.h"
#include "extensions/PxDefaultAllocator.h"

class physxErrorCallback : public physx::PxErrorCallback
{
public:
	physxErrorCallback() {}
	~physxErrorCallback() {}

	virtual void reportError(physx::PxErrorCode::Enum e, const char* message, const char* file, int line)
	{
		const char* errorCode = NULL;

		switch (e)
		{
		case physx::PxErrorCode::eNO_ERROR:
			errorCode = "no error";
			break;
		case physx::PxErrorCode::eINVALID_PARAMETER:
			errorCode = "invalid parameter";
			break;
		case physx::PxErrorCode::eINVALID_OPERATION:
			errorCode = "invalid operation";
			break;
		case physx::PxErrorCode::eOUT_OF_MEMORY:
			errorCode = "out of memory";
			break;
		case physx::PxErrorCode::eDEBUG_INFO:
			errorCode = "info";
			break;
		case physx::PxErrorCode::eDEBUG_WARNING:
			errorCode = "warning";
			break;
		case physx::PxErrorCode::ePERF_WARNING:
			errorCode = "performance warning";
			break;
		case physx::PxErrorCode::eABORT:
			errorCode = "abort";
			break;
		case physx::PxErrorCode::eINTERNAL_ERROR:
			errorCode = "internal error";
			break;
		case physx::PxErrorCode::eMASK_ALL:
			errorCode = "unknown error";
			break;
		}

		PX_ASSERT(errorCode);
		if (errorCode)
		{
			char buffer[1024];
			sprintf(buffer, "%s (%d) : %s : %s\n", file, line, errorCode, message);
			std::cout << buffer << std::endl;
			/*physx::shdfnd::printString(buffer);*/

			// in debug builds halt execution for abort codes
			PX_ASSERT(e != PxErrorCode::eABORT);

			// in release builds we also want to halt execution 
			// and make sure that the error message is flushed  
			while (e == physx::PxErrorCode::eABORT)
			{
				std::cout << buffer << std::endl;
				/*physx::shdfnd::printString(buffer);
				physx::shdfnd::Thread::sleep(1000);*/
			}
		}
	}
};

namespace Engine {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr; 


	Application::Application()
	{
		EN_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create(Renderer::GetAPI()));
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		m_Window->SetVSync(true);

		Renderer::Init();


		//--physex test--------------------
		static physxErrorCallback gphysicsErrorCallback;
		static physx::PxDefaultAllocator gDefaultAllocatorCallback;

		physx::PxFoundation* m_Foundation = PxCreateFoundation(PX_PHYSICS_VERSION, gDefaultAllocatorCallback, gphysicsErrorCallback);
		if (!m_Foundation)
			EN_CORE_FATAL("PxCreateFoundation failed!");
		else
			EN_CORE_INFO("physx initialized");

		m_Foundation->release();

	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event & e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClosed));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			//EN_CORE_TRACE(e.ToString());
			(*--it)->OnEvent(e);
			if (e.Handled())
				break;
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();
			Renderer::Get()->Render();

			

			m_Window->OnUpdate();			
		}		

		Renderer::Get()->CleanUp();

	}

	void Application::PushLayer(Layer * layer)
		{
			m_LayerStack.PushLayer(layer);
			layer->OnAttach();
		}

		void Application::PushOverLay(Layer * overlay)
		{
			m_LayerStack.PushOverLay(overlay);
			overlay->OnAttach();
	}

	bool Application::OnWindowClosed(WindowCloseEvent & e)
	{
		m_Running = false;
		return true;
	}
}


