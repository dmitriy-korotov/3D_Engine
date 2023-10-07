#pragma once

#include <engine/render/util/basic_models_loader.hpp>



enum aiTextureType;
struct aiMesh;
struct aiMaterial;
struct aiScene;
struct aiNode;

namespace engine::render::utility
{
	class models_loader final: public basic_models_loader
	{
	public:

		using texture_cache = std::unordered_map<std::string, std::shared_ptr<basic_texture2D>>;

		void load(const path& _path_to_model) noexcept override;

	private:

		void processNode(aiNode* _node, const aiScene* _scene) noexcept;
		void prossesMesh(aiMesh* _mesh, const aiScene* _scene) noexcept;
		void prossesMaterial(aiMaterial* _material) noexcept;
		void loadMaterialTextures(aiMaterial* _material, aiTextureType _texture_type, texture_storage& _textures) noexcept;

	private:

		texture_cache m_cached_textures;

	};
}