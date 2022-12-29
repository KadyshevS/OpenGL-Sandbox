#pragma once
#include <glad/glad.h>
#include <stb/stb_image.h>
#include <string>
#include "Shader.h"

namespace kde
{
	class Texture
	{
	private:
		int imgW, imgH, colNumCh;

	public:
		GLuint id;
		GLenum type;
		GLuint unit;

	public:
		Texture(const std::string& image, GLenum texType, GLuint slot, GLenum format);

		void texUnit(kde::Shader& shader, const char* uniform, GLuint unit);
		void Bind();
		void Unbind();
		void Delete();
	};
}