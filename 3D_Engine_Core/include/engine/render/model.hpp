#pragma once

#include <engine/util/nocopyeble.hpp>

#include <engine/render/meshes/open_gl/mesh.hpp>
#include <engine/render/materials/open_gl/material.hpp>

#include <assimp/scene.h>

#include <vector>
#include <memory>
#include <filesystem>



namespace engine::render
{
	using std::filesystem::path;
	using meshes::open_gl::mesh;
	using materials::open_gl::material;
	using render::open_gl::texture2D;

	class model : private util::nocopyeble
	{
	public:

		using material_ptr = std::shared_ptr<material>;
		using mesh_storage = std::vector<mesh>;

		model(const path& _path_to_model) noexcept;

		const mesh_storage& getMeshes() const noexcept;
		const material_ptr& getMaterial() const noexcept;

	private:

		void loadModel(const path& _path_to_model) noexcept;
		void processNode(aiNode* _node, const aiScene* _scene) noexcept;
		mesh prossesMesh(aiMesh* _mesh, const aiScene* _scene) noexcept;
		void prossesMaterial(aiMaterial* _material, const aiScene* _scene) noexcept;
		std::vector<texture2D> loadMaterialTextures(aiMaterial* _material, aiTextureType _texture_type) noexcept;

	private:

		mesh_storage m_meshes;
		material_ptr m_material;

		path m_model_directory;

	};
}