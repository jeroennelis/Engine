#pragma once
#include "Shader.h"
#include "RawModel.h"
#include "OBJLoader.h"
#include "XYZLoader.h"
#include "Material.h"

namespace Engine {

	class Loader
	{
	public:
		
		~Loader();

		static void Create();
		static Loader* Get();

		inline const std::vector<Material*>& GetMaterials() const  { return m_Materials; };
		inline const std::unordered_map<std::string, RawModel*>& GetRawModels() const { return m_Models; }
		inline const std::vector<RawModel>& GetPointCloud() const { return m_PointCloud; }

		Material* DraggedMaterial();
		void SetDraggedMaterial(Material* material);

		inline Material* SelectedMaterial() { return m_SelectedMaterial; }
		inline void SetSelectedMaterial(Material* material) { m_SelectedMaterial = material; }

		inline RawModel* SelectedRawModel() { return m_SelectedRawModel; }
		inline void SetDraggedRawModel(RawModel* model) { m_SelectedRawModel = model; }

		Shader* GetShader(const std::string&);
		RawModel* GetModel(const std::string&);

		void RenderMaterialPreviews();



	private:
		Loader();
		void LoadShaders();
		void LoadModels();
		void LoadMaterials();

	private:
		static Loader* s_Instance;
	
		std::unordered_map<std::string, Shader*> m_Shaders;
		std::unordered_map<std::string, RawModel*> m_Models;
		std::vector<RawModel> m_PointCloud;

		const std::unordered_map<std::string, std::string> m_ShaderPaths =
		{
			{"basic",	"../Engine/res/shaders/basic.shader" },
			{"diffuse",	"../Engine/res/shaders/diffuse.shader" },
			{"texture",	"../Engine/res/shaders/texture.shader"},
			{"preview",	"../Engine/res/shaders/preview.shader"},
			{"terrain", "../Engine/res/shaders/terrain.shader"},
			{"pointcloud", "../Engine/res/shaders/pointcloud.shader" }
		};

		const std::unordered_map<std::string, std::string> m_ModelPaths =
		{
			{"cube",		"../Engine/res/models/cube.obj"},
			{"sphere",		"../Engine/res/models/sphere.obj"},
			{"dragon",		"../Engine/res/models/dragon.obj"},
			{"killhouse",	"../Engine/res/models/killhouse.obj"},
			{"target",		"../Engine/res/models/target.obj"}
		};

		const std::unordered_map<std::string, std::string> m_PointCloudPaths =
		{
			{"statie", "../Engine/res/models/oude statie.xyz"}
		};

		std::vector<Material*> m_Materials;
		Material * m_DraggedMaterial;
		Material * m_SelectedMaterial;
		RawModel * m_SelectedRawModel;
	};
}
