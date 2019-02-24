#pragma once
#include <fstream>
#include <sstream>
#include <iostream>
#include "XMLNode.h"

namespace Engine
{
	class XMLReader{

	public:
		static XMLNode ReadFile(const std::string& fileName);
	};
}
