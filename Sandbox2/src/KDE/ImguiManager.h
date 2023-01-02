#pragma once
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

namespace kde
{
	class ImguiManager
	{
	private:
		ImGuiIO* io;

	public:
		ImguiManager(GLFWwindow* window);
		~ImguiManager();

		void Update();
		void Render();

		bool WantCaptureMouse() const;

		ImGuiIO* getIO() const;
	};
}
