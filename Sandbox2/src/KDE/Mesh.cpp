#include "Mesh.h"
#include "ImguiManager.h"

namespace kde
{
	Mesh::Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures, const std::string& meshName)
		:
		vertices(vertices),
		indices(indices),
		textures(textures),
		meshName(meshName)
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

	void Mesh::Draw(Shader& shader, Camera& camera, glm::vec3& lightPos, glm::vec3& lightColor)
	{
		glm::mat4 modelMat(1.0f);

		auto t = glm::translate(glm::mat4(1.0f), position);
		auto s = glm::scale(glm::mat4(1.0f), scale);
		auto r =
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		modelMat = s * r * t;
		
		shader.Use();
		glUniformMatrix4fv(glGetUniformLocation(shader.mProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMat));
		glUniform4f(glGetUniformLocation(shader.mProgram, "lightColor"), lightColor.x, lightColor.y, lightColor.z, 1.0f);
		glUniform3f(glGetUniformLocation(shader.mProgram, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

		vao.Bind();
		
		unsigned int numDiffuse = 0;
		unsigned int numSpecular = 0;

		for (unsigned int i = 0; i < textures.size(); i++)
		{
			std::string num;
			std::string type = textures[i].type;
			if (type == "diffuse")
			{
				num = std::to_string(numDiffuse++);
			}
			else if (type == "specular")
			{
				num = std::to_string(numSpecular++);
			}
			textures[i].texUnit(shader, (type + num).c_str(), i);
			textures[i].Bind();
		}

		glUniform3f(glGetUniformLocation(shader.mProgram, "camPos"), camera.position.x, camera.position.y, camera.position.z);
		camera.Matrix(shader, "camMatrix");

		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	}
	std::vector<Vertex> Mesh::getVertices() const
	{
		return vertices;
	}
	std::vector<unsigned int> Mesh::getIndices() const
	{
		return indices;
	}
	void Mesh::DrawWindow()
	{
		if (ImGui::Begin(meshName.c_str()))
		{
			ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Position");
			ImGui::SliderFloat("X", &position.x, -2.0f, 2.0f, "%.1f");
			ImGui::SliderFloat("Y", &position.y, -2.0f, 2.0f, "%.1f");
			ImGui::SliderFloat("Z", &position.z, -2.0f, 2.0f, "%.1f");
			ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Scale");
			ImGui::SliderFloat("X ", &scale.x, 0.5f, 3.0f, "%.1f");
			ImGui::SliderFloat("Y ", &scale.y, 0.5f, 3.0f, "%.1f");
			ImGui::SliderFloat("Z ", &scale.z, 0.5f, 3.0f, "%.1f");
			ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Rotation");
			ImGui::SliderFloat("X  ", &rotation.x, -180.0f, 180.0f);
			ImGui::SliderFloat("Y  ", &rotation.y, -180.0f, 180.0f);
			ImGui::SliderFloat("Z  ", &rotation.z, -180.0f, 180.0f);

			if (ImGui::Button("Clear"))
			{
				position = { 0.0f, 0.0f, 0.0f };
				scale = { 1.0f, 1.0f, 1.0f };
				rotation = { 0.0f, 0.0f, 0.0f };
			}
		}
		ImGui::End();
	}
}
