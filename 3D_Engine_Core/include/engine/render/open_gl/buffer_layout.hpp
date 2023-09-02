#pragma once

#include <vector>



namespace engine::render::open_gl
{
	enum class ShaderDataType : uint8_t
	{
		Float,
		Float2,
		Float3,
		Float4,

		Int,
		Int2,
		Int3,
		Int4
	};



	struct buffer_element
	{
		ShaderDataType shader_data_type;
		uint32_t components_type;
		size_t components_count;
		size_t offset;
		size_t size;

		buffer_element(ShaderDataType _shader_data_type) noexcept;
	};



	class buffer_layout
	{
	public:

		buffer_layout(std::initializer_list<buffer_element> _buffer_elements) noexcept;

		const std::vector<buffer_element>& getElements() const noexcept;
		size_t getStride() const noexcept;

	private:

		std::vector<buffer_element> m_buffer_elements_;
		size_t m_stride = 0;

	};
}