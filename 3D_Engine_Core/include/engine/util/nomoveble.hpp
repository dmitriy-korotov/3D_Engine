#pragma once



namespace engine::util
{
	class nomoveble
	{
	public:

		nomoveble() = default;

		nomoveble(nomoveble&&) = delete;
		nomoveble& operator=(nomoveble&&) = delete;

	};
}