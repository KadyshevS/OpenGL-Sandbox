#pragma once
#include "../VAO.h"

struct Plane
{
	static std::vector<Vertex> vertices()
	{
		return verticesBuffer;
	}
	static std::vector<GLuint> indices()
	{
		return indicesBuffer;
	}

private:
	static std::vector<Vertex> verticesBuffer;
	static std::vector<GLuint> indicesBuffer;
};

std::vector<Vertex> Plane::verticesBuffer =
{
	{ {-1.0f, 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f } },
	{ {-1.0f, 0.0f,-1.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f } },
	{ { 1.0f, 0.0f,-1.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f } },
	{ { 1.0f, 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } }
};
std::vector<GLuint> Plane::indicesBuffer =
{
	0, 1, 2,
	0, 2, 3
};