#include <engine/render/model.hpp>

#include <engine/logging/log.hpp>

#include <engine/render/image.hpp>

#include <engine/render/meshes/open_gl/mesh.hpp>

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
			prossesMesh(_mesh, _scene);
		}

		for (size_t i = 0; i < _node->mNumChildren; i++)
		{
			processNode(_node->mChildren[i], _scene);
		}
	}



	void model::prossesMesh(aiMesh* _mesh, const aiScene* _scene) noexcept
	{
		std::vector<meshes::vertex> vertexes;
		std::vector<unsigned int> indexes;

		float max_abs = 0;
		for (size_t i = 0; i < _mesh->mNumVertices; i++)
		{
			meshes::vertex vertex;
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
			aiFace face = _mesh->mFaces[i];
			for (size_t j = 0; j < face.mNumIndices; j++)
			{
				indexes.push_back(face.mIndices[j]);
			}
		}

		aiMaterial* material = _scene->mMaterials[_mesh->mMaterialIndex];
		prossesMaterial(material, _scene);

		m_meshes.emplace_back(std::make_shared<meshes::open_gl::mesh>(std::move(vertexes), std::move(indexes)));
	}



	void model::prossesMaterial(aiMaterial* _material, const aiScene* _scene) noexcept
	{
		std::vector<texture2D> textures;

		loadMaterialTextures(_material, aiTextureType_DIFFUSE, textures);
		loadMaterialTextures(_material, aiTextureType_SPECULAR, textures);
		loadMaterialTextures(_material, aiTextureType_HEIGHT, textures);
		loadMaterialTextures(_material, aiTextureType_AMBIENT, textures);
		
		m_material = std::make_shared<material>(std::move(textures));
	}



	void model::loadMaterialTextures(aiMaterial* _material, aiTextureType _texture_type, std::vector<texture2D>& _textures) noexcept
	{
		std::vector<texture2D> textures;
		for (size_t i = 0; i < _material->GetTextureCount(_texture_type); i++)
		{
			aiString path_to_texture;
			_material->GetTexture(_texture_type, i, &path_to_texture);

			auto finded_texture = m_loaded_textures.find(path_to_texture.C_Str());
			if (finded_texture != m_loaded_textures.end())
			{
				texture2D texture;
				texture.setData(finded_texture->second.getData(), finded_texture->second.getWidth(), finded_texture->second.getHeight());
				_textures.push_back(std::move(texture));
				continue;
			}

			image img(m_model_directory / path_to_texture.C_Str());
			texture2D texture;
			texture.setData(img.getData(), img.getWidth(), img.getHeight());

			m_loaded_textures.emplace(path_to_texture.C_Str(), std::move(img));
			_textures.push_back(std::move(texture));
		}
	}
}