#pragma once

#include "Engine/Core.h"
#include "Layer.h"

namespace Engine {

	class ENGINE_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		/**
		*	Layers wil be pushed into the list at the position m_LayerInsert
		*	Overlays will always be pushed into the list after the layers
		*	This insures the overlays will be rendered last and appear on top
		**/

		void PushLayer(Layer* layer);
		void PushOverLay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverLay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:
		std::vector<Layer*> m_Layers;
		std::vector<Layer*>::iterator m_LayerInsert;
	};
}