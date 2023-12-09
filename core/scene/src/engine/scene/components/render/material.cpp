#include <engine/scene/components/render/material.hpp>

#include <engine/logging/log.hpp>

#include <engine/render/material.hpp>

#include <engine/resource_manager.hpp>

#include <cassert>



namespace engine::scene::components
{
	material::material(std::string_view _material_name) noexcept
			: m_material_name(_material_name)
	{ 
		setMaterial(_material_name);
	}



	auto material::setMaterial(std::string_view _material_name) noexcept -> bool
	{
		m_material_name = _material_name;

		auto model = GetResourceManager().getModelsManager().getModel(m_material_name);
		if (model == nullptr)
		{
			LOG_ERROR("[Material component ERROR] Can't find material with this name: {0}", m_material_name);
			disable();
			return false;
		}

		if (!model->hasMaterial())
		{
			LOG_WARN("[Material component WARN] Material with this name is empty: {0}", m_material_name);
			disable();
			return false;
		}

		m_material = std::move(*model).getMaterial();

		enable();

		return true;
	}



	auto material::getMaterial() const noexcept -> const material_ptr_t&
	{ 
		assert(m_material != nullptr);
		return m_material;
	}



	auto material::serialize() const noexcept -> serialized_view_t
	{
		serialized_view_t serialized_view = scene_component::serialize();

		serialized_view["component_name"] = component_name;
		serialized_view["material_name"] = m_material_name;

		return serialized_view;
	}



	auto material::deserializeFrom(const serialized_view_t& _serialized_view) noexcept -> void
	{
		scene_component::deserializeFrom(_serialized_view);

		setMaterial(_serialized_view.at("material_name"));
	}
}