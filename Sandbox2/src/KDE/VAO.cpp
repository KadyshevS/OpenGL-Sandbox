#include "VAO.h"

namespace kde
{
	VAO::VAO()
	{
		glGenVertexArrays(1, &id);
	}

	void VAO::LinkVBO(VBO vbo, GLuint layout, GLint size)
	{
		vbo.Bind();
		glVertexAttribPointer(layout, size, GL_FLOAT, GL_FALSE, size * sizeof(float), (void*)0);
		glEnableVertexAttribArray(layout);
		vbo.Unbind();
	}
	void VAO::Bind()
	{
		glBindVertexArray(id);
	}
	void VAO::Unbind()
	{
		glBindVertexArray(0);
	}
	void VAO::Delete()
	{
		glDeleteVertexArrays(1, &id);
	}
}