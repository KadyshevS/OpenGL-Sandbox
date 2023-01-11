#include "Texture.h"

namespace kde
{
	Texture::Texture(const std::string& image, const std::string& texType, GLenum format)
	{
	//	Loading texture
		type = texType;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* bytes = stbi_load(image.c_str(), &imgW, &imgH, &colNumCh, 0);

		// Generates an OpenGL texture object
		glGenTextures(1, &id);
		// Assigns the texture to a Texture Unit
		if (texType == "diffuse")
		{
			unit = 0;
		}
		else if (texType == "specular")
		{
			unit = 1;
		}
		else
		{
			std::cout << "Failed to load texture(Wrong type)." << std::endl;
		}
		glActiveTexture(GL_TEXTURE0 + unit);
		
		glBindTexture(GL_TEXTURE_2D, id);
		// Configures the type of algorithm that is used to make the image smaller or bigger
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		// Configures the way the texture repeats (if it does at all)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// Extra lines in case you choose to use GL_CLAMP_TO_BORDER
		// float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
		// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

		// Assigns the image to the OpenGL Texture object
		glTexImage2D(GL_TEXTURE_2D, 0, format, imgW, imgH, 0, format, GL_UNSIGNED_BYTE, bytes);
		// Generates MipMaps
		glGenerateMipmap(GL_TEXTURE_2D);

		// Deletes the image data as it is already in the OpenGL Texture object
		stbi_image_free(bytes);

		// Unbinds the OpenGL Texture object so that it can't accidentally be modified
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
	void Texture::texUnit(kde::Shader& shader, const char* uniform, GLuint unit)
	{
	//	Bind texture sampler
		GLuint texUni = glGetUniformLocation(shader.mProgram, uniform);
		shader.Use();
		glUniform1i(texUni, unit);
	}
	void Texture::Bind()
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, id);
	}
	void Texture::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void Texture::Delete()
	{
		glDeleteTextures(1, &id);
	}
}