#include "enpch.h"
#include "OBJLoader.h"
//
//
//
//
//OBJLoader::OBJLoader()
//{
//}
//
//
//OBJLoader::~OBJLoader()
//{
//}
//
//RawModel OBJLoader::loadOBJModel(const std::string & objFile, Loader & loader)
//{
//	//ParseMaterialFile(materialFile);
//	std::ifstream file(objFile);
//	std::vector<Vertex*> vertices;
//	std::vector<glm::vec2> textures;
//	std::vector<glm::vec3> normals;
//	std::vector<int> indices;
//
//
//	std::string line;
//	if (!file.is_open())
//	{
//		std::cout << "file: " << objFile << "could not be opened!" << std::endl;
//		return RawModel{ 0,0 };
//	}
//
//	while (file.good())
//	{
//		const char* lineCStr = line.c_str();
//
//		getline(file, line);
//		if (lineCStr[0] == 'v')
//		{
//			if (lineCStr[1] == 't')
//			{
//				std::vector<std::string> currentLine = SplitString(line, ' ');
//				glm::vec2 newTexture(strtof((currentLine[1]).c_str(), 0), strtof(currentLine[2].c_str(), 0));
//
//				textures.push_back(newTexture);
//			}
//			else if (lineCStr[1] == 'n')
//			{
//				std::vector<std::string> currentLine = SplitString(line, ' ');
//				glm::vec3 newNormal(strtof((currentLine[1]).c_str(), 0), strtof(currentLine[2].c_str(), 0), strtof(currentLine[3].c_str(), 0));
//
//				normals.push_back(newNormal);
//			}
//			else if (lineCStr[1] == ' ' || lineCStr[1] == '\t')
//			{
//				std::vector<std::string> currentLine = SplitString(line, ' ');
//				glm::vec3 vertex(strtof((currentLine[1]).c_str(), 0), strtof(currentLine[2].c_str(), 0), strtof(currentLine[3].c_str(), 0));
//
//				vertices.push_back(new Vertex((int)vertices.size(), vertex));
//			}
//		}
//		else if (line.substr(0, 2) == "f ")
//			break;
//	}
//	while ((!line.empty()) && (line.substr(0, 2) == "f "))
//	{
//		std::vector<std::string> currentLine = SplitString(line, ' ');
//		std::vector<std::string> vertex1 = SplitString(currentLine[1], '/');
//		std::vector<std::string> vertex2 = SplitString(currentLine[2], '/');
//		std::vector<std::string> vertex3 = SplitString(currentLine[3], '/');
//		processVertex(vertex1, vertices, indices);
//		processVertex(vertex2, vertices, indices);
//		processVertex(vertex3, vertices, indices);
//
//		getline(file, line);
//	}
//	removeUnusedVertices(vertices);
//	std::vector<float> verticesVectors;
//	std::vector<float> texturesVectors;
//	std::vector<float> normalsVectors;
//	convertDataToVectors(vertices, textures, normals, verticesVectors, texturesVectors, normalsVectors);
//	for (Vertex *vertex : vertices)
//		delete vertex;
//	return loader.LoadToVAO(verticesVectors, texturesVectors, normalsVectors, indices);
//}
//
//RawModel OBJLoader::loadOBJModelPointCloud(const std::string & filePath, Loader & loader)
//{
//	std::ifstream file(filePath);
//	std::vector<Vertex*> vertices;
//	std::vector<glm::vec2> textures;
//	std::vector<glm::vec3> normals;
//	std::vector<int> indices;
//
//
//	std::string line;
//	if (!file.is_open())
//	{
//		std::cout << "file: " << filePath << "could not be opened!" << std::endl;
//		return RawModel{ 0,0 };
//	}
//
//	while (file.good())
//	{
//		const char* lineCStr = line.c_str();
//
//		getline(file, line);
//		if (lineCStr[0] == 'v')
//		{
//			if (lineCStr[1] == 't')
//			{
//				std::vector<std::string> currentLine = SplitString(line, ' ');
//				glm::vec2 newTexture(strtof((currentLine[1]).c_str(), 0), strtof(currentLine[2].c_str(), 0));
//
//				textures.push_back(newTexture);
//			}
//			else if (lineCStr[1] == 'n')
//			{
//				std::vector<std::string> currentLine = SplitString(line, ' ');
//				glm::vec3 newNormal(strtof((currentLine[1]).c_str(), 0), strtof(currentLine[2].c_str(), 0), strtof(currentLine[3].c_str(), 0));
//
//				normals.push_back(newNormal);
//			}
//			else if (lineCStr[1] == ' ' || lineCStr[1] == '\t')
//			{
//				std::vector<std::string> currentLine = SplitString(line, ' ');
//				glm::vec3 vertex(strtof((currentLine[1]).c_str(), 0), strtof(currentLine[2].c_str(), 0), strtof(currentLine[3].c_str(), 0));
//
//				vertices.push_back(new Vertex((int)vertices.size(), vertex));
//			}
//		}
//		else if (line.substr(0, 2) == "f ")
//			break;
//	}
//	while ((!line.empty()) && (line.substr(0, 2) == "f "))
//	{
//		std::vector<std::string> currentLine = SplitString(line, ' ');
//		std::vector<std::string> vertex1 = SplitString(currentLine[1], '/');
//		std::vector<std::string> vertex2 = SplitString(currentLine[2], '/');
//		std::vector<std::string> vertex3 = SplitString(currentLine[3], '/');
//		processVertex(vertex1, vertices, indices);
//		processVertex(vertex2, vertices, indices);
//		processVertex(vertex3, vertices, indices);
//
//		getline(file, line);
//	}
//	removeUnusedVertices(vertices);
//	std::vector<float> verticesVectors;
//	std::vector<float> texturesVectors;
//	std::vector<float> normalsVectors;
//	convertDataToVectors(vertices, textures, normals, verticesVectors, texturesVectors, normalsVectors);
//	for (Vertex *vertex : vertices)
//		delete vertex;
//
//	texturesVectors.clear();
//	texturesVectors.reserve(verticesVectors.size());
//	for (int i = 0; i < verticesVectors.size() / 3; i++)
//	{
//		texturesVectors.emplace_back(0.0f);
//		texturesVectors.emplace_back(0.0f);
//		texturesVectors.emplace_back(1.0f);
//		std::cout << i << std::endl;
//	}
//	return loader.LoadPointCloudToVAO(verticesVectors, texturesVectors);
//}
//
//std::vector<std::string> OBJLoader::SplitString(const std::string & s, char delim)
//{
//	std::vector<std::string> elems;
//
//	const char* cstr = s.c_str();
//	unsigned int strLength = (unsigned int)s.length();
//	unsigned int start = 0;
//	unsigned int end = 0;
//
//	while (end <= strLength)
//	{
//		while (end <= strLength)
//		{
//			if (cstr[end] == delim)
//				break;
//			end++;
//		}
//		elems.push_back(s.substr(start, end - start));
//		start = end + 1;
//		end = start;
//	}
//
//	return elems;
//}
//
//void OBJLoader::processVertex(std::vector<std::string> &vertex, std::vector<Vertex*> &vertices, std::vector<int> &indices)
//{
//	int index = atoi(vertex[0].c_str()) - 1;
//
//	Vertex* currentVertex = vertices[index];
//	int textureIndex = atoi(vertex[1].c_str()) - 1;
//	int normalIndex = atoi(vertex[2].c_str()) - 1;
//
//	if (!currentVertex->IsSet())
//	{
//		currentVertex->TextureIndex = textureIndex;
//		currentVertex->NormalIndex = normalIndex;
//
//		indices.push_back(index);
//	}
//	else
//		dealWithAlreadyProcessedVertex(currentVertex, textureIndex, normalIndex, indices, vertices);
//}
//
//void OBJLoader::dealWithAlreadyProcessedVertex(Vertex * previousVertex, int newTextureIndex, int newNormalIndex, std::vector<int>& indices, std::vector<Vertex*>& vertices)
//{
//	if (previousVertex->HasSameTextureAndNormal(newTextureIndex, newNormalIndex))
//		indices.push_back(previousVertex->Index);
//	else
//	{
//
//		Vertex* anotherVertex = previousVertex->DuplicateVertex;
//		if (anotherVertex != NULL)
//			dealWithAlreadyProcessedVertex(anotherVertex, newTextureIndex, newNormalIndex, indices, vertices);
//		else
//		{
//			Vertex *duplicateVertex = new Vertex((int)vertices.size(), previousVertex->Position);
//			duplicateVertex->TextureIndex = newTextureIndex;
//			duplicateVertex->NormalIndex = newNormalIndex;
//			previousVertex->DuplicateVertex = duplicateVertex;
//			vertices.push_back(duplicateVertex);
//			indices.push_back(duplicateVertex->Index);
//		}
//
//	}
//}
//
//void OBJLoader::removeUnusedVertices(std::vector<Vertex*> & vertices)
//{
//	for (Vertex * vertex: vertices)
//	{
//		if (!vertex->IsSet())
//		{
//			vertex->TextureIndex = 0;
//			vertex->NormalIndex = 0;
//		}
//	}
//}
//
//void OBJLoader::convertDataToVectors(std::vector<Vertex*>& vertices, std::vector<glm::vec2>& textures, std::vector<glm::vec3>& normals, std::vector<float>& verticesVector, std::vector<float>& texturesVector, std::vector<float>& normalsVector)
//{
//	for (Vertex * vertex : vertices)
//	{
//		glm::vec3 position = vertex->Position;
//		if (textures.size())
//		{
//			glm::vec2 textureCoord = textures[vertex->TextureIndex];
//			texturesVector.push_back(textureCoord.x);
//			texturesVector.push_back(1 - textureCoord.y);
//		}
//		
//		glm::vec3 normalVector = normals[vertex->NormalIndex];
//		verticesVector.push_back(position.x);
//		verticesVector.push_back(position.y);
//		verticesVector.push_back(position.z);
//		
//		normalsVector.push_back(normalVector.x);
//		normalsVector.push_back(normalVector.y);
//		normalsVector.push_back(normalVector.z);
//	}
//}
//
//void OBJLoader::ParseMaterialFile(const std::string & materialFile)
//{
//	std::ifstream file(materialFile);
//	std::string line;
//	if (!file.is_open())
//	{
//		std::cout << "file: " << materialFile << "could not be opened!" << std::endl;
//	}
//	while (file.good())
//	{
//		const char* lineCStr = line.c_str();
//		getline(file, line);
//		std::cout << line << std::endl;
//	}
//}
