#include "ImguiManager.h"
#include <sstream>

namespace kde
{
	ImguiManager::ImguiManager(GLFWwindow* window)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		io = &ImGui::GetIO();
		(void)io;
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330");
		io->ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
	}
	ImguiManager::~ImguiManager()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImguiManager::Update()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		
		ImGui::NewFrame();
	}
	void ImguiManager::Render()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImguiManager::ShowStatistics()
	{
		std::stringstream ss;
		ss << "Framerate: " << getFramerate() << "\nDelta time: " << getDeltaTime();

		ImGui::Begin("Statistics");
		ImGui::Text( ss.str().c_str() );
		ImGui::End();
	}

	bool ImguiManager::WantCaptureMouse() const
	{
		return io->WantCaptureMouse;
	}
	int ImguiManager::getFramerate() const
	{
		return io->Framerate;
	}
	float ImguiManager::getDeltaTime() const
	{
		return io->DeltaTime;
	}
	float ImguiManager::getSensDeltaTime() const
	{
		return io->DeltaTime * 0.01f;
	}
	ImGuiIO* ImguiManager::getIO() const
	{
		return io;
	}
}
