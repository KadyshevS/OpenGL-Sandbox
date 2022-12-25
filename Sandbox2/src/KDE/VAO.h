#pragma once
#include <glad/glad.h>
#include "VBO.h"

namespace kde
{
	class VAO
	{
	public:
		GLuint id;

	public:
		VAO();
		~VAO() = default;

		void LinkVBO(VBO vbo, GLuint layout, GLint size);
		void Bind();
		void Unbind();
		void Delete();
	};
}