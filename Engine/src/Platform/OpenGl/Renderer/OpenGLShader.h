#pragma once

#include "../GL.h"
#include "glm/glm.hpp"
#include "Engine/Renderer/Shader.h"
#include "Engine/Components/Light.h"

namespace Engine {

	class OpenGLShader : public Shader
	{
	private:
		std::string m_FilePath;
		unsigned int m_RendererID;
		std::unordered_map<std::string, int> m_LocationCache;
		std::unordered_map<std::string, std::string> m_Properties;

	public:
		OpenGLShader(const std::string& filepath);
		~OpenGLShader();

		void Bind() const override;
		void Unbind() const override;

		const std::unordered_map<std::string, std::string>& GetProperties() { return m_Properties; }

		// Set Uniforms
		void SetUniform1i(const std::string& name, int value);
		void SetUniform1f(const std::string& name, float value);

		void SetUniform(const std::string& name, float value);
		void SetUniform(const std::string& name, const glm::vec4& v);
		void SetUniform(const std::string& name, const glm::vec3& v);
		void SetUniform(const std::string& name, const glm::mat4& matrix);
		void SetLights(const std::string& name, const std::vector<Light*>& lights);
	
	private:
		std::tuple<std::string, std::string> ParseShader(const std::string& filepath);
		unsigned int CompileShader(unsigned int type, const std::string& source);
		unsigned int CreateShader(const std::string&vertexShader, const std::string& fragmentShader);
		int GetUniformLocation(const std::string& name);
	};
}