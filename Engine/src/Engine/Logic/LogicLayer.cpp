#include  "enpch.h"
#include  "LogicLayer.h" 

namespace Engine
{
	LogicLayer::LogicLayer()
		:Layer( "Logic Layer" )
	{
		m_Scene = std::make_shared<Scene>();
	}


	LogicLayer::~LogicLayer()
	{
	}

	void LogicLayer::OnAttach()
	{
		EN_CORE_INFO( "attached Logic Layer" );
	}

	void LogicLayer::OnUpdate()
	{
		Scene::Current()->OnUpdate();
		Scene::Current()->Render();
	}

	void LogicLayer::OnEvent(Event & event)
	{
		Scene::Current()->GetSceneCamera()->OnEvent(event);
		//EN_CORE_INFO("{0}",event.ToString());
	}
}


