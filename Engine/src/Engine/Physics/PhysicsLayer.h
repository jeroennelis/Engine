#pragma once
#include "Engine/Layer.h"

namespace Engine {

	class PhysicsLayer : public Layer
	{
	public:
		PhysicsLayer();

		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnUpdate();
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}
	};
}
