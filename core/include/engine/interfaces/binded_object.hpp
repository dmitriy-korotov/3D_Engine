#pragma once



namespace engine::interfaces
{
	class binded_object
	{
	public:

		virtual ~binded_object() = default;

		virtual void bind() const noexcept = 0;
		virtual void unbind() const noexcept = 0;

	};
}