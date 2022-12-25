#pragma once
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <iostream>

namespace kde
{
	std::string GetFileSource(std::string filePath);

	class Shader
	{
	public:
		GLuint mProgram;

	public:
		Shader(const std::string& vertexShader, const std::string& fragmentShader);
		Shader(const Shader&) = delete;
		~Shader() = default;

		void Use();
		void Delete();
	};
}