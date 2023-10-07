#pragma once

#include <engine/util/nocopyeble.hpp>

#include <vector>
#include <memory>
#include <unordered_map>
#include <filesystem>



namespace engine::render::meshes
{
	class basic_mesh;
}

namespace engine::render::materials
{
	class basic_material;
}

namespace engine::render
{
	class basic_texure2D;
}

namespace engine::render::utility
{
	using std::filesystem::path;

	class basic_models_loader: private util::nocopyeble
	{
	public:

		using mesh_ptr = std::shared_ptr<render::meshes::basic_mesh>;
		using material_ptr = std::shared_ptr<render::materials::basic_material>;
		using texture_ptr = std::shared_ptr<basic_texure2D>;
		using mesh_storage = std::vector<mesh_ptr>;
		using texture_storage = std::vector<texture_ptr>;



		basic_models_loader() = default;
		virtual ~basic_models_loader() = default;

		virtual void load(const path& _path_to_model) noexcept = 0;

		mesh_storage& getMeshes() noexcept;
		material_ptr& getMaterial() noexcept;

		bool isLoaded() const noexcept;

	protected:

		bool m_is_loaded = false;

		path m_model_directory;

		mesh_storage m_meshes;
		material_ptr m_material;

	};
}