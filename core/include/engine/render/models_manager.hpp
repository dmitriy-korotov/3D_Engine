#pragma once

#include <engine/util/nocopyeble.hpp>

#include <engine/util/file_searcher.hpp>

#include <engine/render/model.hpp>

#include <unordered_map>
#include <filesystem>
#include <string>
#include <memory>



namespace engine::render
{
	using std::filesystem::path;

	class models_manager: private util::nocopyeble
	{
	public:

		using dirs_storage_t = util::file_searcher::dirs_storage_t;
		using model_ptr_t = std::shared_ptr<model>;
		using models_storaget_t = std::unordered_map<std::string, std::pair<model_ptr_t, path>>;



		bool addModelsDirectory(path _directory_path) noexcept;
		bool removeModelsDirectory(const path& _directory_path) noexcept;

		model_ptr_t loadModel(std::string_view _model_name, const path& _path_to_model) noexcept;

		[[nodiscard]] model_ptr_t getModel(std::string_view _model_name) const noexcept;
		bool deleleModel(std::string_view _model_name) noexcept;

		const dirs_storage_t& getModelsDirectories() const noexcept;

		std::optional<path> getModelLocation(std::string_view _model_name) const noexcept;

	protected:

		models_manager() = default;

		static models_manager& instance() noexcept;

	private:

		std::optional<path> searchModelFile(const path& _path_to_model) const noexcept;

	private:

		util::file_searcher m_file_searcher;

		models_storaget_t m_models;

	};
}