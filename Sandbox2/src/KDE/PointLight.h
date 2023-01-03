#pragma once
#include "Mesh.h"


namespace kde
{
	class PointLight
	{
	private:
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		Shader shader;

		VAO vao;

	public:
		glm::vec3 position = { 0.0f, 0.0f, -0.5f };
		glm::vec3 color = { 1.0f, 1.0f, 1.0f };
		glm::vec3 scale = { 0.05f, 0.05f, 0.05f };

	public:
		PointLight();
		~PointLight() = default;

		void Draw(Camera& camera);
		void DrawSettings();
	};
}