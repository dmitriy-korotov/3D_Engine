#pragma once

#include <engine/util/nocopyeble.hpp>

#include <engine/render/fwd/basic_texture2D.hpp>
#include <engine/render/fwd/material.hpp>
#include <engine/render/fwd/basic_mesh.hpp>

#include <map>
#include <vector>
#include <memory>
#include <unordered_map>
#include <filesystem>



namespace engine::render::utility
{
	using std::filesystem::path;

	class basic_models_loader: private util::nocopyeble
	{
	public:

		using mesh_ptr = std::shared_ptr<render::basic_mesh>;
		using material_ptr = std::shared_ptr<render::material>;
		using texture_ptr = std::shared_ptr<basic_texture2D>;
		using mesh_storage = std::vector<mesh_ptr>;
		using texture_map = std::map<TextureMap, texture_ptr>;



		basic_models_loader() = default;
		virtual ~basic_models_loader() = default;

		virtual void load(const path& _path_to_model) noexcept = 0;

		mesh_storage& getMeshes() noexcept;
		material_ptr& getMaterial() noexcept;

		bool isLoaded() const noexcept;
		bool hasMaterial() const noexcept;

	protected:

		bool m_is_loaded = false;

		path m_model_directory;

		mesh_storage m_meshes;
		material_ptr m_material = nullptr;

	};
}