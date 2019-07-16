#include "enpch.h"
#include "OBJLoader.h"
#include "Platform/RayTracer/Utilities/Constants.h"

namespace Engine {


	Vertex::Vertex(int index, glm::vec3 & position)
		:Index(index), Position(position)
	{
		Length = (float)position.length();
		TextureIndex = NO_INDEX;
		NormalIndex = NO_INDEX;
		DuplicateVertex = NULL; 
	}




	bool Vertex::IsSet()
	{
		return ((TextureIndex != NO_INDEX) && (NormalIndex != NO_INDEX));
	}

	bool Vertex::HasSameTextureAndNormal(int textureIndexOther, int normalIndexOther)
	{
		return textureIndexOther == TextureIndex && normalIndexOther == NormalIndex;
	}



	OBJLoader::OBJLoader()
	{
	}


	OBJLoader::~OBJLoader()
	{
	}

	RawModel OBJLoader::loadOBJModel(const std::string & objFile)
	{
		//ParseMaterialFile(materialFile);
		std::ifstream file(objFile);
		std::vector<Vertex*> vertices;
		std::vector<glm::vec2> textures;
		std::vector<glm::vec3> normals;
		std::vector<unsigned int> indices; 


		std::string line;
		if (!file.is_open())
		{
			std::cout << "file: " << objFile << "could not be opened!" << std::endl;
			return RawModel{ nullptr };
		}

		while (file.good())
		{
			const char* lineCStr = line.c_str();

			getline(file, line);
			if (lineCStr[0] == 'v')
			{
				if (lineCStr[1] == 't')
				{
					std::vector<std::string> currentLine = SplitString(line, ' ');
					glm::vec2 newTexture(strtof((currentLine[1]).c_str(), 0), strtof(currentLine[2].c_str(), 0));

					textures.push_back(newTexture);
				}
				else if (lineCStr[1] == 'n')
				{
					std::vector<std::string> currentLine = SplitString(line, ' ');
					glm::vec3 newNormal(strtof((currentLine[1]).c_str(), 0), strtof(currentLine[2].c_str(), 0), strtof(currentLine[3].c_str(), 0));

					normals.push_back(newNormal);
				}
				else if (lineCStr[1] == ' ' || lineCStr[1] == '\t')
				{
					std::vector<std::string> currentLine = SplitString(line, ' ');
					glm::vec3 vertex(strtof((currentLine[1]).c_str(), 0), strtof(currentLine[2].c_str(), 0), strtof(currentLine[3].c_str(), 0));

					vertices.push_back(new Vertex((int)vertices.size(), vertex));
				}
			}
			else if (line.substr(0, 2) == "f ")
				break;
		}
		while ((!line.empty()) && (line.substr(0, 2) == "f "))
		{
			std::vector<std::string> currentLine = SplitString(line, ' ');
			std::vector<std::string> vertex1 = SplitString(currentLine[1], '/');
			std::vector<std::string> vertex2 = SplitString(currentLine[2], '/');
			std::vector<std::string> vertex3 = SplitString(currentLine[3], '/');
			processVertex(vertex1, vertices, indices);
			processVertex(vertex2, vertices, indices);
			processVertex(vertex3, vertices, indices);

			getline(file, line);
		}
		removeUnusedVertices(vertices);
		std::vector<float> verticesVectors;
		std::vector<float> texturesVectors;
		std::vector<float> normalsVectors;
		BBox bBox = convertDataToVectors(vertices, textures, normals, verticesVectors, texturesVectors, normalsVectors);
		for (Vertex *vertex : vertices)
			delete vertex;
		RawModel rawmodel = ConvertVectorsToRawModel(verticesVectors, texturesVectors, normalsVectors, indices);
		rawmodel.va->Bind();
		rawmodel.va->GetIndexBuffer()->Bind();
		rawmodel.path = objFile;
		rawmodel.bBox = bBox;
		return rawmodel;
	}



	std::vector<std::string> OBJLoader::SplitString(const std::string & s, char delim)
	{
		std::vector<std::string> elems;

		const char* cstr = s.c_str();
		unsigned int strLength = (unsigned int)s.length();
		unsigned int start = 0;
		unsigned int end = 0;

		while (end <= strLength)
		{
			while (end <= strLength)
			{
				if (cstr[end] == delim)
					break;
				end++;
			}
			elems.push_back(s.substr(start, end - start));
			start = end + 1;
			end = start;
		}

		return elems;
	}

	void OBJLoader::processVertex(std::vector<std::string> &vertex, std::vector<Vertex*> &vertices, std::vector<unsigned int> &indices)
	{
		int index = atoi(vertex[0].c_str()) - 1;

		Vertex* currentVertex = vertices[index];
		int textureIndex = atoi(vertex[1].c_str()) - 1;
		int normalIndex = atoi(vertex[2].c_str()) - 1;

		if (!currentVertex->IsSet())
		{
			currentVertex->TextureIndex = textureIndex;
			currentVertex->NormalIndex = normalIndex;

			indices.push_back(index);
		}
		else
			dealWithAlreadyProcessedVertex(currentVertex, textureIndex, normalIndex, indices, vertices);
	}

	void OBJLoader::dealWithAlreadyProcessedVertex(Vertex * previousVertex, int newTextureIndex, int newNormalIndex, std::vector<unsigned int>& indices, std::vector<Vertex*>& vertices)
	{
		if (previousVertex->HasSameTextureAndNormal(newTextureIndex, newNormalIndex))
			indices.push_back(previousVertex->Index);
		else
		{

			Vertex* anotherVertex = previousVertex->DuplicateVertex;
			if (anotherVertex != NULL)
				dealWithAlreadyProcessedVertex(anotherVertex, newTextureIndex, newNormalIndex, indices, vertices);
			else
			{
				Vertex *duplicateVertex = new Vertex((int)vertices.size(), previousVertex->Position);
				duplicateVertex->TextureIndex = newTextureIndex;
				duplicateVertex->NormalIndex = newNormalIndex;
				previousVertex->DuplicateVertex = duplicateVertex;
				vertices.push_back(duplicateVertex);
				indices.push_back(duplicateVertex->Index);
			}

		}
	}

	void OBJLoader::removeUnusedVertices(std::vector<Vertex*> & vertices)
	{
		for (Vertex * vertex : vertices)
		{
			if (!vertex->IsSet())
			{
				vertex->TextureIndex = 0;
				vertex->NormalIndex = 0;
			}
		}
	}

	BBox OBJLoader::convertDataToVectors(std::vector<Vertex*>& vertices, std::vector<glm::vec2>& textures, std::vector<glm::vec3>& normals, std::vector<float>& verticesVector, std::vector<float>& texturesVector, std::vector<float>& normalsVector)
	{
		BBox boundingBox = BBox(kHugeValue, -kHugeValue, kHugeValue, -kHugeValue, kHugeValue, -kHugeValue);
		for (Vertex * vertex : vertices)
		{
			glm::vec3 position = vertex->Position;
			if (textures.size())
			{
				glm::vec2 textureCoord = textures[vertex->TextureIndex];
				texturesVector.push_back(textureCoord.x);
				texturesVector.push_back(1 - textureCoord.y);
			}

			glm::vec3 normalVector = normals[vertex->NormalIndex];
			verticesVector.push_back(position.x);
			verticesVector.push_back(position.y);
			verticesVector.push_back(position.z);

			normalsVector.push_back(normalVector.x);
			normalsVector.push_back(normalVector.y);
			normalsVector.push_back(normalVector.z);

			if (position.x < boundingBox.X0)
				boundingBox.X0 = position.x;
			if (position.y < boundingBox.Y0)
				boundingBox.Y0 = position.y; 
			if (position.z < boundingBox.Z0)
				boundingBox.Z0 = position.z;

			if (position.x > boundingBox.X1)
				boundingBox.X1 = position.x;
			if (position.y > boundingBox.Y1)
				boundingBox.Y1 = position.y;
			if (position.z > boundingBox.Z1)
				boundingBox.Z1 = position.z;
			
		}
		return boundingBox;
	}

	RawModel OBJLoader::ConvertVectorsToRawModel(std::vector<float>& verticesVector, std::vector<float>& texturesVector, std::vector<float>& normalsVector, std::vector<unsigned int>& indices)
	{
		std::vector<float> data;
		for (int i = 0; i < verticesVector.size()/3; i++)
		{
			data.push_back(verticesVector[long(i * 3)]);
			data.push_back(verticesVector[long(i * 3 + 1)]);
			data.push_back(verticesVector[long(i * 3 + 2)]);

			data.push_back(normalsVector[long(i * 3)]);
			data.push_back(normalsVector[long(i * 3 + 1)]);
			data.push_back(normalsVector[long(i * 3 + 2)]);

			data.push_back(texturesVector[long(i * 2)]);
			data.push_back(texturesVector[long(i * 2 + 1)]);

		}

		std::shared_ptr<VertexArray> va;
		va.reset(VertexArray::Create());
		va->Bind();


		std::shared_ptr<VertexBuffer> vb;
		vb.reset(VertexBuffer::Create(data.data(), (int)verticesVector.size() / 3 * 8 * sizeof(float)));
		
		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float3, "a_Normal"},
			{ShaderDataType::Float2, "a_TexCoords"} 
		};
		vb->SetLayout(layout);
		
		va->AddVertexBuffer(vb);

		std::shared_ptr<IndexBuffer> ib;
		ib.reset(IndexBuffer::Create(indices.data(), (int)indices.size()));
		va->SetIndexBuffer(ib);


		va->UnBind();
		vb->UnBind();
		ib->UnBind();
		return RawModel{ va };
	}

	void OBJLoader::ParseMaterialFile(const std::string & materialFile)
	{
		std::ifstream file(materialFile);
		std::string line;
		if (!file.is_open())
		{
			std::cout << "file: " << materialFile << "could not be opened!" << std::endl;
		}
		while (file.good())
		{
			const char* lineCStr = line.c_str();
			getline(file, line);
		}
	}
}
