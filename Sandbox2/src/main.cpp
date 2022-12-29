#include <iostream>
#include "KDE/KDstd.h"
#include "KDE/GL/GLstd.h"

const unsigned constexpr int WIDTH = 800;
const unsigned constexpr int HEIGHT = 800;

int main()
{
//	Initializing GLFW & creating window
	GL::GLFW glfw(3, 3);
	GL::Window window(WIDTH, HEIGHT, "OpenGL Test");

	//	Creating arrays of verticies & indicies of pyramid
	GLfloat verts[] =
	{
//	   /    COORDINATES		 /    TexCoord   /	    NORMALS      /  //
	-1.0f, 0.0f,  1.0f,			0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	-1.0f, 0.0f, -1.0f,			0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f, -1.0f,			1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f,  1.0f,			1.0f, 0.0f,		0.0f, 1.0f, 0.0f
	};
	GLuint indicies[] =
	{
		0,	1,	2,
		0,	2,	3,
		4,	6,	5,
		7,	9,	8,
		10, 12, 11,
		13, 15, 14,
	};

	//	Creating arrays of verticies & indicies of light source cube
	GLfloat lightVerts[] =
	{
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
	};
	GLuint lightIndicies[] =
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

//	Creating & bind Shaders, VAO, VBO, EBO
	kde::Shader pyramidShader("default", "default");
	
	kde::VAO vao1;
	vao1.Bind();

	kde::VBO vbo1(verts, sizeof(verts));
	kde::EBO ebo1(indicies, sizeof(indicies));
	
	vao1.LinkAttrib( vbo1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0 );
	vao1.LinkAttrib( vbo1, 1, 2, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)) );
	vao1.LinkAttrib( vbo1, 2, 3, GL_FLOAT, 8 * sizeof(float), (void*)(5 * sizeof(float)) );

	vao1.Unbind();
	vbo1.Unbind();
	ebo1.Unbind();

//	Creating & bind shaders, vao, vbo, ebo for light source
	kde::Shader lightShader("light", "light");
	
	kde::VAO lightVAO;
	lightVAO.Bind();

	kde::VBO lightVBO(lightVerts, sizeof(lightVerts));
	kde::EBO lightEBO(lightIndicies, sizeof(lightIndicies));

	lightVAO.LinkAttrib( lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0 );

	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();

	glm::vec3 lightPos = glm::vec3(0.0f, 0.2f, -0.2f);
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

	lightShader.Use();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.mProgram, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.mProgram, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	pyramidShader.Use();
	glUniformMatrix4fv(glGetUniformLocation(pyramidShader.mProgram, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(pyramidShader.mProgram, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(pyramidShader.mProgram, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

//	Texture init
	kde::Texture tex0( "planks.png", GL_TEXTURE_2D, 0, GL_RGBA );
	tex0.texUnit(pyramidShader, "tex0", 0);
	kde::Texture tex1( "planksSpec.png", GL_TEXTURE_2D, 1, GL_RED );
	tex0.texUnit(pyramidShader, "tex1", 1);
	
	tex0.Unbind();

//	Enable depth test
	glEnable(GL_DEPTH_TEST);

//	Creating camera obj
	kde::Camera cam(WIDTH, HEIGHT, { 0.0f, 0.0f, 2.0f });

//	Main loop
	while ( !glfwWindowShouldClose(window.getWindowInst()) )
	{
		glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		cam.UpdateMatrix(65.0f, 0.05f, 100.f);

		pyramidShader.Use();
		glUniform3f(glGetUniformLocation(pyramidShader.mProgram, "camPos"), cam.position.x, cam.position.y, cam.position.z);

		cam.Matrix(pyramidShader, "camMatrix");
		cam.Input(window.getWindowInst(), 0.000001f);
		tex0.Bind();
		tex1.Bind();
		vao1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indicies)/sizeof(int), GL_UNSIGNED_INT, 0);

		lightShader.Use();
		cam.Matrix(lightShader, "camMatrix");
		lightVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndicies)/sizeof(int), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window.getWindowInst());
		glfwPollEvents();
	}
	
//	Delete everything in the end of project
	vao1.Delete();
	vbo1.Delete();
	ebo1.Delete();
	tex0.Delete();
	pyramidShader.Delete();

	return 0;
}