#include "enpch.h"
#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Engine/Log.h"

namespace Engine {

	Application::Application()
	{
	}


	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1200, 720);
		EN_TRACE(e);

		while(true);
	}
}


