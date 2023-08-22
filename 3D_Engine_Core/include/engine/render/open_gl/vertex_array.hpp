#pragma once



namespace engine::render
{
	class vertex_buffer;



	class vertex_array
	{
	public:

		vertex_array(const vertex_array&) = delete;
		vertex_array& operator=(const vertex_array&) = delete;

		
		
		explicit vertex_array() noexcept;
		vertex_array(vertex_array&&) = default;
		vertex_array& operator=(vertex_array&&) = default;
		~vertex_array();

		void addBuffer(const vertex_buffer& _buffer) noexcept;
		void bind() const noexcept;
		void unbind() const noexcept;

	private:

		unsigned int m_id_ = 0;
		unsigned int m_amount_buffers_ = 0;

	};
}