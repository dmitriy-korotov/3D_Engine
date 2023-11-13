#pragma once

#include <engine/interfaces/serialized_view.hpp>

#include <nlohmann/json.hpp>

#include <optional>
#include <unordered_map>



namespace engine::util
{
	class json_view: public interfaces::serialized_view			// TODO wrapp json
	{
	public:

		using json_t = nlohmann::json;



		struct json_iterator: public serialized_view::virtual_iterator
		{
			json_iterator(json_t::iterator _internal_iter) noexcept;

			virtual_iterator& operator++() noexcept override;
			serialized_view* operator*() noexcept override;
			serialized_view* operator->() noexcept override;
			const serialized_view* operator*() const noexcept override;
			const serialized_view* operator->() const noexcept override;
			bool operator!=(const serialized_view::virtual_iterator& _right) const noexcept override;

		private:

			json_t::iterator m_internal_iter;

		};



		json_view() noexcept;

		serialized_view& at(const char* _key) override;

		serialized_view& to_array() noexcept override;
		iterator begin() noexcept override;
		iterator end() noexcept override;
		void push_back(const serialized_view& _value) noexcept override;

		void emplace(const char* _key, float _value) noexcept override;
		void emplace(const char* _key, double _value) noexcept override;
		void emplace(const char* _key, unsigned int _value) noexcept override;
		void emplace(const char* _key, int _value) noexcept override;
		void emplace(const char* _key, bool _value) noexcept override;
		void emplace(const char* _key, std::string _value) noexcept override;
		void emplace(const char* _key, const char* _value) noexcept override;

		operator float() const noexcept override;
		operator double() const noexcept override;
		operator unsigned int() const noexcept override;
		operator int() const noexcept override;
		operator bool() const noexcept override;
		operator std::string() const noexcept override;

	private:

		json_view(json_t& _reference_on_data) noexcept;

	private:

		using childs_map_t = std::unordered_map<std::string, json_view>;

		std::optional<json_t> m_data;
		json_t& m_reference_on_data;

		std::optional<childs_map_t> m_childs;

	};
}