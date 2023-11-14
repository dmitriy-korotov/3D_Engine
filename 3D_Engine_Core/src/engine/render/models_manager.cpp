#include <engine/render/models_manager.hpp>

#include <engine/logging/log.hpp>

#include <engine/render/util/models_loader.hpp>



namespace engine::render
{
	auto models_manager::instance() noexcept -> models_manager&
	{
		static models_manager instance;
		return instance;
	}



	auto models_manager::addModelsDirectory(path _directory_path) noexcept -> bool
	{
		return m_file_searcher.addSearchDirectory(std::move(_directory_path));
	}



	auto models_manager::removeModelsDirectory(const path& _directory_path) noexcept -> bool
	{
		return m_file_searcher.removeSearchDirectory(_directory_path);
	}



	std::optional<path> models_manager::searchModelFile(const path& _path_to_model) const noexcept
	{
		return m_file_searcher.searchFile(_path_to_model);
	}



	auto models_manager::loadModel(std::string_view _model_name, const path& _path_to_model) noexcept -> model_ptr_t
	{
		auto exists_model = getModel(_model_name);
		if (exists_model != nullptr)
			return exists_model;



		path path_to_model;

		if (std::filesystem::exists(_path_to_model))
		{
			path_to_model = _path_to_model;
		}
		else
		{
			auto path_to_model_opt = searchModelFile(_path_to_model);
			if (!path_to_model_opt.has_value())
			{
				LOG_ERROR("[Models manager ERROR] Can't find model file with this filename: '{0}'", _path_to_model.generic_string());
				return nullptr;
			}
			path_to_model = std::move(path_to_model_opt.value());
		}


		utility::models_loader loader;
		loader.load(path_to_model);

		if (!loader.isLoaded())
		{
			LOG_ERROR("[Models manager ERROR] Can't load model file with this filename: '{0}'", _path_to_model.generic_string());
			return nullptr;
		}

		auto meshes = std::move(loader).getMeshes();
		auto material = std::move(loader).getMaterial();

		auto model = std::make_shared<render::model>(std::move(meshes), std::move(material));

		if (!m_models.emplace(_model_name, std::make_pair(model, _path_to_model)).second)
			LOG_WARN("[Models manager WARN] Model with this name is not saved: '{0}'", _model_name);

		return model;
	}



	auto models_manager::getModel(std::string_view _model_name) const noexcept -> model_ptr_t
	{
		auto finded_model = m_models.find(_model_name.data());
		if (finded_model == m_models.end())
			return nullptr;
		return finded_model->second.first;
	}



	std::optional<path> models_manager::getModelLocation(std::string_view _model_name) const noexcept
	{
		auto finded_model = m_models.find(_model_name.data());
		if (finded_model == m_models.end())
		{
			LOG_WARN("[Models manager WARN] Location model with this name is not found: '{0}'", _model_name);
			return std::nullopt;
		}
		return finded_model->second.second;
	}



	auto models_manager::deleleModel(std::string_view _model_name) noexcept -> bool
	{
		auto count_removed_elements = m_models.erase(_model_name.data());
		return count_removed_elements;
	}



	auto models_manager::getModelsDirectories() const noexcept -> const dirs_storage_t&
	{
		return m_file_searcher.getSearchDirectories();
	}
}