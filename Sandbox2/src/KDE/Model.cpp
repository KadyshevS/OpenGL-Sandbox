#include "Model.h"
#include "ImguiManager.h"
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
		//	Test input file path
			std::ifstream fileTest(fileName);
			if (!fileTest.is_open()) throw std::runtime_error("");

		//	Parse object by Assimp
			Assimp::Importer imp;
			const auto pModel = imp.ReadFile(fileName, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
			
		//	Clear meshes array if it's not
			aiMeshes.clear();
			aiMeshes.reserve(pModel->mNumMeshes);

			for (unsigned int i = 0; i < pModel->mNumMeshes; i++)
			{
			//	Getting current mesh
				const auto& currMesh = pModel->mMeshes[i];
				const auto& currMatIndex = currMesh->mMaterialIndex;
				
			//	Creating std::vector for each data type
				std::vector<Vertex> currVerts;
				std::vector<unsigned int> currIndices;
				std::vector<kde::Texture> currTextures;

				currIndices.reserve(currMesh->mNumFaces * 3);
				for (unsigned int j = 0; j < currMesh->mNumFaces; j++)
				{
					const auto& face = currMesh->mFaces[j];
					assert(face.mNumIndices == 3 && "Face of model is not a triangle.");
					currIndices.push_back(face.mIndices[0]);
					currIndices.push_back(face.mIndices[1]);
					currIndices.push_back(face.mIndices[2]);
				}

				currVerts.reserve(currMesh->mNumVertices);
				for (unsigned int j = 0; j < currMesh->mNumVertices; j++)
				{
					currVerts.emplace_back(
							glm::vec3(currMesh->mVertices[j].x * scale, currMesh->mVertices[j].y * scale, currMesh->mVertices[j].z * scale),
							glm::vec3(0.0f, 1.0f, 0.0f),
							glm::vec3(currMesh->mNormals[j].x, currMesh->mNormals[j].y, currMesh->mNormals[j].z),
							currMesh->HasTextureCoords(0) ? glm::vec2(currMesh->mTextureCoords[0][j].x, currMesh->mTextureCoords[0][j].y) : glm::vec2(0.0f, 0.0f)
					);
				}

				currTextures.reserve(2);
				auto material = pModel->mMaterials[currMesh->mMaterialIndex];
				aiString materialName;
				material->Get(AI_MATKEY_NAME, materialName);

				int numDiffuse = material->GetTextureCount(aiTextureType_DIFFUSE);
				int numSpecular = material->GetTextureCount(aiTextureType_SPECULAR);
				aiString aiDiffuseName;
				aiString aiSpecularName;
				std::string diffuseName;
				std::string specularName;

				if (numDiffuse > 0)
				{
					material->Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), aiDiffuseName);
					diffuseName = fileName.substr(0, fileName.find_last_of("\\")) + "\\" + aiDiffuseName.data;
				}
				if (numSpecular > 0)
				{
					material->Get(AI_MATKEY_TEXTURE(aiTextureType_SPECULAR, 0), aiSpecularName);
					specularName = fileName.substr(0, fileName.find_last_of("\\")) + "\\" + aiSpecularName.data;
				}
				
				std::string fileType = diffuseName.substr( diffuseName.find_last_of("."), diffuseName.length() );

				if(fileType == ".png")
					currTextures.emplace_back(diffuseName, "diffuse", GL_RGBA);
				else if(fileType == ".jpg")
					currTextures.emplace_back(diffuseName, "diffuse", GL_RGB);

				currTextures.emplace_back(specularName, "specular", GL_RED);

				aiMeshes.emplace_back(currVerts, currIndices, currTextures, currMesh->mName.C_Str());
			}
		}
		catch (std::runtime_error e)
		{
			std::cout << "Failed to load model." << std::endl;
			return false;
		}
		
		return true;
	}
	void Model::Draw(Shader& shader, Camera& camera, PointLight& light)
	{
		for (auto& m : aiMeshes)
		{
			m.Draw(shader, camera, light.position, light.color);
		}
	}
	void Model::DrawOutline(Shader& shader, Camera& cam, PointLight& light, float outlining, glm::vec3 outlineColor)
	{
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);

		Draw(shader, cam, light);

		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilMask(0x00);
		glDisable(GL_DEPTH_TEST);
		outlineShader.Use();
		glUniform1f(glGetUniformLocation(outlineShader.mProgram, "outlining"), (outlining * 0.01f));
		glUniform3f(glGetUniformLocation(outlineShader.mProgram, "outlineColor"), outlineColor.x, outlineColor.y, outlineColor.z);
		Draw(outlineShader, cam, light);

		glStencilMask(0xFF);
		glStencilFunc(GL_ALWAYS, 0, 0xFF);
		glEnable(GL_DEPTH_TEST);
	}

	void Model::DrawWindow()
	{
		for (auto& m : aiMeshes)
		{
			m.DrawWindow();
		}
	}
}