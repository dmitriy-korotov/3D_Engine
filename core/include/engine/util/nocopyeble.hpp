#pragma once



namespace engine::util
{
	class nocopyeble
	{
	public:

		nocopyeble() = default;

		nocopyeble(const nocopyeble&) = delete;
		nocopyeble& operator=(const nocopyeble&) = delete;

	};
}