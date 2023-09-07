#pragma once

#include <engine/util/nocopyeble.hpp>

#include <engine/render/open_gl/gl_types.hpp>
#include <engine/render/texture_parametrs.hpp>

#include <stdint.h>



namespace engine::render::open_gl
{
	class texture2D : util::nocopyeble
	{
	public:

		explicit texture2D() noexcept;
		~texture2D();

		texture2D(texture2D&& _other) noexcept;
		texture2D& operator=(texture2D&& _right) noexcept;

		uint16_t getWidth() const noexcept;
		uint16_t getHeight() const noexcept;

		void setData(const uint8_t* _data, uint16_t _width, uint16_t _height,
				     InternalFormat _internal_format = InternalFormat::RGB_8) noexcept;
		void setParametrs(const TextureParamsStorage& _texture_params) noexcept;
		void bind(uint8_t _unit) const noexcept;

	private:

		GLuint m_id = 0;

		uint16_t m_width = 0;
		uint16_t m_height = 0;

	};
}