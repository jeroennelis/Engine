#include "enpch.h"
#include "LogicLayer.h"

namespace Engine
{
	LogicLayer::LogicLayer()
		:Layer("Logic Layer")
	{
		m_Scene = std::make_shared<Scene>();
	}


	LogicLayer::~LogicLayer()
	{
	}

	void LogicLayer::OnAttach()
	{
		EN_CORE_INFO("attached Logic Layer");
	}

	void LogicLayer::OnUpdate()
	{
		Scene::Current()->OnUpdate();
	}
}


