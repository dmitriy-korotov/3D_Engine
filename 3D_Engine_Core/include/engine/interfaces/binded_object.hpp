#pragma once



namespace engine
{
	class binded_object
	{
	public:

		virtual ~binded_object(){}

		virtual void bind() const noexcept = 0;
		virtual void unbind() const noexcept = 0;

	};
}