#pragma once

#include <filesystem>
#include <unordered_set>



namespace engine::render
{
	using std::filesystem::path;

	class shaders_manager
	{
	public:

		using dirs_storage = std::unordered_set<path>;

		static shaders_manager& instance() noexcept;

		void addShadersDirectory(path _directory_path) noexcept;
		void removeShadersDirectory(const path& _directory_path) noexcept;

		const dirs_storage& getShadersDirectories() const noexcept;

	private:

		shaders_manager() = default;

	private:

		 dirs_storage m_shaders_directories;

	};
}