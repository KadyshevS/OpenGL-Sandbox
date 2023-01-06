#include "PointLight.h"
#include "shapes/Cube.h"
#include "ImguiManager.h"

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
		
		auto t = glm::translate(glm::mat4(1.0f), position);
		auto s = glm::scale(glm::mat4(1.0f), scale);

		modelMat = t * s;

		shader.Use();
		glUniformMatrix4fv(glGetUniformLocation(shader.mProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMat));
		glUniform4f(glGetUniformLocation(shader.mProgram, "lightColor"), color.x, color.y, color.z, 1.0f);

		vao.Bind();

		glUniform3f(glGetUniformLocation(shader.mProgram, "camPos"), camera.position.x, camera.position.y, camera.position.z);
		camera.Matrix(shader, "camMatrix");

		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	}
	void PointLight::DrawWindow()
	{
		if ( ImGui::Begin("Point Light"))
		{
			ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Position");
			ImGui::SliderFloat("X", &position.x, -3.0f, 3.0f, "%.1f");
			ImGui::SliderFloat("Y", &position.y, -3.0f, 3.0f, "%.1f");
			ImGui::SliderFloat("Z", &position.z, -3.0f, 3.0f, "%.1f");
			ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Scale");
			ImGui::SliderFloat("X ", &scale.x, 0.01f, 2.0f, "%.2f");
			ImGui::SliderFloat("Y ", &scale.y, 0.01f, 2.0f, "%.2f");
			ImGui::SliderFloat("Z ", &scale.z, 0.01f, 2.0f, "%.2f");
			ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Color");
			ImGui::ColorEdit3("RGB", &color.r);

			if ( ImGui::Button("Clear"))
			{
				position = { 0.0f, 0.2f, 0.5f };
				scale = { 0.05f, 0.05f, 0.05f };
				color = { 1.0f, 1.0f, 1.0f };
			}
		}
		ImGui::End();
	}
}