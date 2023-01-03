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

		void ShowStatistics();

		bool WantCaptureMouse() const;

		int getFramerate() const;
		float getDeltaTime() const;
		float getSensDeltaTime() const;

		ImGuiIO* getIO() const;
	};
}
