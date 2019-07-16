#pragma once

#include "Shader.h"

namespace Engine {

	class Shader;

	class MaterialProperty
	{
	public:
		MaterialProperty(const std::string& name);
		virtual ~MaterialProperty();

		virtual void SetProperty(Shader* shader) = 0;
		virtual void SetData(void*) = 0;
		virtual void RenderInspectorInfo() = 0;

		inline const std::string& Name()const { return m_Name; }

	protected:
		std::string m_Name;
	};

	//-------------	int Property	---------------------------------

	class IntProperty : public MaterialProperty
	{
	public:
		IntProperty(const std::string& name, int data);
		virtual void SetProperty(Shader * shader) override;
		virtual void SetData(void*)override;
		virtual void RenderInspectorInfo() override;

	private:
		int m_Data;
	};

	//------------- float Property---------------------------------

	class FloatProperty : public MaterialProperty
	{
	public:
		FloatProperty(const std::string& name, float data);

		virtual void SetProperty(Shader * shader) override;
		virtual void SetData(void*)override;
		virtual void RenderInspectorInfo() override;

	private:
		float m_Data;
	};

	//-------------	Vec3 Property	---------------------------------

	class Vec3Property : public MaterialProperty
	{
	public:
		Vec3Property(const std::string& name, const glm::vec3& data);

		virtual void SetProperty(Shader * shader) override;
		virtual void RenderInspectorInfo() override;

	private:
		glm::vec3 m_Data;
	};

	//-------------Vec4 Property---------------------------------

	class Vec4Property : public MaterialProperty
	{
	public:
		Vec4Property(const std::string& name, const glm::vec4& data);

		virtual void SetProperty(Shader * shader) override;
		virtual void SetData(void*)override;
		virtual void RenderInspectorInfo() override;

	private:
		glm::vec4 m_Data;
	};

	//-------------Vec4 Property---------------------------------

	class ColorProperty : public MaterialProperty
	{
	public:
		ColorProperty(const std::string& name, const glm::vec4&  vec);

		virtual void SetProperty(Shader * shader) override;
		virtual void SetData(void*)override;
		virtual void RenderInspectorInfo() override;

	private:
		glm::vec4 m_Data;
	};
	
	//-------------Mat4 Property---------------------------------

	class Mat4Property : public MaterialProperty
	{
	public:
		Mat4Property(const std::string& name, const glm::mat4& data);

		virtual void SetProperty(Shader * shader) override;
		virtual void SetData(void* data)override;
		virtual void RenderInspectorInfo() override;

	private:
		glm::mat4 m_Data;
	};

}