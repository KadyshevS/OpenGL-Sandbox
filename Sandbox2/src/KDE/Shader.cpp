#include "Shader.h"

namespace kde
{
	std::string GetFileSource(std::string filePath)
	{
		std::ifstream fis(filePath);
		if (!fis.is_open())
		{
			std::cout << "Failed to open file source." << std::endl;
		}

		std::string fileSource{ std::istreambuf_iterator<char>(fis), std::istreambuf_iterator<char>() };
		return fileSource;
	}

	Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader)
	{
	//	Getting shaders source
		std::string vs_src = GetFileSource( "res/shaders/" + vertexShader + ".vert" );
		std::string fs_src = GetFileSource( "res/shaders/" + fragmentShader + ".frag" );

		const char* vs_src_c = vs_src.c_str();
		const char* fs_src_c = fs_src.c_str();

	//	Creating & binding shaders
		GLuint vs = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vs, 1, &vs_src_c, NULL);
		glCompileShader(vs);
	
		GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fs, 1, &fs_src_c, NULL);
		glCompileShader(fs);
		
	//	Creating shader program & binding shaders to this
		mProgram = glCreateProgram();
		glAttachShader(mProgram, vs);
		glAttachShader(mProgram, fs);
		glLinkProgram(mProgram);
	
	//	Deleting shader objects
		glDeleteShader(vs);
		glDeleteShader(fs);
	}

	void Shader::Use()
	{
		glUseProgram(mProgram);
	}
	void Shader::Delete()
	{
		glDeleteProgram(mProgram);
	}
}