#include "VBO.h"

namespace kde
{
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