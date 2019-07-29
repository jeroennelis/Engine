#include "enpch.h"

#include "Terrain.h"
#include "stb_image.h"

namespace Engine {

	Terrain::Terrain(int gridX, int gridZ, const std::string& heightMap)
		:SIZE(800), VERTEX_COUNT(128), MAX_HEIGHT(20), MAX_PIXEL_COLOUR(255)
	{
		m_X = gridX * SIZE;
		m_Z = gridZ * SIZE;
		m_Model = GenerateTerrain(heightMap);
	}

	Terrain::~Terrain()
	{
	}

	RawModel Terrain::GenerateTerrain(const std::string& heightMap)
	{
		stbi_set_flip_vertically_on_load(0);
		unsigned char* localBuffer;
		int width, imageHeight, BPP;
		int VERTEX_COUNT = 0;
		if (localBuffer = stbi_load(heightMap.c_str(), &width, &imageHeight, &BPP, 1))
			VERTEX_COUNT = imageHeight;


		unsigned int bytesPerPixel = BPP;
		std::cout << bytesPerPixel << std::endl;


		const int count = VERTEX_COUNT * VERTEX_COUNT;
		std::vector<float> vertices(count * 3);
		std::vector<float> normals(count * 3);
		std::vector<float> textureCoords(count * 2);
		std::vector<unsigned int> indices(6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1));
		int vertexPointer = 0;

		m_Heights = std::vector<std::vector<float>>();

		std::vector<float> temp;
		for (int i = 0; i < VERTEX_COUNT; i++)
		{
			temp.clear();
			for (int j = 0; j < VERTEX_COUNT; j++)
			{
				vertices[vertexPointer * 3] = (float)j / ((float)VERTEX_COUNT - 1) * SIZE;
				float height = GetHeigt(j, i, localBuffer, imageHeight);
				vertices[vertexPointer * 3 + 1] = height;
				vertices[vertexPointer * 3 + 2] = (float)i / ((float)VERTEX_COUNT - 1) * SIZE;
				glm::vec3 normal = CalculateNormal(j, i, localBuffer, imageHeight);
				normals[vertexPointer * 3] = normal.x;
				normals[vertexPointer * 3 + 1] = normal.y;
				normals[vertexPointer * 3 + 2] = normal.z;
				textureCoords[vertexPointer * 2] = (float)j / ((float)VERTEX_COUNT - 1);
				textureCoords[vertexPointer * 2 + 1] = (float)i / ((float)VERTEX_COUNT - 1);
				vertexPointer++;
				temp.push_back(height);
			}
			m_Heights.push_back(temp);
		}
		int pointer = 0;
		for (int gz = 0; gz < VERTEX_COUNT - 1; gz++) {
			for (int gx = 0; gx < VERTEX_COUNT - 1; gx++) {
				int topLeft = (gz * VERTEX_COUNT) + gx;
				int topRight = topLeft + 1;
				int bottomLeft = ((gz + 1) * VERTEX_COUNT) + gx;
				int bottomRight = bottomLeft + 1;
				indices[pointer++] = topLeft;
				indices[pointer++] = bottomLeft;
				indices[pointer++] = topRight;
				indices[pointer++] = topRight;
				indices[pointer++] = bottomLeft;
				indices[pointer++] = bottomRight;
			}
		}

		std::shared_ptr<VertexArray> va;
		va.reset(VertexArray::Create());
		va->Bind();

		std::vector<float> data;

		for (int i = 0; i < vertices.size() / 3; i++)
		{
			data.push_back(vertices[long(i * 3)]);
			data.push_back(vertices[long(i * 3 + 1)]);
			data.push_back(vertices[long(i * 3 + 2)]);

			data.push_back(normals[long(i * 3)]);
			data.push_back(normals[long(i * 3 + 1)]);
			data.push_back(normals[long(i * 3 + 2)]);

			data.push_back(textureCoords[long(i * 2)]);
			data.push_back(textureCoords[long(i * 2 + 1)]);
		}

		std::shared_ptr<VertexBuffer> vb;
		vb.reset(VertexBuffer::Create(data.data(), (int)vertices.size() / 3 * 8 * sizeof(float)));

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

	float Terrain::GetHeigt(int x, int y, unsigned char* localBuffer, int h)
	{
		if (x < 0 || x >= h || y < 0 || y >= h)
		{
			return 0;
		}
		int offset = (x + y * (h));
		float heightValue = (float)localBuffer[offset];
		float height = heightValue;
		height -= MAX_PIXEL_COLOUR / 2.0f;
		height /= MAX_PIXEL_COLOUR / 2.0f;
		height *= MAX_HEIGHT;
		return height;
	}

	glm::vec3 Terrain::CalculateNormal(int x, int z, unsigned char* localBuffer, int height)
	{
		float heightL = GetHeigt(x - 1, z, localBuffer, height);
		float heightR = GetHeigt(x + 1, z, localBuffer, height);
		float heightD = GetHeigt(x, z - 1, localBuffer, height);
		float heightU = GetHeigt(x, z + 1, localBuffer, height);
		glm::vec3 normal(heightL - heightR, 2.0f, heightD - heightU);
		return glm::normalize(normal);
	}
}


