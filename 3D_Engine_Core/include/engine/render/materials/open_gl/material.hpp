#pragma once

#include <engine/render/materials/basic_material.hpp>
#include <engine/render/open_gl/texture2D.hpp>

#include <vector>



namespace engine::render::materials::open_gl
{
	using render::open_gl::texture2D;

	class material final: public basic_material 
	{
	public:

		using texture_storage = std::vector<texture2D>;

		material(texture_storage _textures) noexcept;

		void use() const noexcept override;
		void unuse() const noexcept override;

	private:

		texture_storage m_textures;

	};
}