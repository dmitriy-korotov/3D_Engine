#include <engine/render/material.hpp>

#include <engine/render/basic_texture2D.hpp>



namespace engine::render
{
	material::material(texture_map _textures) noexcept
			: m_textures(std::move(_textures))
	{ }



	material::texture_ptr material::getTexture(TextureMap _texture_map_type) const noexcept
	{
		auto texture = m_textures.find(_texture_map_type);
		if (texture != m_textures.end())
			return texture->second;
		return nullptr;
	}



	bool material::isEmpty() const noexcept
	{
		return m_textures.empty();
	}
}