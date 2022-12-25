#include <iostream>
#include "KDE/gl.h"
#include "KDE/KDstd.h"

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
		 0.0f ,  0.5f,
		-0.25f,  0.0f,
		 0.25f,  0.0f,
		-0.5f , -0.5f,
		-0.5f , -0.5f,
		 0.0f , -0.5f,
		 0.5f , -0.5f,
	};

//	Creating array of verticies
	GLuint indicies[] =
	{
		0, 1, 2,
		1, 4, 5,
		2, 5, 6,
	};

//	Creating window
	GLFWwindow* win = glfwCreateWindow(800, 600, "OpenGL Test", NULL, NULL);
	if (win == NULL)
	{
		std::cout << "Failed to create window." << std::endl;
		glfwTerminate();
		return -1;
	}

//	Set Current context
	glfwMakeContextCurrent(win);
	
	gladLoadGL();

	glViewport(0, 0, 800, 600);

//	Creating & bind Shaders, VAO, VBO, EBO
	kde::Shader shdr1("default", "default");
	
	kde::VAO vao1;
	vao1.Bind();

	kde::VBO vbo1(verts, sizeof(verts));
	kde::EBO ebo1(indicies, sizeof(indicies));
	
	vao1.LinkVBO(vbo1, 0, 2);

	vao1.Unbind();
	vbo1.Unbind();
	ebo1.Unbind();

//	Main loop
	while ( !glfwWindowShouldClose(win) )
	{
		glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shdr1.Use();
		vao1.Bind();
		
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, NULL);

		glfwSwapBuffers(win);
		glfwPollEvents();
	}
	
//	Delete everything in the end of project
	vao1.Delete();
	vbo1.Delete();
	ebo1.Delete();
	shdr1.Delete();

	glfwDestroyWindow(win);
	glfwTerminate();
	return 0;
}