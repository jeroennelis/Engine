#include "enpch.h"

#include "XYZLoader.h"

#include "RawModel.h"

namespace Engine{


	XYZLoader::XYZLoader()
	{
	}


	XYZLoader::~XYZLoader()
	{
	}

	RawModel XYZLoader::ConvertToRawModel(const std::vector<float>& verticesVector, const std::vector<float>& colorsVector)
	{
		std::vector<float> data;

		for (int i = 0; i < verticesVector.size() / 3; i++)
		{
			data.push_back(verticesVector[i * 3]);
			data.push_back(verticesVector[i * 3 + 1]);
			data.push_back(verticesVector[i * 3 + 1]);

			data.push_back(colorsVector[i * 3]);
			data.push_back(colorsVector[i * 3 + 1]);
			data.push_back(colorsVector[i * 3 + 1]);
		}

		std::shared_ptr<VertexArray> va;
		va.reset(VertexArray::Create());
		va->Bind();


		std::shared_ptr<VertexBuffer> vb;
		vb.reset(VertexBuffer::Create(data.data(), (int)verticesVector.size() / 3 * 6 * sizeof(float)));

		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float3, "a_Colors"},
		};
		vb->SetLayout(layout);

		va->AddVertexBuffer(vb);


		va->UnBind();
		vb->UnBind();

		va->SetCount(verticesVector.size() / 3);

		return RawModel{ va };
	}

	RawModel XYZLoader::ConvertToRawModel(const std::vector<float>& data)
	{
		std::shared_ptr<VertexArray> va;
		va.reset(VertexArray::Create());
		va->Bind();

		std::shared_ptr<VertexBuffer> vb;
		vb.reset(VertexBuffer::Create(data.data(), (int)data.size() * sizeof(float)));

		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float3, "a_Colors"},
		};

		vb->SetLayout(layout);

		va->AddVertexBuffer(vb);

		va->UnBind();
		vb->UnBind();

		va->SetCount(data.size() / 6);

		return RawModel{ va };
	}

	std::vector<RawModel> XYZLoader::LoadXYZModel(const std::string& filePath)
	{
		std::vector<RawModel> models;
		std::vector<float> vertices(10000000);
		std::vector<float> colours(10000000);
		std::vector<float> data(10000000);

		FILE* file;
		fopen_s(&file, filePath.c_str(), "r");
		if (file == NULL) {
			std::cout << "file: " << filePath << "could not be opened!" << std::endl;
			return models;
		}

		float x, y, z;
		int r, g, b;
		int segment = 0;
		int i = 0;
		do {
			int nItemsRead = fscanf_s(file, "%f %f %f %d %d %d\n", &x, &y, &z, &r, &g, &b);

			if (6 != nItemsRead)
				break;

			data.push_back(x);
			data.push_back(y);
			data.push_back(z);
			data.push_back((float)r / 255);
			data.push_back((float)g / 255);
			data.push_back((float)b / 255);
			//std::cout << x << "\t" << y << "\t" << z << "\t" << r << "\t" << g << "\t" << b << "\t" << std::endl;

			i++;
			if ((i % 1048576 == 0) || (segment == 0))
			{
				segment++;
				std::cout << "new segment" << std::endl;
				i = 0;
				//models.push_back( ConvertToRawModel(vertices, colours));
				models.push_back(ConvertToRawModel(data));
				vertices.clear();
				colours.clear();
				data.clear();
			}
		} while (1);




		return models;
	}

	std::vector<std::string> XYZLoader::SplitString(const std::string & s, char delim)
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

	
}