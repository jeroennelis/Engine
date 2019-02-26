#pragma once
//#include <iostream>
//#include <string>
//#include <fstream>
//#include <vector>
//#include <GLM\glm.hpp>
//
//#define NO_INDEX -1
//
//struct Vertex
//{
//	glm::vec3 Position;
//	int TextureIndex;
//	int NormalIndex;
//	Vertex * DuplicateVertex;
//	int Index;
//	float Length;
//
//	Vertex(int index, glm::vec3 &position);
//
//
//	void AddTangent(glm::vec3 & tangent);
//	void AverageTangents();
//
//	bool IsSet();
//	bool HasSameTextureAndNormal(int textureIndexOther, int normalIndexOther);
//};
//
//
//class OBJLoader
//{
//public:
//	OBJLoader();
//	~OBJLoader();
//
//	static RawModel loadOBJModel(const std::string & objFile, Loader & loader);
//	static RawModel loadOBJModelPointCloud(const std::string & fileName, Loader &loader);
//	static void ParseMaterialFile(const std::string & materialFile);
//private:
//	static std::vector<std::string> SplitString(const std::string &s, char delim);
//	static void processVertex(std::vector<std::string> &vertex, std::vector<Vertex*> &vertices, std::vector<int> &indices);
//	static void dealWithAlreadyProcessedVertex(Vertex *previousVertex, int newTextureIndex, int newNormalIndex, std::vector<int> &indices, std::vector<Vertex*> &vertices);
//	static void removeUnusedVertices(std::vector<Vertex*> & vertices);
//	static void convertDataToVectors(std::vector<Vertex*> &vertices, std::vector<glm::vec2> &textures, std::vector<glm::vec3> &normals,
//		std::vector<float> &verticesVector, std::vector<float> &texturesVector, std::vector<float> &normalsVector);
//	
//};

