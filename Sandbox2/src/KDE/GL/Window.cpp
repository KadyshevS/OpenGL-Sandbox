#include "Window.h"
#include <iostream>
#include <stdexcept>

namespace GL
{
	Window::Window(const unsigned int width, const unsigned int height, const std::string& title)
	{
		//	Creating window
		win = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		if (win == NULL)
		{
			std::cout << "Failed to create window." << std::endl;
			glfwTerminate();
			
			throw std::runtime_error( "Failed to create window." );
		}
		
		SetContextCurrent();
		LoadGL();
		glViewport(0, 0, width, height);
	}
	Window::~Window()
	{
		glfwDestroyWindow(win);
	}

	GLFWwindow* Window::getWindowInst() const
	{
		return win;
	}

	void Window::SetContextCurrent()
	{
		//	Set Current context
		glfwMakeContextCurrent(win);
	}
	void Window::LoadGL()
	{
		gladLoadGL();
	}
}