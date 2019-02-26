#include  "enpch.h" 
#include  "XMLWriter.h" 

namespace Engine {

	std::ofstream XMLWriter::file;

	void XMLWriter::write(std::shared_ptr<XMLNode> node, int niveau)
	{
		WriteStartTag(node, niveau);

		for (std::shared_ptr<XMLNode> child : node->Children())
			write(child, niveau + 1);
		WriteEndTag(node, niveau);
	}

	void XMLWriter::WriteStartTag(std::shared_ptr<XMLNode> node, int niveau)
	{
		for (int i = 0; i < niveau; i++)
			file <<  "\t" ;

		file <<  "<"  << node->Type().c_str();

		for (const std::pair<std::string, std::string>& attribute : node->Attibutes())
		{
			file << ""    << attribute.first.c_str() <<  "=\""   << attribute.second.c_str() <<  "\""  ;
		}
		file <<  ">\n" ;
	}

	void XMLWriter::WriteEndTag(std::shared_ptr<XMLNode> node, int niveau)
	{
		for (int i = 0; i < niveau; i++)
			file <<  "\t" ;
		file <<  "</"  << node->Type().c_str() <<  ">\n" ;
	}

	void XMLWriter::WriteScene(Scene* scene)
	{
		std::shared_ptr<XMLNode> sceneNode = std::make_shared<XMLNode>( "scene" );
		sceneNode->AddAttribute( "name" , scene->Name());
		for (std::shared_ptr<GameObject> go : scene->GameObjects())
		{
			AddGameObjectToNode(sceneNode, go);
		}

		file.open( "test.xml" );

		write(sceneNode, 0);

		file.close();

	}

	void XMLWriter::AddGameObjectToNode(std::shared_ptr<XMLNode> parent, std::shared_ptr<GameObject> go)
	{
		std::shared_ptr<XMLNode> node= std::make_shared<XMLNode>( "GameObject" );
		node->AddAttribute( "name" , go->Name());
		parent->AddChildNode(node);
		
		for (const std::shared_ptr<Component> comp : go->Components())
		{
			AddComponentToNode(node, comp);
		}
		for (std::shared_ptr<GameObject> child : go->Children())
		{
			AddGameObjectToNode(node, child);
		}
	}
	void XMLWriter::AddComponentToNode(std::shared_ptr<XMLNode> parent, const std::shared_ptr<Component> comp)
	{
		std::shared_ptr<XMLNode> node = std::make_shared<XMLNode>( "Component" );
		node->AddAttribute( "type" , std::to_string(comp->Type()));
		parent->AddChildNode(node);
	}

	XMLWriter::XMLWriter()
	{
	}


	XMLWriter::~XMLWriter()
	{
	}
}


