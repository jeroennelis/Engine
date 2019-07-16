#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <GLM\glm.hpp>

#include "RawModel.h"
#include "Engine/Renderer/VertexArray.h"

#define NO_INDEX -1

namespace Engine {

	struct Vertex
	{
		glm::vec3 Position;
		int TextureIndex;
		int NormalIndex;
		Vertex * DuplicateVertex;
		int Index;
		float Length;

		Vertex(int index, glm::vec3 &position);

		bool IsSet();
		bool HasSameTextureAndNormal(int textureIndexOther, int normalIndexOther);
	};


	class OBJLoader
	{
	public:
		OBJLoader();
		~OBJLoader();

		static RawModel loadOBJModel(const std::string & objFile);
		static void ParseMaterialFile(const std::string & materialFile);
	private:
		static std::vector<std::string> SplitString(const std::string &s, char delim);
		static void processVertex(std::vector<std::string> &vertex, std::vector<Vertex*> &vertices, std::vector<unsigned int> &indices);
		static void dealWithAlreadyProcessedVertex(Vertex *previousVertex, int newTextureIndex, int newNormalIndex, std::vector<unsigned int> &indices, std::vector<Vertex*> &vertices);
		static void removeUnusedVertices(std::vector<Vertex*> & vertices);
		static BBox convertDataToVectors(std::vector<Vertex*> &vertices, std::vector<glm::vec2> &textures, std::vector<glm::vec3> &normals,
			std::vector<float> &verticesVector, std::vector<float> &texturesVector, std::vector<float> &normalsVector);
		static RawModel ConvertVectorsToRawModel(std::vector<float> &verticesVector, std::vector<float> &texturesVector, std::vector<float> &normalsVector, std::vector<unsigned int>& indices);

	};
}

