#pragma once
#include <glad/glad.h>
#include <vector>

namespace kde
{
	class EBO
	{
	public:
		GLuint id;

	public:
		EBO(std::vector<GLuint>& indices);
		~EBO() = default;

		void Bind();
		void Unbind();
		void Delete();
	};
}
