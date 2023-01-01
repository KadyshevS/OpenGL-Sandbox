#include "Model.h"
#include <vector>

namespace kde
{
	Model::Model()
	{
	}
	Model::~Model()
	{
	}

	bool Model::LoadMesh(const std::string& fileName, const float scale)
	{
		try
		{
			std::string filePath = "res\\models\\suzanne.obj";

			Assimp::Importer imp;
			const auto pModel = imp.ReadFile(filePath, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
			const auto pMesh = pModel->mMeshes[0];

			vertices.reserve(pMesh->mNumVertices);
			for (unsigned int i = 0; i < pMesh->mNumVertices; i++)
			{
				vertices.push_back( 
					{
						glm::vec3(pMesh->mVertices[i].x*scale, pMesh->mVertices[i].y*scale, pMesh->mVertices[i].z*scale),
						glm::vec3(0.0f, 1.0f, 0.0f),
						glm::vec3(pMesh->mNormals[i].x, pMesh->mNormals[i].y, pMesh->mNormals[i].z)
					}
				);
			}
			
			indices.reserve(pMesh->mNumFaces * 3);
			for (unsigned int i = 0; i < pMesh->mNumFaces; i++)
			{
				const auto& face = pMesh->mFaces[i];
				assert(face.mNumIndices == 3 && "Face of model is not a trinagle.");
				indices.push_back(face.mIndices[0]);
				indices.push_back(face.mIndices[1]);
				indices.push_back(face.mIndices[2]);
			}

			vao.Bind();

			kde::VBO vbo(vertices);
			kde::EBO ebo(indices);

			vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
			vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
			vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
			vao.LinkAttrib(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));

			vao.Unbind();
			vbo.Unbind();
			ebo.Unbind();
		}
		catch (...)
		{
			std::cout << "Failed to load model." << std::endl;
			return false;
		}
		
		return true;
	}
	void Model::Draw(Shader& shader, Camera& camera)
	{
		// Bind shader to be able to access uniforms
		shader.Use();
		vao.Bind();

		// Take care of the camera Matrix
		glUniform3f(glGetUniformLocation(shader.mProgram, "camPos"), camera.position.x, camera.position.y, camera.position.z);
		camera.Matrix(shader, "camMatrix");

		// Draw the actual mesh
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	}
	void Model::Draw(Shader& shader, Camera& camera, glm::vec3& lightPos, glm::vec4& lightColor)
	{
		// Bind shader to be able to access uniforms
		shader.Use();
		glUniformMatrix4fv(glGetUniformLocation(shader.mProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMat));
		glUniform4f(glGetUniformLocation(shader.mProgram, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		glUniform3f(glGetUniformLocation(shader.mProgram, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

		vao.Bind();

		// Take care of the camera Matrix
		glUniform3f(glGetUniformLocation(shader.mProgram, "camPos"), camera.position.x, camera.position.y, camera.position.z);
		camera.Matrix(shader, "camMatrix");

		// Draw the actual mesh
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	}
}