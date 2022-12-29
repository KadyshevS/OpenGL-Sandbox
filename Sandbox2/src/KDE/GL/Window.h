#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

namespace GL
{
	class Window
	{
	private:
		GLFWwindow* win;

	public:
		Window(const unsigned int width, const unsigned int height, const std::string& title);
		~Window();

		GLFWwindow* getWindowInst() const;

		void SetContextCurrent();
		void LoadGL();
	};
}