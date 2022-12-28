#include "Camera.h"

namespace kde
{
	Camera::Camera(const int width, const int height, glm::vec3 position)
		:
		width(width),
		height(height),
		position(position)
	{}

	void Camera::UpdateMatrix(float FOVdeg, float nearPlane, float farPlane)
	{
		glm::mat4 view(1.0f);
		glm::mat4 proj(1.0f);

		view = glm::lookAt(position, position + orientation, up);
		proj = glm::perspective(glm::radians(FOVdeg), (float)(width / height), nearPlane, farPlane);

		cameraMatrix = proj * view;
	}
	void Camera::Matrix(kde::Shader& shader, const char* uniform)
	{
		glUniformMatrix4fv(glGetUniformLocation(shader.mProgram, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
	}
	void Camera::Input(GLFWwindow* window, const float dt)
	{
		if ( glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS )
		{
			position += speed * dt * orientation;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			position += speed * dt * -glm::normalize(glm::cross(orientation, up));
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			position += speed * dt * -orientation;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			position += speed * dt * glm::normalize(glm::cross(orientation, up));
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			position += speed * dt * up;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		{
			position += speed * dt * -up;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			speed = 255.0f * 1.5f;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
		{
			speed = 255.0f * 0.5f;
		}

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			if( esc_pressed_once ) {}
			else
			{
				glfwSetInputMode(window, GLFW_CURSOR, capture_mouse ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN);
				
				capture_mouse = capture_mouse ? false : true;
				esc_pressed_once = true;
			}
		}
		else
		{
			esc_pressed_once = false;
		}

		if (capture_mouse) FreeLook(window, dt);
		else
		{
			// Unhides cursor since camera is not looking around anymore
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			// Makes sure the next time the camera looks around it doesn't jump
			firstPress = true;
		}
	}
	void Camera::FreeLook(GLFWwindow* window, const float dt)
	{
		if (firstPress)
		{
			glfwSetCursorPos(window, (width / 2), (height / 2));
			firstPress = false;
		}

		// Stores the coordinates of the cursor
		double mouseX;
		double mouseY;
		// Fetches the coordinates of the cursor
		glfwGetCursorPos(window, &mouseX, &mouseY);

		// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
		// and then "transforms" them into degrees 
		float rotX = sensetivity * (float)(mouseY - (height / 2)) / height;
		float rotY = sensetivity * (float)(mouseX - (width / 2)) / width;

		// Calculates upcoming vertical change in the Orientation
		glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(-rotX), glm::normalize(glm::cross(orientation, up)));

		// Decides whether or not the next vertical Orientation is legal or not
		if (abs(glm::angle(newOrientation, up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			orientation = newOrientation;
		}

		// Rotates the Orientation left and right
		orientation = glm::rotate(orientation, glm::radians(-rotY), up);

		// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
}