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
		kde::VAO vao;
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;

		glm::mat4 modelMat = glm::mat4(1.0f);

	public:
		Model();
		~Model();

		bool LoadMesh(const std::string& fileName, const float scale = 1.0f);
		void Draw(Shader& shader, Camera& camera);
		void Draw(Shader& shader, Camera& camera, glm::vec3& lightPos, glm::vec4& lightColor);
	};
}