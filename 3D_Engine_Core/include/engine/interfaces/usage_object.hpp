#pragma once



namespace engine::interfaces
{
	class usage_object
	{
	public:

		virtual ~usage_object() = default;

		virtual void use() const noexcept = 0;
		virtual void unuse() const noexcept = 0;

	};
}