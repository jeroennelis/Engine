#pragma once
#include "Engine/Core.h"
#include "Engine/Layer.h"
namespace Engine {

	class ENGINE_API RenderLayer : 
						public Layer
	{
		virtual void OnAttach();
		virtual void OnDetach() {}
		virtual void OnUpdate();
		virtual void OnEvent(Event& event) {}
	};
}