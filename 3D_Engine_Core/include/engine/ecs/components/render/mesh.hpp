#pragma once

#include <engine/ecs/components/basic_component.hpp>

#include <engine/render/fwd/basic_mesh.hpp>

#include <vector>
#include <memory>



namespace engine::ecs::components
{
	class mesh: public virtual basic_component
	{
	public:

		static constexpr std::string_view component_name = "mesh";



		using mesh_ptr_t = std::shared_ptr<render::basic_mesh>;
		using mesh_storage_t = std::vector<mesh_ptr_t>;

		mesh() = default;
		mesh(std::string_view _model_name) noexcept;

		bool setMeshes(std::string_view _model_name) noexcept;

		const mesh_storage_t& getMeshes() const noexcept;

		serialized_view_t serialize() const noexcept override;
		void deserializeFrom(const serialized_view_t& _serialized_view) noexcept override;

	private:

		std::string m_model_name;
		mesh_storage_t m_meshes;

	};
}