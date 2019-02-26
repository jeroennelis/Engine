#pragma once
#include <iostream>
#include <fstream>
#include  "Engine/Logic/Scene.h" 
#include  "XMLNode.h" 

namespace Engine {
	class XMLWriter
	{
	public:
		XMLWriter();
		~XMLWriter();

		static void WriteScene(Scene* scene);

	private:
		static void write(std::shared_ptr<XMLNode>, int niveau);
		static void WriteStartTag(std::shared_ptr<XMLNode> node, int niveau);
		static void WriteEndTag(std::shared_ptr<XMLNode> node, int niveau);

		static void AddGameObjectToNode(std::shared_ptr<XMLNode> parent, std::shared_ptr<GameObject> go);
		static void AddComponentToNode(std::shared_ptr<XMLNode> parent, const std::shared_ptr<Component> comp);
		static std::ofstream file;
	};
}



