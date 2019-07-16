#include "enpch.h"

#include "Shader.h"
#include <fstream>

#include "glm/gtc/type_ptr.hpp"

namespace Engine {

	Shader::Shader(const std::string & filepath)
		:m_FilePath(filepath), m_RendererID(0)
	{
		//"../Engine/res/shaders/basic.shader"
		 ShaderProgramSource source = ParseShader(filepath);
		 m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
	}

	Shader::~Shader()
	{
		GLCall(glDeleteProgram(m_RendererID));
	}

	ShaderProgramSource Shader::ParseShader(const std::string& filepath)
	{
		std::ifstream stream(filepath);

		enum class Status
		{
			NONE = -1,
			PROPERTIES = 0,
			SHADER = 1
		};

		enum class ShaderType
		{
			NONE = -1,
			VERTEX = 0,
			FRAGMENT = 1,
			GEOMETRY = 2
		};

		Status status = Status::NONE;
		ShaderType type = ShaderType::NONE;

		std::string line;
		std::stringstream ss[3];
		while (getline(stream, line))
		{
			if (line.find("#properties") != std::string::npos)
			{
				status = Status::PROPERTIES;
			}
			else if (line.find("#shader") != std::string::npos)
			{
				status = Status::SHADER;
				if (line.find("vertex") != std::string::npos)
					type = ShaderType::VERTEX;
				else if (line.find("fragment") != std::string::npos)
					type = ShaderType::FRAGMENT;
				else if (line.find("geometry") != std::string::npos)
					type = ShaderType::GEOMETRY;
			}
			else if (status == Status::PROPERTIES)
			{
				if (line.find("Color") != std::string::npos)
				{
					size_t begin = line.find("{");
					size_t end = line.find("}");
					std::string prop = line.substr(begin + 2, end - begin -3);
					m_Properties.insert({ prop, "Color" });
				}
				if (line.find("float") != std::string::npos)
				{

					size_t begin = line.find("{");
					size_t end = line.find("}");
					std::string prop = line.substr(begin + 2, end - begin - 3);
					m_Properties.insert({ prop, "float" });
				}
			}
			else if(status == Status::SHADER)
			{
				ss[(int)type] << line << '\n';
			}
		}
		return { ss[0].str(), ss[1].str() };
	}

	unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
	{
		unsigned int id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)alloca(length * sizeof(char));
			glGetShaderInfoLog(id, length, &length, message);
			EN_CORE_ERROR("Failed to compile {0} shader", (type == GL_VERTEX_SHADER) ? "vertex" : "fragment");
			std::cout << message << std::endl;
			glDeleteShader(id);
			return 0;
		}

		return id;
	}

	unsigned int Shader::CreateShader(const std::string&vertexShader, const std::string& fragmentShader)
	{
		unsigned int program = glCreateProgram();
		unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

		GLCall(glAttachShader(program, vs));
		GLCall(glAttachShader(program, fs));
		GLCall(glLinkProgram(program));
		GLCall(glValidateProgram(program));
		
		GLCall(glDeleteShader(vs));
		GLCall(glDeleteShader(fs));

		return program;
	}

	void Shader::Bind() const
	{
		GLCall(glUseProgram(m_RendererID));
	}

	void Shader::UnBind() const
	{
		GLCall(glUseProgram(0));
	}

	void Shader::SetUniform1i(const std::string & name, int value)
	{
		GLCall(glUniform1i(GetUniformLocation(name), value));
	}

	void Shader::SetUniform1f(const std::string & name, float value)
	{
		GLCall(glUniform1f(GetUniformLocation(name), value));
	}

	void Shader::SetUniform(const std::string & name, float value)
	{
		GLCall(glUniform1f(GetUniformLocation(name), value));
	}

	void Shader::SetUniform(const std::string & name, const glm::vec4& v)
	{
		glUniform4f(GetUniformLocation(name), v.x, v.y, v.z, v.w);
	}

	void Shader::SetUniform(const std::string & name, const glm::vec3& v)
	{
		glUniform3f(GetUniformLocation(name), v.x, v.y, v.z);
	}

	void Shader::SetUniform(const std::string & name, const glm::mat4& matrix)
	{
		(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix)));
	}

	int Shader::GetUniformLocation(const std::string & name)
	{
		if (m_LocationCache.find(name) != m_LocationCache.end())
			return m_LocationCache[name];

		GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
		if (location == -1)
			EN_CORE_WARN("uniform '{0}' doesn't exist!", name);

		m_LocationCache[name] = location;
		return location;
	}
}