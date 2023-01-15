#include <iostream>
#include "KDE/KDstd.h"
#include "KDE/GL/GLstd.h"

const unsigned constexpr int WIDTH = 1280;
const unsigned constexpr int HEIGHT = 720;

int main()
{
//	Initializing GLFW & creating window
	GL::GLFW glfw(4, 6);
	GL::Window window(WIDTH, HEIGHT, "OpenGL Test");

//	Creating arrays of vertices & indicies of light source cube
	std::vector<Vertex> lightVertices = Cube::vertices();
	std::vector<GLuint> lightIndices = Cube::indices();
	
//	Creating & bind shaders, vao, vbo, ebo for light source
	kde::Shader shaders[] =
	{
		kde::Shader("default.vert", "pointlight_spec.frag"),
		kde::Shader("default.vert", "directlight_spec.frag"),
		kde::Shader("default.vert", "spotlight_spec.frag"),
		kde::Shader("default.vert", "directlight_spec_alphablend.frag"),
	};
	kde::Shader lightShader("light.vert", "light.frag");

	kde::Model testModel("res\\models\\nanosuit\\nanosuit.obj", 0.1f);
	kde::Model testGrass("res\\models\\terrain\\terrain.obj", 0.1f);
	kde::Model testWinLogo("res\\models\\winlogo_cube\\winlogo.obj", 0.05f);

	kde::PointLight light;
	light.position = { 0.0f, 0.2f, 0.5f };

//	Creating camera obj
	kde::Camera cam(WIDTH, HEIGHT, { 0.0f, 0.0f, 2.0f });

//	Initializing ImGui
	kde::ImguiManager imgui(window.getWindowInst());

//	Main loop
	int currShaderFile = 0;
	const char* shadersFiles[] = { "Point Light", "Directional Light", "Spot Light", "Alpha Blend" };

//	Enable depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

//	Enable stencil buffer
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

//	Enable back face culling
//	glEnable(GL_CULL_FACE);
//	glCullFace(GL_FRONT);
//	glFrontFace(GL_CW);

//	Enable alpha blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	while ( !window.ShouldClose() )
	{
		glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // GL_STENCIL_BUFFER_BIT
		window.AdjustViewport();
		imgui.Update();
		cam.UpdateMatrix(45.0f, 0.1f, 100.f);
		if (!imgui.WantCaptureMouse())
		{
			cam.Input(window.getWindowInst(), imgui.getSensDeltaTime());
		}

		ImGui::Begin("Shader");
		ImGui::ListBox("File", &currShaderFile, shadersFiles, 4);
		ImGui::End();
		
		testGrass.Draw(shaders[3], cam, light);
		testModel.Draw(shaders[currShaderFile], cam, light);

		glEnable(GL_BLEND);
		testWinLogo.Draw(shaders[3], cam, light);
		glDisable(GL_BLEND);

		light.Draw(cam);
		light.DrawWindow();
		testModel.DrawWindow();
		testGrass.DrawWindow();
		testWinLogo.DrawWindow();

		imgui.ShowStatistics();
		imgui.Render();
		glfwSwapBuffers(window.getWindowInst());
		glfwPollEvents();
	}

	return 0;
}