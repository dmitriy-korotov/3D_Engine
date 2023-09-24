#pragma once



namespace engine::window::glfw
{
	class glfw
	{
	public:

		static glfw& instance() noexcept;

		glfw();
		~glfw();

		bool isInited() const noexcept;

	private:

		bool m_is_inited = false;

	};
}