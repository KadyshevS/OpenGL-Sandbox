#include <iostream>
#include "KDE/gl.h"
#include "KDE/KDstd.h"
#include <stb/stb_image.h>

int main()
{
//	Initialize GLFW
	glfwInit();
//	Set OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
//	Creating verticies of triangle
	GLfloat verts[] =
	{
//			POSITION			  COLOR					UV
		 -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
		  0.5f, -0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,
		  0.5f,  0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
		 -0.5f,  0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,
	};

//	Creating array of verticies
	GLuint indicies[] =
	{
		0, 1, 2,
		2, 3, 0,
	};

//	Creating window
	GLFWwindow* win = glfwCreateWindow(800, 800, "OpenGL Test", NULL, NULL);
	if (win == NULL)
	{
		std::cout << "Failed to create window." << std::endl;
		glfwTerminate();
		return -1;
	}

//	Set Current context
	glfwMakeContextCurrent(win);
	
	gladLoadGL();

	glViewport(0, 0, 800, 800);

//	Creating & bind Shaders, VAO, VBO, EBO
	kde::Shader shdr1("default", "default");
	
	kde::VAO vao1;
	vao1.Bind();

	kde::VBO vbo1(verts, sizeof(verts));
	kde::EBO ebo1(indicies, sizeof(indicies));
	
	vao1.LinkAttrib( vbo1, 0, 2, GL_FLOAT, 7 * sizeof(float), (void*)0 );
	vao1.LinkAttrib( vbo1, 1, 3, GL_FLOAT, 7 * sizeof(float), (void*)(2 * sizeof(float)) );
	vao1.LinkAttrib( vbo1, 2, 2, GL_FLOAT, 7 * sizeof(float), (void*)(5 * sizeof(float)) );

	vao1.Unbind();
	vbo1.Unbind();
	ebo1.Unbind();

//	Creating texture
	kde::Texture tex("kot.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	tex.texUnit(shdr1, "tex0", 0);

//	Main loop
	while ( !glfwWindowShouldClose(win) )
	{
		glClearColor(0.2f, 0.3f, 0.8f, 0.5f);
		glClear(GL_COLOR_BUFFER_BIT);
		shdr1.Use();
		tex.Bind();
		vao1.Bind();
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, NULL);

		glfwSwapBuffers(win);
		glfwPollEvents();
	}
	
//	Delete everything in the end of project
	vao1.Delete();
	vbo1.Delete();
	ebo1.Delete();
	tex.Delete();
	shdr1.Delete();

	glfwDestroyWindow(win);
	glfwTerminate();
	return 0;
}