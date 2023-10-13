#include <engine/render/util/models_loader.hpp>

#include <engine/logging/log.hpp>

#include <engine/util/image.hpp>
#include <engine/render/open_gl/mesh.hpp>
#include <engine/render/material.hpp>
#include <engine/render/open_gl/texture2D.hpp>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>



namespace engine::render::utility
{
	void models_loader::load(const path& _path_to_model) noexcept
	{
		Assimp::Importer importer;
		const auto& scene = importer.ReadFile(_path_to_model.generic_string(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			LOG_ERROR("[Models loader ERROR] Can't load scene model (path : {0}): {1}", _path_to_model.generic_string(), importer.GetErrorString());
			return;
		}

		m_model_directory = _path_to_model.parent_path();

		processNode(scene->mRootNode, scene);

		m_is_loaded = true;
	}



	void models_loader::processNode(aiNode* _node, const aiScene* _scene) noexcept
	{
		for (size_t i = 0; i < _node->mNumMeshes; i++)
		{
			aiMesh* _mesh = _scene->mMeshes[_node->mMeshes[i]];
			prossesMesh(_mesh, _scene);
		}

		for (size_t i = 0; i < _node->mNumChildren; i++)
		{
			processNode(_node->mChildren[i], _scene);
		}
	}



	void models_loader::prossesMesh(aiMesh* _mesh, const aiScene* _scene) noexcept
	{
		std::vector<vertex> vertexes;
		vertexes.reserve(_mesh->mNumVertices);
		std::vector<unsigned int> indexes;
		indexes.reserve(_mesh->mNumFaces * 3);



		float max_abs = 0;
		for (size_t i = 0; i < _mesh->mNumVertices; i++)
		{
			vertex vertex;
			glm::vec3 vector;

			vector.x = _mesh->mVertices[i].x;
			vector.y = _mesh->mVertices[i].y;
			vector.z = _mesh->mVertices[i].z;

			if (std::abs(vector.x) > max_abs)
			{
				max_abs = std::abs(vector.x);
			}
			if (std::abs(vector.y) > max_abs)
			{
				max_abs = std::abs(vector.y);
			}
			if (std::abs(vector.z) > max_abs)
			{
				max_abs = std::abs(vector.z);
			}

			vertex.position = vector;

			if (_mesh->HasNormals())
			{
				vector.x = _mesh->mNormals[i].x;
				vector.y = _mesh->mNormals[i].y;
				vector.z = _mesh->mNormals[i].z;

				vertex.normal = vector;
			}

			glm::vec2 tex_coords(0.f);
			if (_mesh->mTextureCoords[0])
			{
				tex_coords.x = _mesh->mTextureCoords[0][i].x;
				tex_coords.y = _mesh->mTextureCoords[0][i].y;
			}
			vertex.tex_coord = tex_coords;

			vertexes.push_back(vertex);
		}

		for (size_t i = 0; i < vertexes.size(); i++)
		{
			//vertexes[i].position /= max_abs;
		}

		for (size_t i = 0; i < _mesh->mNumFaces; i++)
		{
			aiFace& face = _mesh->mFaces[i];
			for (size_t j = 0; j < face.mNumIndices; j++)
			{
				indexes.push_back(face.mIndices[j]);
			}
		}

		aiMaterial* material = _scene->mMaterials[_mesh->mMaterialIndex];
		prossesMaterial(material);

		m_meshes.emplace_back(std::make_shared<open_gl::mesh>(std::move(vertexes), std::move(indexes)));
	}



	void models_loader::prossesMaterial(aiMaterial* _material) noexcept
	{
		texture_storage textures;

		loadMaterialTextures(_material, aiTextureType_DIFFUSE, textures);
		loadMaterialTextures(_material, aiTextureType_SPECULAR, textures);
		loadMaterialTextures(_material, aiTextureType_HEIGHT, textures);
		loadMaterialTextures(_material, aiTextureType_AMBIENT, textures);

		m_material = std::make_shared<material>(std::move(textures));
	}



	void models_loader::loadMaterialTextures(aiMaterial* _material, aiTextureType _texture_type, texture_storage& _textures) noexcept
	{
		for (size_t i = 0; i < _material->GetTextureCount(_texture_type); i++)
		{
			aiString path_to_texture;
			_material->GetTexture(_texture_type, i, &path_to_texture);

			auto finded_texture = m_cached_textures.find(path_to_texture.C_Str());
			if (finded_texture != m_cached_textures.end())
			{
				_textures.push_back(finded_texture->second);
				continue;
			}

			util::image img(m_model_directory / path_to_texture.C_Str());
			auto texture = std::make_shared<open_gl::texture2D>();
			texture->setData(img.getData(), img.getWidth(), img.getHeight());

			m_cached_textures.emplace(path_to_texture.C_Str(), texture);
			_textures.emplace_back(std::move(texture));
		}
	}
}