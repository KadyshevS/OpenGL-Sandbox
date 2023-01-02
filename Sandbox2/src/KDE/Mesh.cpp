#include "Mesh.h"

namespace kde
{
	Mesh::Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures)
		:
		vertices(vertices),
		indices(indices),
		textures(textures)
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

	void Mesh::Draw(Shader& shader, Camera& camera, glm::vec3& lightPos, glm::vec4& lightColor)
	{
		glm::mat4 modelMat(1.0f);
		modelMat = glm::translate(modelMat, this->position);
		modelMat = glm::scale(modelMat, this->scale);
		
		shader.Use();
		glUniformMatrix4fv(glGetUniformLocation(shader.mProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMat));
		glUniform4f(glGetUniformLocation(shader.mProgram, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
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
	void Mesh::setPosition(const glm::vec3& translation)
	{
		position = translation;
	}
	void Mesh::setScale(const glm::vec3& scaling)
	{
		scale = scaling;
	}
}
