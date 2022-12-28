#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Shader.h"

namespace kde
{
	class Camera
	{
	private:
		bool capture_mouse = false;
		bool esc_pressed_once = false;
		bool firstPress = true;

	private:
		void FreeLook(GLFWwindow* window, const float dt);

	public:
		glm::vec3 position;
		glm::vec3 orientation = { 0.0f, 0.0f, -1.0f };
		glm::vec3 up = { 0.0f, 1.0f, 0.0f };
		glm::mat4 cameraMatrix = glm::mat4( 1.0f );

		int width, height;
		float speed = 255.0f;
		float sensetivity = 100.0f;

	public:
		Camera(const int width, const int height, glm::vec3 position);

		void UpdateMatrix(float FOVdeg, float nearPlane, float farPlane);
		void Matrix(kde::Shader& shader, const char* uniform);
		void Input(GLFWwindow* window, const float dt);
	};
}
