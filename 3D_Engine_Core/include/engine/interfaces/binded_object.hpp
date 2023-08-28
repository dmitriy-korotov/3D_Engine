#pragma once



namespace engine
{
	class binded_object
	{
	public:

		virtual ~binded_object() {}

		virtual void bind() const noexcept = delete;
		virtual void unbind() const noexcept = delete;

	};
}