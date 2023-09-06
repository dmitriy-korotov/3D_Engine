#pragma once

#include <engine/render/open_gl/gl_types.hpp>

#include <stdint.h>



namespace engine::render::open_gl
{
	class texture2D
	{
	public:

		explicit texture2D() noexcept;
		~texture2D();

		void setTextureData(const uint8_t* _data, uint16_t _width, uint16_t _height) noexcept;

		void bindTexture(uint8_t _target) noexcept;

	private:

		GLuint m_texture_id = 0;

		uint16_t m_width = 0;
		uint16_t m_height = 0;

	};
}