#pragma once

#include <string>
#include <GLCore.h>
#include <glad/glad.h>

namespace GLCore::Utils {

	class Shader
	{
	public:
		~Shader();

		GLuint GetRendererID() { return m_RendererID; }

		static Shader* FromGLSLTextFiles(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

		void Bind() const;
		void UnBind() const;

		// Set Uniforms
		void SetUniform4f(const std::string& name, float v0, float v1, float f2, float f3);
		void SetUniform1f(const std::string& name, float v0);
		void SetUniform1i(const std::string& name, int v0);
		void SetUniform1iv(const std::string& name, int v0[], int count);
		void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
	private:
		Shader() = default;

		void LoadFromGLSLTextFiles(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		GLuint CompileShader(GLenum type, const std::string& source);
		int GetUniformLocation(const std::string& name);
	private:
		GLuint m_RendererID;
		std::unordered_map<std::string, unsigned int> m_UniformLocationCache;
	};

}