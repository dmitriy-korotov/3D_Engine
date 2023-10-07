#pragma once

#include <engine/render/materials/basic_material.hpp>

#include <vector>
#include <memory>



namespace engine::render
{
	class basic_texture2D;
}

namespace engine::render::materials::open_gl
{
	class material final: public basic_material 
	{
	public:

		using texture_storage = std::vector<std::shared_ptr<basic_texture2D>>;

		material(texture_storage _textures) noexcept;

		void use() const noexcept override;
		void unuse() const noexcept override;

	private:

		texture_storage m_textures;

	};
}