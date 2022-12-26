#pragma once
#include <glad/glad.h>

namespace kde
{
	class VBO
	{
	public:
		GLuint id;

	public:
		template<typename T>
		VBO(T* verticies, GLsizeiptr size)
		{
			glGenBuffers(1, &id);
			glBindBuffer(GL_ARRAY_BUFFER, id);
			glBufferData(GL_ARRAY_BUFFER, size, verticies, GL_STATIC_DRAW);
		}
		~VBO() = default;

		void Bind();
		void Unbind();
		void Delete();
	};
}
