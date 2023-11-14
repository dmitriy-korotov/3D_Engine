#include <engine/ecs/components/render/mesh.hpp>

#include <engine/logging/log.hpp>

#include <engine/render/basic_mesh.hpp>

#include <engine/resource_manager.hpp>



namespace engine::ecs::components
{
	mesh::mesh(std::string_view _model_name) noexcept
			: m_model_name(_model_name)
	{
		setMeshes(_model_name);
	}



	bool mesh::setMeshes(std::string_view _model_name) noexcept
	{
		m_model_name = _model_name;

		auto model = GetResourceManager().getModel(_model_name);
		if (model == nullptr)
		{
			LOG_ERROR("[Meshes component ERROR] Can't find model with this name: {0}", m_model_name);
			disable();
			return false;
		}

		m_meshes = std::move(*model).getMeshes();

		enable();

		return true;
	}



	const mesh::mesh_storage_t& mesh::getMeshes() const noexcept
	{
		return m_meshes;
	}



	auto mesh::serialize() const noexcept -> serialized_view_t
	{
		auto serialized_view = basic_component::serialize();

		serialized_view["component_name"] = component_name;
		serialized_view["model_name"] = m_model_name;

		return serialized_view;
	}



	void mesh::deserializeFrom(const serialized_view_t& _serialized_view) noexcept
	{
		basic_component::deserializeFrom(_serialized_view);

		setMeshes(_serialized_view.at("model_name"));
	}
}