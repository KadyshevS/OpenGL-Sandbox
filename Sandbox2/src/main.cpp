#include <iostream>
#include "KDE/KDstd.h"

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 800;

const float FOV = 45.0f;	

int main()
{
	FrameTimer ft;

//	Initialize GLFW
	glfwInit();
//	Set OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			   
//	Creating verticies of triangle
	GLfloat verts[] =
	{
	//     COORDINATES		 /          COLORS       /    TexCoord  /   //
		-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
		 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
		 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
		 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
	};	

//	Creating array of verticies
	GLuint indicies[] =
	{
		0, 1, 2,
		0, 2, 3,
		0, 1, 4,
		1, 2, 4,
		2, 3, 4,
		3, 0, 4,
	};

//	Creating window
	GLFWwindow* win = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Test", NULL, NULL);
	if (win == NULL)
	{
		std::cout << "Failed to create window." << std::endl;
		glfwTerminate();
		return -1;
	}

//	Set Current context
	glfwMakeContextCurrent(win);
	
	gladLoadGL();

	glViewport(0, 0, WIDTH, HEIGHT);

//	Creating & bind Shaders, VAO, VBO, EBO
	kde::Shader shdr1("default", "default");
	
	kde::VAO vao1;
	vao1.Bind();

	kde::VBO vbo1(verts, sizeof(verts));
	kde::EBO ebo1(indicies, sizeof(indicies));
	
	vao1.LinkAttrib( vbo1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0 );
	vao1.LinkAttrib( vbo1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)) );
	vao1.LinkAttrib( vbo1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)) );

	vao1.Unbind();
	vbo1.Unbind();
	ebo1.Unbind();

//	Texture init
	kde::Texture tex0( "brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA );
	tex0.texUnit(shdr1, "tex0", 0);
	
	tex0.Unbind();
	
//	Depth test
	glEnable(GL_DEPTH_TEST);	

	const float rotVel = 255.0f * 80;
	float rotation = 0.0f;

//	Main loop
	while ( !glfwWindowShouldClose(win) )
	{
		glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shdr1.Use();

		rotation += rotVel * ft.Peek();

		glm::mat4 model(1.0f);
		glm::mat4 view(1.0f);
		glm::mat4 proj(1.0f);
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
		proj = glm::perspective(glm::radians(FOV), (float)(WIDTH/HEIGHT), 0.1f, 100.0f);

		int modelLoc = glGetUniformLocation(shdr1.mProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		int viewLoc = glGetUniformLocation(shdr1.mProgram, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));	
		int projLoc = glGetUniformLocation(shdr1.mProgram, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

		tex0.Bind();
		vao1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indicies)/sizeof(int), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(win);
		glfwPollEvents();

		ft.Mark();
	}
	
//	Delete everything in the end of project
	vao1.Delete();
	vbo1.Delete();
	ebo1.Delete();
	tex0.Delete();
	shdr1.Delete();

	glfwDestroyWindow(win);
	glfwTerminate();
	return 0;
}