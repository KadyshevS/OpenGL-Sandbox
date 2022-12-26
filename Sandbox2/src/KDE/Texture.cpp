#include "Texture.h"

namespace kde
{
	Texture::Texture(const std::string& image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
	{
	//	Loading texture
		type = texType;
		const std::string imagePath = "res/textures/" + image;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* bytes = stbi_load(imagePath.c_str(), &imgW, &imgH, &colNumCh, 0);

		glGenTextures(1, &id);
		glActiveTexture(slot);
		glBindTexture(texType, id);

		glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST	);

		glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(texType, 0, format, imgW, imgH, 0, format, pixelType, bytes);
		glGenerateMipmap(texType);

		stbi_image_free(bytes);
		glBindTexture(texType, 0);
	}

	void Texture::texUnit(kde::Shader& shader, const char* uniform, GLuint unit)
	{
	//	Bind texture sampler
		GLuint texUni = glGetUniformLocation(shader.mProgram, "tex0");
		shader.Use();
		glUniform1i(texUni, unit);
	}
	void Texture::Bind()
	{
		glBindTexture(type, id);
	}
	void Texture::Unbind()
	{
		glBindTexture(type, 0);
	}
	void Texture::Delete()
	{
		glDeleteTextures(1, &id);
	}
}