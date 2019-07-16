#include "enpch.h"

#include "MaterialProperty.h"
#include "imgui.h"

namespace Engine {
	MaterialProperty::MaterialProperty(const std::string & name)
		:m_Name(name)
	{
	}

	MaterialProperty::~MaterialProperty()
	{
	}

	//-------------int Property---------------------------------

	IntProperty::IntProperty(const std::string & name, int data)
		:MaterialProperty(name), m_Data(data)
	{
	}

	void IntProperty::SetProperty(Shader * shader)
	{
		shader->SetUniform1i(m_Name, m_Data);
	}

	void IntProperty::SetData(void *)
	{
	}

	void IntProperty::RenderInspectorInfo()
	{
	}

	//------------- float Property---------------------------------

	FloatProperty::FloatProperty(const std::string & name, float data)
		:MaterialProperty(name), m_Data(data)
	{
	}

	void FloatProperty::SetProperty(Shader * shader)
	{
		shader->SetUniform(m_Name, m_Data);
	}

	void FloatProperty::SetData(void * data)
	{
		m_Data = *(float*)data;
	}

	void FloatProperty::RenderInspectorInfo()
	{
		ImGui::DragFloat(m_Name.c_str(), &m_Data, 0.01f, 0.0f, 1.0f);
	}

	//-------------Vec3 Property---------------------------------

	Vec3Property::Vec3Property(const std::string & name, const glm::vec3& data)
		:MaterialProperty(name), m_Data(data)
	{
	}

	void Vec3Property::SetProperty(Shader * shader)
	{
		shader->SetUniform(m_Name, m_Data);
	}

	void Vec3Property::RenderInspectorInfo()
	{
	}

	//-------------Vec4 Property---------------------------------

	Vec4Property::Vec4Property(const std::string & name, const glm::vec4& vec)
		:MaterialProperty(name), m_Data(vec)
	{
	}

	void Vec4Property::SetProperty(Shader * shader)
	{
		shader->SetUniform(m_Name, m_Data);
	}

	void Vec4Property::SetData(void *)
	{
	}

	void Vec4Property::RenderInspectorInfo()
	{
	}


	//-------------color Property---------------------------------

	ColorProperty::ColorProperty(const std::string & name, const glm::vec4&  vec)
		:MaterialProperty(name), m_Data(vec)
	{
	}

	void ColorProperty::SetProperty(Shader * shader)
	{
		shader->SetUniform(m_Name, m_Data);
	}

	void ColorProperty::SetData(void * data)
	{
		m_Data = *(glm::vec4*)data;
	}

	void ColorProperty::RenderInspectorInfo()
	{

		ImGui::ColorEdit4(m_Name.c_str(), &m_Data[0]);
	}

	//-------------Mat4 Property---------------------------------

	Mat4Property::Mat4Property(const std::string & name, const glm::mat4& data)
		:MaterialProperty(name), m_Data(data)
	{
	}

	void Mat4Property::SetProperty(Shader * shader)
	{
		shader->SetUniform(m_Name, m_Data);
	}

	void Mat4Property::SetData(void * data)
	{
	}

	void Mat4Property::RenderInspectorInfo()
	{
	}

}