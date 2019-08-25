#pragma once
#include  "Engine/GameObject.h" 
#include "Engine/Components/Camera.h"
#include "Engine/Physics/ParticleWorld.h"
#include "Engine/Physics/ParticleLinks.h"

#include "Platform/OpenGl/Materials/OpenGLMaterial.h"
#include "Engine/Events/MouseEvent.h"
#include "Engine/Components/Light.h"

#include "Platform/OpenGl/SkyboxRenderer.h"




namespace Engine {

	class OpenGLMaterial;

	struct RawModel;

	class Scene
	{
	public:

		Scene();
		Scene(const std::string& name);
		~Scene();

		inline static Scene* Current() { return m_Current; }
		inline static void SetCurrent(Scene* scene) { m_Current = scene; }

		inline static GameObject* SelectedGameObject() { return m_SelectedGameObject; }
		inline static void SetSelectedGameObject(GameObject* gameObject) { m_SelectedMaterial = nullptr; m_SelectedGameObject = gameObject; }

		inline static OpenGLMaterial* SelectedMaterial() { return m_SelectedMaterial; }
		inline static void SetSelectedMaterial(OpenGLMaterial* material) { m_SelectedGameObject = nullptr; m_SelectedMaterial = material; }

		inline const std::string& Name() const { return m_Name; }

		inline std::vector<std::shared_ptr<GameObject>>& GameObjects() { return m_GameObjects; }

		inline void RenderSkybox() { m_Skybox->Render(); }

		void AddGameObject(std::shared_ptr<GameObject> go);
		GameObject* AddRawModel(RawModel* model);

		void OnUpdate();

		static std::shared_ptr<GameObject> CreateCube(GameObject* parent = nullptr);
		static std::shared_ptr<GameObject> CreateSphere(GameObject* parent = nullptr);
		static std::shared_ptr<GameObject> CreateTarget(GameObject* parent = nullptr);

		void DeleteGameObject(const std::shared_ptr<GameObject>& object);
		static void AddCube(const glm::vec3& position = glm::vec3(0,0,0));
		static void AddSphere();

		static void AddPointCloud();

		static void AddCone();

		static unsigned int ObjectCount;

		inline static void SetGameCamera(Camera* cam) { m_GameCamera = cam; }
		inline static Camera* GetGameCamera() { return m_GameCamera; }
		inline static Camera* GetSceneCamera() { return m_SceneCamera; }

		inline std::vector<Light*> GetLights() { return m_Lights; }

		void OnEvent(Event& event);
		bool Scroll(MouseScrolledEvent event);


		void AddLight();

		void AddTerrain();

		inline void RunPhysics() { runPhysics = true; }

	private:
		static Scene* m_Current;
		static GameObject* m_SelectedGameObject;
		std::string m_Name;

		static Camera* m_GameCamera;
		static Camera* m_SceneCamera;
		std::vector<std::shared_ptr<GameObject>> m_GameObjects;

		SkyboxRenderer* m_Skybox;
		
		static OpenGLMaterial* m_SelectedMaterial;

		//temp

		physics::ParticleWorld particleWorld;

		std::vector<std::shared_ptr<GameObject>> particles;

		physics::ParticleGravity gravity;
		
		bool runPhysics;

		std::vector<Light*> m_Lights;
	};

}


