#include "PointLight.h"
#include "shapes/Cube.h"

namespace kde
{
	PointLight::PointLight():
		vertices( Cube::vertices() ),
		indices( Cube::indices() ),
		shader( Shader("light.vert", "light.frag") )
	{
		vao.Bind();

		VBO vbo(vertices);
		EBO ebo(indices);

		vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
		vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
		vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
		vao.LinkAttrib(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));

		vao.Unbind();
		vbo.Unbind();
		ebo.Unbind();
	}

	void PointLight::Draw(Camera& camera)
	{
		glm::mat4 modelMat(1.0f);
		
		modelMat = glm::translate(modelMat, position);
		modelMat = glm::scale(modelMat, scale);

		shader.Use();
		glUniformMatrix4fv(glGetUniformLocation(shader.mProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMat));
		glUniform4f(glGetUniformLocation(shader.mProgram, "lightColor"), color.x, color.y, color.z, 1.0f);

		vao.Bind();

		glUniform3f(glGetUniformLocation(shader.mProgram, "camPos"), camera.position.x, camera.position.y, camera.position.z);
		camera.Matrix(shader, "camMatrix");

		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	}
}