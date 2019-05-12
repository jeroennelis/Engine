#pragma once

#include "GL.h"
#include "glm/glm.hpp"

namespace Engine {

	struct ShaderProgramSource
	{
		std::string VertexSource;
		std::string FragmentSource;
	};

	class Shader
	{
	private:
		std::string m_FilePath;
		unsigned int m_RendererID;
		std::unordered_map<std::string, int> m_LocationCache;
		std::unordered_map<std::string, std::string> m_Properties;

	public:
		Shader(const std::string& filepath);
		~Shader();

		void Bind() const;
		void UnBind() const;

		const std::unordered_map<std::string, std::string>& GetProperties() { return m_Properties; }

		// Set Uniforms
		void SetUniform1i(const std::string& name, int value);
		void SetUniform1f(const std::string& name, float value);

		void SetUniform(const std::string& name, float value);
		void SetUniform(const std::string& name, glm::vec4* v);
		void SetUniform(const std::string& name, glm::vec3* v);
		void SetUniform(const std::string& name, glm::mat4* matrix);
	
	private:
		ShaderProgramSource ParseShader(const std::string& filepath);
		unsigned int CompileShader(unsigned int type, const std::string& source);
		unsigned int CreateShader(const std::string&vertexShader, const std::string& fragmentShader);
		int GetUniformLocation(const std::string& name);
	};
}