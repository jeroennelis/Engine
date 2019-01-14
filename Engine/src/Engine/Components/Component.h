#pragma once
#include "Engine/Core.h"
#include <iostream>
namespace Engine {

#define COMP_UNASSIGNED	0
#define COMP_TEST		1

	class ENGINE_API Component
	{
	public:
		inline virtual ~Component() {}
		virtual void Update() = 0;

		inline const std::string& Name() const { return m_Name; }
		inline const unsigned int const ID()const { return m_ComponentID; }

	protected:
		inline Component(const std::string & name, const unsigned int ID) :m_Name(name), m_ComponentID(ID) {}

	protected:
		std::string  m_Name;
		unsigned int m_ComponentID;
	};
}
