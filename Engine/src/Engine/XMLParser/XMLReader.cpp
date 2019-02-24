#include "enpch.h"
#include "XMLReader.h"


XMLNode Engine::XMLReader::ReadFile(const std::string& fileName)
{
	std::ifstream stream(fileName);
	
	if (!stream.is_open())
	{
		EN_CORE_ERROR("could not open file: {0}", fileName);
		return 0;
	}

	std::string line;
	XMLNode node("test");
	while (std::getline(stream, line))
	{
		/*if (line._Starts_with("<scene"))
		{
			std::string segments[] = line
			EN_CORE_INFO("start");
		}line.s*/

	}
	
	

	

	stream.close();
	return node;
}
