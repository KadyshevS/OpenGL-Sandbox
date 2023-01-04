#pragma once
#include "../VAO.h"

struct Plank
{
	static std::vector<Vertex> vertices()
	{
		return
		{
			{ {-1.0f, 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f } },
			{ {-1.0f, 0.0f,-1.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f } },
			{ { 1.0f, 0.0f,-1.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f } },
			{ { 1.0f, 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } }
		};
	}
	static std::vector<GLuint> indices()
	{
		return
		{
			0, 1, 2,
			0, 2, 3
		};
	}
};