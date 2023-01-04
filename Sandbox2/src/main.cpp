#include <iostream>
#include "KDE/KDstd.h"
#include "KDE/GL/GLstd.h"

const unsigned constexpr int WIDTH = 1280;
const unsigned constexpr int HEIGHT = 720;

int main()
{
//	Initializing GLFW & creating window
	GL::GLFW glfw(3, 3);
	GL::Window window(WIDTH, HEIGHT, "OpenGL Test");

//	Creating arrays of vertices & indicies of light source cube
	std::vector<Vertex> lightVertices = Cube::vertices();
	std::vector<GLuint> lightIndices = Cube::indices();

	std::vector<Vertex> plankVerts = Plank::vertices();
	std::vector<GLuint> plankInd = Plank::indices();

//	Creating array of textures
	std::vector<kde::Texture> tex =
	{
		kde::Texture("res\\textures\\planks.png"	 , "diffuse" , GL_RGBA),
		kde::Texture("res\\textures\\planksSpec.png", "specular", GL_RED),
	};
	
//	Creating & bind shaders, vao, vbo, ebo for light source
	kde::Shader modelShader("default.vert", "default.frag");
	kde::Shader lightShader("light.vert", "light.frag");

	kde::Model testModel("res\\models\\nanosuit\\nanosuit.obj", 0.1f);

	kde::PointLight light;
	light.position = { 0.0f, 0.2f, 0.5f };

//	Enable depth test
	glEnable(GL_DEPTH_TEST);

//	Creating camera obj
	kde::Camera cam(WIDTH, HEIGHT, { 0.0f, 0.0f, 2.0f });

//	Initializing ImGui
	kde::ImguiManager imgui(window.getWindowInst());

//	Main loop
	while ( !glfwWindowShouldClose(window.getWindowInst()) )
	{
		glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		window.AdjustViewport();
		imgui.Update();
		
		cam.UpdateMatrix(45.0f, 0.1f, 100.f);

		if (!imgui.WantCaptureMouse())
		{
			cam.Input(window.getWindowInst(), imgui.getSensDeltaTime());
		}

		light.Draw(cam);
		testModel.Draw(modelShader, cam, light);

		light.DrawWindow();
		testModel.DrawWindow();

		imgui.ShowStatistics();
		imgui.Render();
		glfwSwapBuffers(window.getWindowInst());
		glfwPollEvents();
	}

	return 0;
}