#include "enpch.h"

#include "Loader.h"
#include "Materials/OpenGLPhong.h"
#include "Engine/Textures/ConstantColor.h"

namespace Engine {

	Loader* Loader::s_Instance = nullptr;

	Loader::Loader()
	{
		LoadShaders();
		LoadMaterials();
		LoadCone();
		LoadModels();
	}

	Loader::~Loader()
	{
		for (const auto& s : m_Shaders)
			delete s.second;

		for (const auto& m : m_Models)
			delete m.second;
	}

	void Loader::Create()
	{
		s_Instance = new Loader();
	}

	Loader * Loader::Get()
	{
		return s_Instance;
	}

	OpenGLMaterial* Loader::DraggedMaterial()
	{
		return m_DraggedMaterial; 
	}

	void Loader::SetDraggedMaterial(OpenGLMaterial* material)
	{
		 m_DraggedMaterial = material; 
	}

	Shader * Loader::GetShader(const std::string& name)
	{
		const auto& shader = m_Shaders.find(name);
		if (shader == m_Shaders.end())
			return nullptr;
		return shader->second;
	}

	RawModel * Loader::GetModel(const std::string& name)
	{
		const auto& model = m_Models.find(name);
		if (model == m_Models.end())
			return nullptr;
		return model->second;
	}

	void Loader::RenderMaterialPreviews()
	{
		for (OpenGLMaterial* mat : m_Materials)
		{
			mat->RenderPreview();
		}
	}

	void Loader::LoadShaders()
	{
		for (const auto& s : m_ShaderPaths)
			m_Shaders.insert({ s.first, new Shader(s.second)});
	}

	void Loader::LoadModels()
	{
		for (const auto& m : m_ModelPaths)
			m_Models.insert({ m.first, new RawModel(OBJLoader::loadOBJModel(m.second)) });
		/*for (const auto& m : m_PointCloudPaths)
		{
			m_PointCloud = XYZLoader::LoadXYZModel(m.second);
		}*/


	}

	void Loader::LoadMaterials()
	{
		//TEST
		OpenGLPhong* mat1 = new OpenGLPhong(GetShader("phong"), "Red");
		ConstantColor* texture1 = new ConstantColor();
		texture1->SetColor({ 0.968f, 0.032f, 0.032f });
		mat1->SetCd(texture1);
		mat1->SetKd(0.47f);
		mat1->SetKa(0.1);
		mat1->SetKs(0.06f);
		mat1->SetExp(100);
		
		OpenGLPhong* mat2 = new OpenGLPhong(GetShader("phong"), "Green");
		ConstantColor* texture2 = new ConstantColor();
		texture2->SetColor({ 0.032f, 0.968f, 0.032f });
		mat2->SetCd(texture2);
		mat2->SetKd(0.47f);
		mat2->SetKa(0.1);
		mat2->SetKs(0.06f);
		mat2->SetExp(100);

		OpenGLPhong* mat3 = new OpenGLPhong(GetShader("phong"), "Blue");
		ConstantColor* texture3 = new ConstantColor();
		texture3->SetColor({ 0.032f, 0.032f, 0.968f });
		mat3->SetCd(texture3);
		mat3->SetKd(0.47f);
		mat3->SetKa(0.1);
		mat3->SetKs(0.06f);
		mat3->SetExp(100);

		OpenGLPhong* mat4 = new OpenGLPhong(GetShader("phong"), "Black");
		ConstantColor* texture4 = new ConstantColor();
		texture4->SetColor({ 0.032f, 0.032f, 0.032f });
		mat4->SetCd(texture4);
		mat4->SetKd(0.47f);
		mat4->SetKa(0.1);
		mat4->SetKs(0.06f);
		mat4->SetExp(100);

		OpenGLPhong* mat5 = new OpenGLPhong(GetShader("phong"), "White");
		ConstantColor* texture5 = new ConstantColor();
		texture5->SetColor({ 0.968f, 0.968f, 0.968f });
		mat5->SetCd(texture5);
		mat5->SetKd(0.47f);
		mat5->SetKa(0.1);
		mat5->SetKs(0.06f);
		mat5->SetExp(100);

		OpenGLPhong* mat6 = new OpenGLPhong(GetShader("outline"), "temp");
		ConstantColor* texture6 = new ConstantColor();
		texture6->SetColor({ 0.90, 0.1, 0.1 });
		mat6->SetCd(texture6);
		mat6->SetKd(0.5);
		mat6->SetKa(0.1);
		mat6->SetKs(0.05);
		mat6->SetExp(100);
		
		m_Materials.push_back(mat1);
		m_Materials.push_back(mat2);
		m_Materials.push_back(mat3);
		m_Materials.push_back(mat4);
		m_Materials.push_back(mat5);
		m_Materials.push_back(mat6);

	}

	void Loader::LoadCone()
	{
		int nrOfSubDivisions = 100;
		float angle = 0;

		float degreeOfUncertainty = 5.0f;

		float distance1 = 10;
		float distance2 = 20;
		float distance3 = 40;


		float radius1 = 0.009;
		float radius2;
		float radius3;
		float radius4 = distance3 * sin(glm::radians(degreeOfUncertainty));
		

		

		radius2 = radius1 + (radius4 - radius1) / distance3 * distance1;
		radius3 = radius1 + (radius4 - radius1) / distance3 * distance2;

		float deltaTheta = TWO_PI/ nrOfSubDivisions;

		glm::vec3 origin(0.0, 0.0, 0.0);


		std::vector<float> pos;
		std::vector<int> color;
		
		//distance 0
		for (int i = 0; i < nrOfSubDivisions; i++)
		{
			float x = radius1 * cos(angle);
			float y = radius1 * sin(angle);
			float z = 0.0;

			angle += deltaTheta;
			
			pos.push_back(x);
			pos.push_back(y);
			pos.push_back(z);

			color.push_back(0);			
		}


		//distance 1

		angle = 0;

		for (int i = 0; i < nrOfSubDivisions; i++)
		{
			float x = radius2 * cos(angle);
			float y = radius2 * sin(angle);
			float z = sqrt(pow(distance1, 2) - pow(radius2, 2));

			angle += deltaTheta;

			pos.push_back(x);
			pos.push_back(y);
			pos.push_back(z);

			color.push_back(0);

		}
		
		//distance1 2
		angle = 0;

		for (int i = 0; i < nrOfSubDivisions; i++)
		{
			float x = radius2 * cos(angle);
			float y = radius2 * sin(angle);
			float z = sqrt(pow(distance1, 2) - pow(radius2, 2));

			angle += deltaTheta;

			pos.push_back(x);
			pos.push_back(y);
			pos.push_back(z);

			color.push_back(1);

		}

		//distance 2
			angle = 0;

			for (int i = 0; i < nrOfSubDivisions; i++)
			{
				float x = radius3 * cos(angle);
				float y = radius3 * sin(angle);
				float z = sqrt(pow(distance2, 2) - pow(radius3, 2));

				angle += deltaTheta;

				pos.push_back(x);
				pos.push_back(y);
				pos.push_back(z);

				color.push_back(1);

			}
	
			//distance2 2

		angle = 0;

		for (int i = 0; i < nrOfSubDivisions; i++)
		{
			float x = radius3 * cos(angle);
			float y = radius3 * sin(angle);
			float z = sqrt(pow(distance2, 2) - pow(radius3, 2));


			angle += deltaTheta;

			pos.push_back(x);
			pos.push_back(y);
			pos.push_back(z);

			color.push_back(0);

		}

		angle = 0;

		for (int i = 0; i < nrOfSubDivisions; i++)
		{
			float x = radius4 * cos(angle);
			float y = radius4 * sin(angle);
			float z = sqrt(pow(distance3, 2) - pow(radius4, 2));


			angle += deltaTheta;

			pos.push_back(x);
			pos.push_back(y);
			pos.push_back(z);

			color.push_back(0);

		}

		std::vector<unsigned int> indices;

		for (int i = 0; i < 5 * nrOfSubDivisions; i++)
		{
			indices.push_back(i);
			indices.push_back(nrOfSubDivisions + i);
			indices.push_back(nrOfSubDivisions + i -1);

			indices.push_back(i + 1);
			indices.push_back(nrOfSubDivisions + i);
			indices.push_back(i);
		}

		std::shared_ptr<VertexArray> va;
		va.reset(VertexArray::Create());
		va->Bind();

		std::shared_ptr<VertexBuffer> vb;
		vb.reset(VertexBuffer::Create(pos.data(), (int)pos.size() * sizeof(float)));

		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"}
		};
		vb->SetLayout(layout);

		va->AddVertexBuffer(vb);

		std::shared_ptr<VertexBuffer> vbc;
		vbc.reset(VertexBuffer::Create(color.data(), (int)color.size() * sizeof(int)));

		BufferLayout layoutc = {
			{ShaderDataType::Int, "a_color"}
		};
		vbc->SetLayout(layoutc);

		va->AddVertexBuffer(vbc);

		std::shared_ptr<IndexBuffer> ib;
		ib.reset(IndexBuffer::Create(indices.data(), (int)indices.size()));
		va->SetIndexBuffer(ib);

		va->UnBind();
		vb->UnBind();
		vbc->UnBind();

		va->SetCount(pos.size() / 3);

		m_Cone = RawModel{ va };
	}
}


