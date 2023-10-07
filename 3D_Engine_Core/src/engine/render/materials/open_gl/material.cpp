#include <engine/render/materials/open_gl/material.hpp>

#include <engine/render/basic_texture2D.hpp>



namespace engine::render::materials::open_gl
{
	material::material(texture_storage _textures) noexcept
			: m_textures(std::move(_textures))
	{ }



	void material::use() const noexcept
	{
		size_t unit = 0;
		for (const auto& texture : m_textures)
		{
			texture->bind(unit++);
		}
	}



	void material::unuse() const noexcept
	{ }
}