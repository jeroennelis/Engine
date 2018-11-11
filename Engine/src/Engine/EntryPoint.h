#pragma once

#ifdef ENGINE_PLATFORM_WINDOWS

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{
	Engine::Log::Init();
	EN_CORE_WARN("initialized Log!");
	int a = 10;
	EN_CLIENT_INFO("welcome! Var={0}", a);

	auto app = Engine::CreateApplication();
	app->Run();
	delete app;
}

#endif
