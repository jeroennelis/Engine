#pragma once

#include "Component.h"

namespace Engine {

	class RenderComponent : public Component
	{
	public:

		RenderComponent(const std::string& name);

		virtual const unsigned int Type() const override;

		virtual void Render() = 0;
		const static unsigned int ComponentType;

	private:
	};
}