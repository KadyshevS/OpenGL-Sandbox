#include "GLFW.h"
#include <GLFW/glfw3.h>
#include <stdexcept>

namespace GL
{
	GLFW::GLFW(const unsigned short ver_major, const unsigned short ver_minor)
	{
		//	Initialize GLFW
		if( !glfwInit() )
		{
			throw std::runtime_error("Failed to initialize GLFW.");
		}
		//	Set OpenGL version
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, (int)ver_major);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, (int)ver_minor);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}
	GLFW::~GLFW()
	{
		glfwTerminate();
	}
}
