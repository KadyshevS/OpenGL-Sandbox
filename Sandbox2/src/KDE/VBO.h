#pragma once
#include <glad/glad.h>

namespace kde
{
	class VBO
	{
	public:
		GLuint id;

	public:
		VBO(GLfloat* verticies, GLsizeiptr size);
		~VBO() = default;

		void Bind();
		void Unbind();
		void Delete();
	};
}
