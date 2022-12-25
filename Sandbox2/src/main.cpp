#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//	Creating vertex shader source code
const char* vs_src = 
	"#version 330 core\n"
	"\n"
	"in vec2 position;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(position, 0.0, 1.0);\n"
	"}\0";

//	Creating fragment shader source code
const char* fs_src = 
	"#version 330 core\n"
	"\n"
	"out vec4 color;\n"
	"void main()\n"
	"{\n"
	"	color = vec4(0.0, 1.0, 0.0, 1.0);\n"
	"}\0";

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

//	Creating & binding shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vs_src, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fs_src, NULL);
	glCompileShader(fragmentShader);
	
//	Creating shader program & binding shaders to this
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);	
	glLinkProgram(shaderProgram);

//	Deleting shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

//	Creating Vertex Buffer Object
	GLuint vao, vbo, ebo;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

//	Main loop
	while ( !glfwWindowShouldClose(win) )
	{
		glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(vao);
		
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, NULL);

		glfwSwapBuffers(win);
		glfwPollEvents();
	}
	
//	Delete everything in the end of project
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(win);
	glfwTerminate();
	return 0;
}