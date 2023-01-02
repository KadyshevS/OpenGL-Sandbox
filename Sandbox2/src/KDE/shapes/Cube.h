#pragma once
#include "../VAO.h"

struct Cube
{
	static std::vector<Vertex> vertices()
	{
		return 
		{
			{ {-1.0f,-1.0f, 1.0f} },
			{ { 1.0f,-1.0f, 1.0f} },
			{ { 1.0f, 1.0f, 1.0f} },
			{ {-1.0f, 1.0f, 1.0f} },
			{ {-1.0f,-1.0f,-1.0f} },
			{ { 1.0f,-1.0f,-1.0f} },
			{ { 1.0f, 1.0f,-1.0f} },
			{ {-1.0f, 1.0f,-1.0f} },
		};
	}
	static std::vector<GLuint> indices()
	{
		return
		{
			0, 1, 2,
			0, 2, 3,
			4, 5, 6,
			4, 6, 7,
			4, 0, 3,
			4, 3, 7,
			1, 2, 6,
			1, 5, 6,
			3, 7, 6,
			3, 2, 6,
			0, 1, 4,
			1, 4, 5
		};
	}
};