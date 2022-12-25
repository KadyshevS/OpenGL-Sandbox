#include "Shader.h"

namespace kde
{
	std::string GetFileSource(std::string filePath)
	{
		std::ifstream fis(filePath);
		if ( !fis.is_open() )
		{
			std::cout << "Failed to open file source." << std::endl;
		}

		std::string fileSource{ std::istreambuf_iterator<char>(fis), std::istreambuf_iterator<char>() };
		return fileSource;
	}
	unsigned int CompileShader(unsigned int type, const std::string& source)
	{
	    unsigned int id = glCreateShader(type);
	    const char* src = source.c_str();
	    glShaderSource(id, 1, &src, nullptr);
	    glCompileShader(id);
	
	    int result;
	    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			int len;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
			char* msg = (char*)alloca(len * sizeof(char));
			glGetShaderInfoLog(id, len, &len, msg);
			std::cout << "Failed to compile " <<
				(type == GL_VERTEX_SHADER ? "vertex" : "fragment")
				<< " shader " << std::endl;
			std::cout << msg << std::endl;
			glDeleteShader(id);

			return 0;
		}

		return id;
	}

	Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader)
	{
	//	Getting shaders source
		std::string vs_src = GetFileSource( "res/shaders/" + vertexShader + ".vert" );
		std::string fs_src = GetFileSource( "res/shaders/" + fragmentShader + ".frag" );

	//	Creating & binding shaders
		GLuint vs = CompileShader(GL_VERTEX_SHADER, vs_src);
		GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fs_src);
		
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