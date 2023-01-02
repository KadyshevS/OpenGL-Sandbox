#pragma once
#include <string>
#include "VAO.h"
#include "EBO.h"
#include "Camera.h"
#include "Texture.h"

namespace kde
{
	class Mesh
	{
	public:
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		std::vector<Texture> textures;

		glm::vec3 position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 scale = { 1.0f, 1.0f, 1.0f };

		VAO vao;

	public:
		Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures);

		void Draw(Shader& shader, Camera& camera, glm::vec3& lightPos, glm::vec4& lightColor);

		std::vector<Vertex> getVertices() const;
		std::vector<unsigned int> getIndices() const;

		void setPosition(const glm::vec3& translation);
		void setScale(const glm::vec3& scaling);
	};
}