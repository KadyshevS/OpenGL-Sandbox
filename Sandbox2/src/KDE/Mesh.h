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
		friend class Model;
	public:
		std::string meshName = "";

		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		std::vector<Texture> textures;

		glm::vec3 position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 scale = { 1.0f, 1.0f, 1.0f };
		glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };

		VAO vao;
	public:
		Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures, const std::string& meshName);

		void Draw(Shader& shader, Camera& camera, glm::vec3& lightPos, glm::vec3& lightColor);

		std::vector<Vertex> getVertices() const;
		std::vector<unsigned int> getIndices() const;

		void DrawWindow();
	};
}