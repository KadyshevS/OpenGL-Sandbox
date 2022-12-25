#include "VBO.h"

namespace kde
{
	VBO::VBO(GLfloat* verticies, GLsizeiptr size)
	{
		glGenBuffers(1, &id);
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferData(GL_ARRAY_BUFFER, size, verticies, GL_STATIC_DRAW);
	}

	void VBO::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, id);
	}
	void VBO::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void VBO::Delete()
	{
		glDeleteBuffers(1, &id);
	}
}