#pragma once
#include "VAO.h"
#include "EBO.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Shader.h"
#include "Camera.h"

namespace kde
{
	class Model
	{
	private:
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;

		glm::vec3 position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 scale = { 1.0f, 1.0f, 1.0f };

		VAO vao;

	public:
		Model() = default;
		Model(const std::string& fileName, const float scale = 1.0f);
		~Model() = default;

		bool LoadMesh(const std::string& fileName, const float scale = 1.0f);
		void Draw(Shader& shader, Camera& camera, glm::vec3& lightPos, glm::vec3& lightColor);

		std::vector<Vertex> getVertices() const;
		std::vector<unsigned int> getIndices() const;

		void setPosition(const glm::vec3& translation);
		void setScale(const glm::vec3& scaling);
	};
}