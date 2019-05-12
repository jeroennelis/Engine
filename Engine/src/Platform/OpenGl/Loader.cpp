#include "enpch.h"

#include "Loader.h"

namespace Engine {

	Loader* Loader::s_Instance = nullptr;

	Loader::Loader()
	{
		LoadShaders();
		LoadModels();
		LoadMaterials();
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

	Material * Loader::DraggedMaterial()
	{
		return m_DraggedMaterial; 
	}

	void Loader::SetDraggedMaterial(Material * material)
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
		for (Material* mat : m_Materials)
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
	}

	void Loader::LoadMaterials()
	{
		//TEST
		Material* mat1 = new Material(GetShader("diffuse"), "Red");
		for (MaterialProperty* prop : mat1->MaterialProperties())
		{
			if (prop->Name() == "u_Cd")
			{
				glm::vec4 data(1.0f, 0.032f, 0.032f, 1.0f);
				prop->SetData(&data);
			}
			if (prop->Name() == "u_Kd")
			{
				float data = 0.47f;
				prop->SetData(&data);
			}
			if (prop->Name() == "u_Ka")
			{
				float data = 0.36f;
				prop->SetData(&data);
			}
			if (prop->Name() == "u_Ks")
			{
				float data = 0.06f;
				prop->SetData(&data);
			}
			if (prop->Name() == "u_epsilon")
			{
				float data = 0.66f;
				prop->SetData(&data);
			}
		}

		Material* mat2 = new Material(GetShader("diffuse"),"Green");
		for (MaterialProperty* prop : mat2->MaterialProperties())
		{
			if (prop->Name() == "u_Cd")
			{
				glm::vec4 data(0.032f, 1.0f, 0.032f, 1.0f);
				prop->SetData(&data);
			}
			if (prop->Name() == "u_Kd")
			{
				float data = 0.47f;
				prop->SetData(&data);
			}
			if (prop->Name() == "u_Ka")
			{
				float data = 0.36f;
				prop->SetData(&data);
			}
			if (prop->Name() == "u_Ks")
			{
				float data = 0.06f;
				prop->SetData(&data);
			}
			if (prop->Name() == "u_epsilon")
			{
				float data = 0.66f;
				prop->SetData(&data);
			}
		}

		Material* mat3 = new Material(GetShader("diffuse"), "Blue");
		for (MaterialProperty* prop : mat3->MaterialProperties())
		{
			if (prop->Name() == "u_Cd")
			{
				glm::vec4 data(0.032f, 0.032f, 1.0f, 1.0f);
				prop->SetData(&data);
			}
			if (prop->Name() == "u_Kd")
			{
				float data = 0.47f;
				prop->SetData(&data);
			}
			if (prop->Name() == "u_Ka")
			{
				float data = 0.36f;
				prop->SetData(&data);
			}
			if (prop->Name() == "u_Ks")
			{
				float data = 0.06f;
				prop->SetData(&data);
			}
			if (prop->Name() == "u_epsilon")
			{
				float data = 0.66f;
				prop->SetData(&data);
			}
		}

		Material* mat4 = new Material(GetShader("diffuse"), "Black");
		for (MaterialProperty* prop : mat4->MaterialProperties())
		{
			if (prop->Name() == "u_Cd")
			{
				glm::vec4 data(0.032f, 0.032f, 0.032f, 1.0f);
				prop->SetData(&data);
			}
			if (prop->Name() == "u_Kd")
			{
				float data = 0.47f;
				prop->SetData(&data);
			}
			if (prop->Name() == "u_Ka")
			{
				float data = 0.36f;
				prop->SetData(&data);
			}
			if (prop->Name() == "u_Ks")
			{
				float data = 0.06f;
				prop->SetData(&data);
			}
			if (prop->Name() == "u_epsilon")
			{
				float data = 0.66f;
				prop->SetData(&data);
			}
		}
		
		Material* mat5 = new Material(GetShader("diffuse"), "white");
		for (MaterialProperty* prop : mat5->MaterialProperties())
		{
			if (prop->Name() == "u_Cd")
			{
				glm::vec4 data(1.0f, 1.0f, 1.0f, 1.0f);
				prop->SetData(&data);
			}
			if (prop->Name() == "u_Kd")
			{
				float data = 0.47f;
				prop->SetData(&data);
			}
			if (prop->Name() == "u_Ka")
			{
				float data = 0.36f;
				prop->SetData(&data);
			}
			if (prop->Name() == "u_Ks")
			{
				float data = 0.06f;
				prop->SetData(&data);
			}
			if (prop->Name() == "u_epsilon")
			{
				float data = 0.66f;
				prop->SetData(&data);
			}
		}

		m_Materials.push_back(mat1);
		m_Materials.push_back(mat2);
		m_Materials.push_back(mat3);
		m_Materials.push_back(mat4);
		m_Materials.push_back(mat5);
	}
}


