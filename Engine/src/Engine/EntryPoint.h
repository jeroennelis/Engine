#pragma once

#ifdef EN_PLATFORM_WINDOWS


#define _CRTDBG_MAP_ALLOC

#include <stdlib.h>
#include <crtdbg.h>

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Engine::Log::Init();
	EN_CORE_WARN( "initialized Log!" );
	int a = 10;
	EN_INFO( "welcome! Var={0}" , a);

	auto app = Engine::CreateApplication();
	app->Run();
	delete app;

	_CrtDumpMemoryLeaks();

	while (1);
}

#endif
