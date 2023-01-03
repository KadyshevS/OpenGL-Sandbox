#include "Model.h"
#include <vector>

namespace kde
{
	Model::Model(const std::string& fileName, const float scale)
		:
		fileName(fileName)
	{
		LoadMesh(fileName, scale);
	}

	bool Model::LoadMesh(const std::string& fileName, const float scale)
	{
		try
		{
			std::string filePath = "res\\models\\" + fileName + "\\" + fileName + ".obj";

			Assimp::Importer imp;
			const auto pModel = imp.ReadFile(filePath, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
			const auto pMesh = pModel->mMeshes[0];
			
			pModel->mMeshes[0]->mName;

			vertices.reserve(pMesh->mNumVertices);
			for (unsigned int i = 0; i < pMesh->mNumVertices; i++)
			{
				vertices.push_back( 
					{
						glm::vec3(pMesh->mVertices[i].x*scale, pMesh->mVertices[i].y*scale, pMesh->mVertices[i].z*scale),
						glm::vec3(1.0f, 1.0f, 1.0f),
						glm::vec3(pMesh->mNormals[i].x, pMesh->mNormals[i].y, pMesh->mNormals[i].z)
					}
				);
			}
			
			indices.reserve(pMesh->mNumFaces * 3);
			for (unsigned int i = 0; i < pMesh->mNumFaces; i++)
			{
				const auto& face = pMesh->mFaces[i];
				assert(face.mNumIndices == 3 && "Face of model is not a triangle.");
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
	void Model::Draw(Shader& shader, Camera& camera, PointLight& light)
	{
		glm::mat4 modelMat(1.0f);
		
		auto t = glm::translate(glm::mat4(1.0f), position);
		auto s = glm::scale(glm::mat4(1.0f), scale);
		auto r = 
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		modelMat = t * r * s;
		
		shader.Use();
		glUniformMatrix4fv(glGetUniformLocation(shader.mProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMat));
		glUniform4f(glGetUniformLocation(shader.mProgram, "lightColor"), light.color.x, light.color.y, light.color.z, 1.0f);
		glUniform3f(glGetUniformLocation(shader.mProgram, "lightPos"), light.position.x, light.position.y, light.position.z);

		vao.Bind();

		glUniform3f(glGetUniformLocation(shader.mProgram, "camPos"), camera.position.x, camera.position.y, camera.position.z);
		camera.Matrix(shader, "camMatrix");

		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	}

	std::vector<Vertex> Model::getVertices() const
	{
		return vertices;
	}
	std::vector<unsigned int> Model::getIndices() const
	{
		return indices;
	}
	void Model::setPosition(const glm::vec3& translation)
	{
		position = translation;
	}
	void Model::setScale(const glm::vec3& scaling)
	{
		scale = scaling;
	}
	void Model::DrawSettings()
	{
		if( ImGui::Begin(fileName.c_str()) )
		{
			ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Position");
			ImGui::SliderFloat("X", &position.x, -1.0f, 1.0f, "%.1f");
			ImGui::SliderFloat("Y", &position.y, -1.0f, 1.0f, "%.1f");
			ImGui::SliderFloat("Z", &position.z, -1.0f, 1.0f, "%.1f");
			ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Scale");
			ImGui::SliderFloat("X ", &scale.x, 0.5f, 3.0f, "%.1f");
			ImGui::SliderFloat("Y ", &scale.y, 0.5f, 3.0f, "%.1f");
			ImGui::SliderFloat("Z ", &scale.z, 0.5f, 3.0f, "%.1f");
			ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Rotation");
			ImGui::SliderFloat("X  ", &rotation.x, -180.0f, 180.0f);
			ImGui::SliderFloat("Y  ", &rotation.y, -180.0f, 180.0f);
			ImGui::SliderFloat("Z  ", &rotation.z, -180.0f, 180.0f);
			
			if ( ImGui::Button("Clear") )
			{
				position = { 0.0f, 0.0f, 0.0f };
				scale = { 1.0f, 1.0f, 1.0f };
				rotation = { 0.0f, 0.0f, 0.0f };
			}
		}
		ImGui::End();
	}
}