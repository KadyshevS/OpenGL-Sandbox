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

		void LinkAttrib(VBO vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
		void Bind();
		void Unbind();
		void Delete();
	};
}