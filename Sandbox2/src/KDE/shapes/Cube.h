#pragma once
#include "../VAO.h"

struct Cube
{
	static std::vector<Vertex> vertices()
	{
		return 
		{
			{ {-1.0f, -1.0f,  1.0} },
			{ {-1.0f, -1.0f, -1.0} },
			{ { 1.0f, -1.0f, -1.0} },
			{ { 1.0f, -1.0f,  1.0} },
			{ {-1.0f,  1.0f,  1.0} },
			{ {-1.0f,  1.0f, -1.0} },
			{ { 1.0f,  1.0f, -1.0} },
			{ { 1.0f,  1.0f,  1.0} }
		};
	}
	static std::vector<GLuint> indices()
	{
		return
		{
			 0, 1, 2,
			 0, 2, 3,
			 4, 0, 7,
			 7, 0, 3,
			 7, 3, 6,
			 6, 3, 2,
			 6, 2, 5,
			 5, 2, 1,
			 5, 1, 4,
			 4, 1, 0,
			 5, 4, 6,
			 6, 4, 7
		};
	}
};