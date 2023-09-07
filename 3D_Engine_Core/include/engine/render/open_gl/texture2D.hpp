#pragma once

#include <engine/render/open_gl/gl_types.hpp>
#include <engine/render/texture_parametrs.hpp>

#include <stdint.h>



namespace engine::render::open_gl
{
	class texture2D
	{
	public:

		explicit texture2D() noexcept;
		~texture2D();

		uint16_t getWidth() const noexcept;
		uint16_t getHeight() const noexcept;

		void setTextureData(const uint8_t* _data, uint16_t _width, uint16_t _height,
						    InternalFormat _internal_format = InternalFormat::RGB_8) noexcept;
		void setTextureParams(const TextureParamsStorage& _texture_params) noexcept;
		void bindTexture(uint8_t _target) const noexcept;

	private:

		GLuint m_texture_id = 0;

		uint16_t m_width = 0;
		uint16_t m_height = 0;

	};
}