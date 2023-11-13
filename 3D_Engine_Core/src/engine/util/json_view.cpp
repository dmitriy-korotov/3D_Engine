#include <engine/util/json_view.hpp>



namespace engine::util
{
	json_view::json_view() noexcept
			: m_data(json_t())
			, m_reference_on_data(m_data.value())
	{ }



	json_view::json_view(json_t& _reference_on_data) noexcept
			: m_reference_on_data(_reference_on_data)
	{ }



	interfaces::serialized_view& json_view::at(const char* _key)
	{
		if (!m_childs.has_value())
			m_childs.emplace(childs_map_t());

		const auto& [ref_on_view, is_inserted] = m_childs->emplace(_key, json_view(m_reference_on_data[_key]));

		return m_childs->at(_key);
	}



	interfaces::serialized_view& json_view::to_array() noexcept
	{
		m_reference_on_data = json_t::array();
		return *this;
	}



	auto json_view::begin() noexcept -> iterator
	{
		return iterator(std::make_shared<json_iterator>(m_reference_on_data.begin()));
	}



	auto json_view::end() noexcept -> iterator
	{
		return iterator(std::make_shared<json_iterator>(m_reference_on_data.end()));
	}



	void json_view::push_back(const serialized_view& _value) noexcept
	{
		const json_view& json_value = static_cast<const json_view&>(_value);
		m_reference_on_data.push_back(json_value.m_reference_on_data);
	}



	void json_view::emplace(const char* _key, float _value) noexcept
	{										
		m_reference_on_data[_key] = _value;
	}										
	void json_view::emplace(const char* _key, double _value) noexcept
	{										
		m_reference_on_data[_key] = _value;
	}										
	void json_view::emplace(const char* _key, unsigned int _value) noexcept
	{										
		m_reference_on_data[_key] = _value;
	}										
	void json_view::emplace(const char* _key, int _value) noexcept
	{										
		m_reference_on_data[_key] = _value;
	}
	void json_view::emplace(const char* _key, bool _value) noexcept
	{										
		m_reference_on_data[_key] = _value;
	}										
	void json_view::emplace(const char* _key, std::string _value) noexcept
	{
		m_reference_on_data[_key] = std::move(_value);
	}
	void json_view::emplace(const char* _key, const char* _value) noexcept
	{
		m_reference_on_data[_key] = _value;
	}



	json_view::operator float() const noexcept
	{
		return m_reference_on_data;
	}
	json_view::operator double() const noexcept
	{
		return m_reference_on_data;
	}
	json_view::operator unsigned int() const noexcept
	{
		return m_reference_on_data;
	}
	json_view::operator int() const noexcept
	{
		return m_reference_on_data;
	}
	json_view::operator bool() const noexcept
	{
		return m_reference_on_data;
	}
	json_view::operator std::string() const noexcept
	{
		return m_reference_on_data;
	}
}