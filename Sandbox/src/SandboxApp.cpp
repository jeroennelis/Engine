#include "Engine.h"

class Sandbox : public Engine::Application
{
public:
	Sandbox()
	{
		PushLayer(new Engine::LogicLayer());
		PushOverLay(new Engine::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Engine::Application* Engine::CreateApplication()
{
	return new Sandbox();
}

