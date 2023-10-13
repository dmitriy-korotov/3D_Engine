#pragma once

#include <engine/render/basic_texture2D.hpp>

#include <engine/render/open_gl/open_gl.hpp>



namespace engine::render::open_gl
{
	class texture2D: public basic_texture2D
	{
	public:

		explicit texture2D() noexcept;
		~texture2D();

		texture2D(texture2D&& _other) noexcept;
		texture2D& operator=(texture2D&& _right) noexcept;

		void setData(const std::byte* _data, uint16_t _width, uint16_t _height,
				     InternalFormat _internal_format = InternalFormat::RGB_8) noexcept override;
		void setParametrs(const TextureParamsStorage& _texture_params) noexcept override;

		void bind(uint8_t _unit) const noexcept override;

	private:

		GLuint m_id = 0;

	};
}