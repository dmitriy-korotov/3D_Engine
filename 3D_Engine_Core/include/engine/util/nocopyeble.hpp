#pragma once



namespace engine::util
{
	class nocopyeble
	{
	public:
		nocopyeble(const nocopyeble&) = delete;
		nocopyeble& operator=(const nocopyeble&) = delete;
	};
}