#include <engine/render/shaders_manager.hpp>



namespace engine::render
{
	shaders_manager& shaders_manager::instance() noexcept
	{
		static shaders_manager instance;
		return instance;
	}



	void shaders_manager::addShadersDirectory(path _directory_path) noexcept
	{
		m_shaders_directories.emplace(std::move(_directory_path));
	}



	void shaders_manager::removeShadersDirectory(const path& _directory_path) noexcept
	{
		m_shaders_directories.erase(_directory_path);
	}



	const shaders_manager::dirs_storage& shaders_manager::getShadersDirectories() const noexcept
	{
		return m_shaders_directories;
	}
}