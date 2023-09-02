#pragma once



namespace engine::util
{
	class nomoveble
	{
	public:

		nomoveble(nomoveble&&) = delete;
		nomoveble& operator=(nomoveble&&) = delete;

	};
}