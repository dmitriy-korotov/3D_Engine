#pragma once

#include <engine/util/nocopyeble.hpp>

#include <engine/render/fwd/basic_texture2D.hpp>

#include <map>
#include <memory>



namespace engine::render
{
	enum class TextureMap : uint8_t
	{
		Ambient,
		Diffuse,
		Specular,
		Normal,
		Unknown
	};

	class material
	{
	public:

		using texture_ptr = std::shared_ptr<basic_texture2D>;
		using texture_map = std::map<TextureMap, texture_ptr>;

		material(texture_map _textures) noexcept;

		[[nodiscard]] texture_ptr getTexture(TextureMap _texture_map_type) const noexcept;

	private:

		texture_map m_textures;

	};
}