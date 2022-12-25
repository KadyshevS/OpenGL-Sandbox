#pragma once
#include <glad/glad.h>

namespace kde
{
	class EBO
	{
	public:
		GLuint id;

	public:
		EBO(GLuint* indicies, GLsizeiptr size);
		~EBO() = default;

		void Bind();
		void Unbind();
		void Delete();
	};
}
