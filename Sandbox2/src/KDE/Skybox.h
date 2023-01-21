#pragma once
#include <vector>
#include <string>
#include "Shader.h"
#include "Camera.h"

namespace kde
{
	class Skybox
	{
	private:
		Shader shader;
		const std::vector<float> vertices =
		{
			//   Coordinates
			-1.0f, -1.0f,  1.0f,//        7--------6
			 1.0f, -1.0f,  1.0f,//       /|       /|
			 1.0f, -1.0f, -1.0f,//      4--------5 |
			-1.0f, -1.0f, -1.0f,//      | |      | |
			-1.0f,  1.0f,  1.0f,//      | 3------|-2
			 1.0f,  1.0f,  1.0f,//      |/       |/
			 1.0f,  1.0f, -1.0f,//      0--------1
			-1.0f,  1.0f, -1.0f
		};
		const std::vector<unsigned int> indices =
		{
		//  Right
			1, 2, 6,
			6, 5, 1,

		//  Left
			0, 4, 7,
			7, 3, 0,

		//  Top
			4, 5, 6,
			6, 7, 4,

		//  Bottom
			0, 3, 2,
			2, 1, 0,

		//  Back
			0, 1, 5,
			5, 4, 0,

		//  Front
			3, 7, 6,
			6, 2, 3
		};

		unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
		unsigned int cubemapTexture;
	public:
		Skybox(const std::string& path);

		void Draw(Camera cam, const float width, const float height, float FOVdeg, float nearPlane, float farPlane);
	};
}