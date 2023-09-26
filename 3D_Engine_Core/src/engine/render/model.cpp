#include <engine/render/model.hpp>

#include <engine/logging/log.hpp>

#include <engine/render/image.hpp>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>



namespace engine::render
{
	model::model(const path& _path_to_model) noexcept
	{
		loadModel(_path_to_model);
	}



	const model::mesh_storage& model:: getMeshes() const noexcept
	{
		return m_meshes;
	}



	const model::material_ptr& model::getMaterial() const noexcept
	{
		return m_material;
	}



	void model::loadModel(const path& _path_to_model) noexcept
	{
		Assimp::Importer importer;
		const auto& scene = importer.ReadFile(_path_to_model.generic_string(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
		{
			LOG_ERROR("[Model ERROR] Can't load scene model (path : {0}): {1}", _path_to_model.generic_string(), importer.GetErrorString());
			return;
		}

		m_model_directory = _path_to_model.parent_path();
		
		processNode(scene->mRootNode, scene);
	}



	void model::processNode(aiNode* _node, const aiScene* _scene) noexcept
	{
		for (size_t i = 0; i < _node->mNumMeshes; i++)
		{
			aiMesh* _mesh = _scene->mMeshes[_node->mMeshes[i]];
			m_meshes.push_back(std::move(prossesMesh(_mesh, _scene)));
		}

		for (size_t i = 0; i < _node->mNumChildren; i++)
		{
			processNode(_node->mChildren[i], _scene);
		}
	}



	mesh model::prossesMesh(aiMesh* _mesh, const aiScene* _scene) noexcept
	{
		std::vector<meshes::vertex> vertexes;
		std::vector<unsigned int> indexes;

		for (size_t i = 0; i < _mesh->mNumVertices; i++)
		{
			meshes::vertex vertex;
			glm::vec3 vector;

			vector.x = _mesh->mVertices[i].x;
			vector.y = _mesh->mVertices[i].y;
			vector.z = _mesh->mVertices[i].z;

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

		for (size_t i = 0; i < _mesh->mNumFaces; i++)
		{
			aiFace face = _mesh->mFaces[i];
			for (size_t j = 0; j < face.mNumIndices; i++)
			{
				indexes.push_back(face.mIndices[j]);
			}
		}

		aiMaterial* material = _scene->mMaterials[_mesh->mMaterialIndex];
		prossesMaterial(material, _scene);

		return { std::move(vertexes), std::move(indexes) };
	}



	void model::prossesMaterial(aiMaterial* _material, const aiScene* _scene) noexcept
	{
		std::vector<texture2D> textures;

		auto diffuse_maps = loadMaterialTextures(_material, aiTextureType_DIFFUSE);
		textures.emplace_back(diffuse_maps.begin(), diffuse_maps.end());

		auto specular_maps = loadMaterialTextures(_material, aiTextureType_SPECULAR);
		textures.emplace_back(specular_maps.begin(), specular_maps.end());

		auto normal_maps = loadMaterialTextures(_material, aiTextureType_HEIGHT);
		textures.emplace_back(normal_maps.begin(), normal_maps.end());

		auto ambiend_maps = loadMaterialTextures(_material, aiTextureType_AMBIENT);
		textures.emplace_back(ambiend_maps.begin(), ambiend_maps.end());
	}



	std::vector<texture2D> model::loadMaterialTextures(aiMaterial* _material, aiTextureType _texture_type) noexcept
	{
		std::vector<texture2D> textures;
		for (size_t i = 0; i < _material->GetTextureCount(_texture_type); i++)
		{
			aiString path_to_texture;
			_material->GetTexture(_texture_type, i, &path_to_texture);

			image img(m_model_directory / path_to_texture.C_Str());
			texture2D texture;
			texture.setData(img.getData(), img.getWidth(), img.getHeight());

			textures.push_back(std::move(texture));
		}
		return textures;
	}
}