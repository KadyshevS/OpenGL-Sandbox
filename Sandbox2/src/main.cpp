#include <iostream>
#include "KDE/KDstd.h"
#include "KDE/GL/GLstd.h"
#include "KDE/Model.h"

const unsigned constexpr int WIDTH = 800;
const unsigned constexpr int HEIGHT = 800;

int main()
{
//	Initializing GLFW & creating window
	GL::GLFW glfw(3, 3);
	GL::Window window(WIDTH, HEIGHT, "OpenGL Test");

	Vertex vertices[] =
	{
		{ {-1.0f, 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f } },
		{ {-1.0f, 0.0f,-1.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f } },
		{ { 1.0f, 0.0f,-1.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f } },
		{ { 1.0f, 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } }
	};
	GLuint indices[] =
	{
		0, 1, 2,
		0, 2, 3
	};
//	Creating arrays of vertices & indicies of light source cube
	Vertex lightVertices[] =
	{//			|   COORDINATES   |
		{ {-1.0f,-1.0f, 1.0f} },
		{ { 1.0f,-1.0f, 1.0f} },
		{ { 1.0f, 1.0f, 1.0f} },
		{ {-1.0f, 1.0f, 1.0f} },
		{ {-1.0f,-1.0f,-1.0f} },
		{ { 1.0f,-1.0f,-1.0f} },
		{ { 1.0f, 1.0f,-1.0f} },
		{ {-1.0f, 1.0f,-1.0f} },
	};
	GLuint lightIndices[] =
	{
		0, 1, 2,
		0, 2, 3,
		4, 5, 6,
		4, 6, 7,
		4, 0, 3,
		4, 3, 7,
		1, 2, 6,
		1, 5, 6,
		3, 7, 6,
		3, 2, 6,
		0, 1, 4,
		1, 4, 5,
	};

//	Creating array of textures
	kde::Texture textures[] =
	{
		kde::Texture( "planks.png"	  , "diffuse" , 0, GL_RGBA ),
		kde::Texture( "planksSpec.png", "specular", 1, GL_RED ),
	};
	
//	Creating & bind shaders, vao, vbo, ebo for light source
	kde::Shader pyramidShader("default.vert", "default.frag");
	
	std::vector<Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector<GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector<kde::Texture> tex(textures, textures + sizeof(textures) / sizeof(kde::Texture));

	kde::Shader lightShader("light.vert", "light.frag");

	std::vector<Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector<GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));

	kde::Mesh floor(verts, ind, tex);
	kde::Mesh light(lightVerts, lightInd, tex);

	glm::vec3 lightPos = glm::vec3(0.0f, 0.2f, 0.5f);
	glm::vec3 lightScale = glm::vec3(0.05f, 0.05f, 0.05f);
	glm::mat4 lightModel = glm::mat4(1.0f);

	lightModel = glm::translate(lightModel, lightPos);
	lightModel = glm::scale(lightModel, lightScale);

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 pyramidScale = glm::vec3(0.75f, 0.75f, 0.75f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);
	pyramidModel = glm::scale(pyramidModel, pyramidScale);

	kde::Model nanosuit;
	nanosuit.LoadMesh( "nanosuit", 0.25f );

	lightShader.Use();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.mProgram, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.mProgram, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	pyramidShader.Use();
	glUniformMatrix4fv(glGetUniformLocation(pyramidShader.mProgram, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(pyramidShader.mProgram, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(pyramidShader.mProgram, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

//	Enable depth test
	glEnable(GL_DEPTH_TEST);

//	Creating camera obj
	kde::Camera cam(WIDTH, HEIGHT, { 0.0f, 0.0f, 2.0f });

//	Main loop
	while ( !glfwWindowShouldClose(window.getWindowInst()) )
	{
		glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		cam.UpdateMatrix(65.0f, 0.1f, 100.f);
		cam.Input(window.getWindowInst(), 0.000001f);

		light.Draw(lightShader, cam);
		nanosuit.Draw(pyramidShader, cam, lightPos, lightColor);

		glfwSwapBuffers(window.getWindowInst());
		glfwPollEvents();
	}
	
//	Delete everything in the end of project
	lightShader.Delete();
	pyramidShader.Delete();

	return 0;
}