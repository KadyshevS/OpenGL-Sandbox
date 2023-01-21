#include "Framebuffer.h"

namespace kde
{
	Framebuffer::Framebuffer(const unsigned WIDTH, const unsigned HEIGHT)
		:
		framebufferShader("framebuffer.vert", "framebuffer.frag")
	{
		//	Creating framebuffer
		glGenFramebuffers(1, &FBO);
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);

		//	Initialize main reactangle
		glGenVertexArrays(1, &rectVAO);
		glGenBuffers(1, &rectVBO);
		glBindVertexArray(rectVAO);
		glBindBuffer(GL_ARRAY_BUFFER, rectVBO);
		glBufferData(GL_ARRAY_BUFFER, rectVertices.size() * sizeof(float), rectVertices.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

		// Create Framebuffer Texture
		glGenTextures(1, &FBOTexture);
		glBindTexture(GL_TEXTURE_2D, FBOTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // Prevents edge bleeding
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Prevents edge bleeding
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, FBOTexture, 0);

		// Create Render Buffer Object
		glGenRenderbuffers(1, &RBO);
		glBindRenderbuffer(GL_RENDERBUFFER, RBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WIDTH, HEIGHT);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

		// Error checking framebuffer
		auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "Framebuffer error: " << fboStatus << std::endl;

		framebufferShader.Use();
		glUniform1i(glGetUniformLocation(framebufferShader.mProgram, "screenTexture"), 1);
	}
	Framebuffer::~Framebuffer()
	{
		Delete();
	}
	void Framebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	}
	void Framebuffer::Draw()
	{
		// Bind the default framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		// Draw the framebuffer rectangle
		framebufferShader.Use();
		glBindVertexArray(rectVAO);
		glDisable(GL_DEPTH_TEST); // prevents framebuffer rectangle from being discarded
		glBindTexture(GL_TEXTURE_2D, FBOTexture);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	void Framebuffer::Delete()
	{
		glDeleteFramebuffers(1, &FBO);
	}
}
