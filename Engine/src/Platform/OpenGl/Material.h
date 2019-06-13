#pragma once
#include "glm/glm.hpp"
#include "Shader.h"
#include "MaterialProperty.h"
#include "Platform/OpenGl/FrameBuffer.h"


namespace Engine {

	class Material
	{
	public:
		Material(Shader* shader, const std::string& name);
		~Material();

		Shader* m_Shader;

		inline const std::vector<MaterialProperty*>& MaterialProperties()const { return m_Properties; }

		void AddProperty(MaterialProperty*);
		
		void Bind();

		virtual void RenderInspectorInfo();
		const void RenderProjectInfo()const ;

		void RenderPreview();

	private:
		std::vector<MaterialProperty*> m_Properties;
		std::string m_Name;
		FrameBuffer* m_Preview;

	private:
		void InitProperties();
	};
}