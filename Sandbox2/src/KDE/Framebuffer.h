#pragma once
#include "Shader.h"
#include <vector>

namespace kde
{
	class Framebuffer
	{
	private:
		const std::vector<float> rectVertices =
		{
			// Coords    // texCoords
			 1.0f, -1.0f,  1.0f, 0.0f,
			-1.0f, -1.0f,  0.0f, 0.0f,
			-1.0f,  1.0f,  0.0f, 1.0f,

			 1.0f,  1.0f,  1.0f, 1.0f,
			 1.0f, -1.0f,  1.0f, 0.0f,
			-1.0f,  1.0f,  0.0f, 1.0f
		};
		Shader framebufferShader;

		unsigned int FBO;
		unsigned int rectVAO, rectVBO;
		unsigned int FBOTexture;
		unsigned int RBO;

	public:
		Framebuffer(const unsigned WIDTH, const unsigned HEIGHT);
		~Framebuffer();

		void Bind();
		void Draw();
		void Delete();
	};
}
