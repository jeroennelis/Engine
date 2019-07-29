#pragma once
#include  "Engine/Core.h" 
#include <iostream>
namespace Engine {

#define COMP_UNASSIGNED		0
#define COMP_TRANSFORM		1
#define COMP_MESHRENDERER	2
#define COMP_CAMERA			3
#define COMP_LIGHT			4
#define COMP_POINTCLOUDRENDERER 5
#define COMP_CONECLOUDRENDERER 6
#define COMP_TEST			100
#define COMP_RENDERER		99;

	class ENGINE_API Component
	{
	public:
		inline virtual ~Component() {}
		virtual void Update() {}
		virtual void RenderInspectorInfo() {}
		virtual const unsigned int Type() const = 0;

		inline const std::string& Name() const { return m_Name; }
		inline const unsigned int ID()const { return m_ComponentID; }

	protected:
		inline Component(const std::string & name, const unsigned int ID) :m_Name(name), m_ComponentID(ID) {}

	protected:
		std::string  m_Name;
		unsigned int m_ComponentID;
	};
}
