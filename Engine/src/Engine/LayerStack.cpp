#include  "enpch.h" 
#include  "LayerStack.h" 

namespace Engine {
	Engine::LayerStack::LayerStack()
	{
	}

	Engine::LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
			delete layer;
	}

	void Engine::LayerStack::PushLayer(Layer * layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
	}

	void Engine::LayerStack::PushOverLay(Layer * overlay)
	{
		m_Layers.emplace_back(overlay);
	}

	void Engine::LayerStack::PopLayer(Layer * layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	void Engine::LayerStack::PopOverLay(Layer * overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
			m_Layers.erase(it);
	}

}