#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 normal;
	glm::vec2 texUV;
};

namespace kde
{
	class VBO
	{
	public:
		GLuint id;

	public:
		VBO(std::vector<Vertex>& vertices);
		~VBO() = default;

		void Bind();
		void Unbind();
		void Delete();
	};
}
