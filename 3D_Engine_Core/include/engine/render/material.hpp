#pragma once

#include <engine/render/basic_material.hpp>

#include <engine/render/fwd/basic_texture2D.hpp>

#include <vector>
#include <memory>



namespace engine::render
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