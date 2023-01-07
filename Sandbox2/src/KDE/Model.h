#pragma once
#include "VAO.h"
#include "EBO.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Shader.h"
#include "Camera.h"
#include "PointLight.h"
#include "Mesh.h"

namespace kde
{
	class Model
	{
	private:
		kde::Shader outlineShader = kde::Shader("outline.vert", "outline.frag");

		std::string fileName;

		std::vector<Mesh> aiMeshes;

		glm::vec3 position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 scale = { 1.0f, 1.0f, 1.0f };
		glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };

		VAO vao;
	public:
		Model(const std::string& fileName, const float scale = 1.0f);
		~Model() = default;

		bool LoadMesh(const std::string& fileName, const float scale = 1.0f);

		void Draw(Shader& shader, Camera& camera, PointLight& light);
		void DrawOutline(Shader& shader, Camera& cam, PointLight& light, float outlining = 1.08f, glm::vec3 outlineColor = {1.0f, 1.0f, 1.0f});

		void setPosition(const glm::vec3& translation);
		void setScale(const glm::vec3& scaling);

		void DrawWindow();
	};
}