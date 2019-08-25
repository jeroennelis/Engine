#pragma once
#include "Renderer/OpenGLShader.h"
#include "RawModel.h"
#include "OBJLoader.h"
#include "XYZLoader.h"
#include "Platform/OpenGl/Materials/OpenGLMaterial.h"
#include "Platform/RayTracer/Utilities/Constants.h"
#include "Engine/Textures/ImageTexture.h"


namespace Engine {

	class Loader
	{
	public:
		
		~Loader();

		static void Create();
		static Loader* Get();

		inline const std::vector<OpenGLMaterial*>& GetMaterials() const  { return m_Materials; };
		inline const std::unordered_map<std::string, RawModel*>& GetRawModels() const { return m_Models; }
		inline const std::vector<RawModel>& GetPointCloud() const { return m_PointCloud; }
		inline const std::unordered_map<std::string, ImageTexture*>& GetTextures() { return m_Textures; }

		inline const RawModel& GetCone() const { return m_Cone; }

		OpenGLMaterial* DraggedMaterial();
		void SetDraggedMaterial(OpenGLMaterial* material);

		inline OpenGLMaterial* SelectedMaterial() { return m_SelectedMaterial; }
		inline void SetSelectedMaterial(OpenGLMaterial* material) { m_SelectedMaterial = material; }

		inline RawModel* SelectedRawModel() { return m_SelectedRawModel; }
		inline void SetDraggedRawModel(RawModel* model) { m_SelectedRawModel = model; }

		inline void SetDraggedTexture(ImageTexture* texture) { m_DraggedTexture = texture; }
		inline ImageTexture* DraggedTexture() { return m_DraggedTexture; }

		Shader* GetShader(const std::string&);
		RawModel* GetModel(const std::string&);

		void RenderMaterialPreviews();



	private:
		Loader();
		void LoadShaders();
		void LoadModels();
		void LoadMaterials();
		void LoadTextures();

		void LoadCone();

	private:
		static Loader* s_Instance;
	
		std::unordered_map<std::string, Shader*> m_Shaders;
		std::unordered_map<std::string, RawModel*> m_Models;
		std::unordered_map<std::string, ImageTexture*> m_Textures;
		std::vector<RawModel> m_PointCloud;

		RawModel m_Cone;

		const std::string m_TexturesPath = "../Engine/res/textures";

		const std::unordered_map<std::string, std::string> m_ShaderPaths =
		{
			{"basic",		"../Engine/res/shaders/basic.shader" },
			{"phong",		"../Engine/res/shaders/phong.shader" },
			{"texture",		"../Engine/res/shaders/texture.shader"},
			{"preview",		"../Engine/res/shaders/preview.shader"},
			{"terrain",		"../Engine/res/shaders/terrain.shader"},
			{"pointcloud",	"../Engine/res/shaders/pointcloud.shader" },
			{"cone",		"../Engine/res/shaders/cone.shader" },
			{"outline",		"../Engine/res/shaders/outline.shader" },
			{"icon",		"../Engine/res/shaders/icon.shader" },
			{"skybox",		"../Engine/res/shaders/skybox.shader"}
		};

		const std::unordered_map<std::string, std::string> m_ModelPaths =
		{
			{"cube",		"../Engine/res/models/cube.obj"},
			{"sphere",		"../Engine/res/models/sphere.obj"},
			{"dragon",		"../Engine/res/models/dragon.obj"},
			{"teapot",		"../Engine/res/models/teapot.obj"},
			{"killhouse",	"../Engine/res/models/killhouse.obj"},
			{"target",		"../Engine/res/models/target.obj"},
			{"stall",		"../Engine/res/models/stall.obj"},
			{"huis",		"../Engine/res/models/huis.obj"}
		};

		const std::unordered_map<std::string, std::string> m_PointCloudPaths =
		{
			{"pelt", "../Engine/res/models/pelt.xyz"}
		};

		std::vector<OpenGLMaterial*> m_Materials;
		OpenGLMaterial* m_DraggedMaterial;
		OpenGLMaterial* m_SelectedMaterial;
		RawModel * m_SelectedRawModel;
		ImageTexture* m_DraggedTexture;
	};
}
