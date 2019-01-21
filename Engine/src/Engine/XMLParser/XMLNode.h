#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>

class XMLNode
{
public:
	XMLNode(const std::string& name);
	~XMLNode();

	inline void AddChildNode(std::shared_ptr<XMLNode> child) { m_ChildNodes.push_back(child); }
	inline void AddAttribute(const std::string& name, const std::string& value) { m_Attributes.insert({ name, value }); }

	inline const std::vector<std::shared_ptr<XMLNode>>& Children() const { return m_ChildNodes; }
	inline const std::unordered_map<std::string, std::string> Attibutes() const { return m_Attributes; }
	inline const std::string& Type() const { return m_Type; }

private:
	std::string m_Type;
	
	std::vector<std::shared_ptr<XMLNode>> m_ChildNodes;
	std::unordered_map<std::string, std::string> m_Attributes;
};

