#pragma once
#include  "Engine/Layer.h" 
#include  "Engine/Logic/Scene.h" 

namespace Engine
{
	class ENGINE_API LogicLayer :
		public Layer
	{
	public:
		LogicLayer();
		~LogicLayer();

		void OnAttach() override;
		void OnUpdate() override;
		void OnEvent(Event& event) override;

	private:
		std::shared_ptr<Scene> m_Scene;
	};

}

