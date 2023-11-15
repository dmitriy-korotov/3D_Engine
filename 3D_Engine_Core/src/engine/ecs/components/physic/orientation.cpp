#include <engine/ecs/components/physic/orientation.hpp>

#include <engine/Engine.hpp>

#include <glm/geometric.hpp>

#include <cassert>



namespace engine::ecs::components
{
	orientation::orientation(const glm::vec3& _forward, const glm::vec3& _right) noexcept
			: m_forward(glm::normalize(_forward))
			, m_right(glm::normalize(_right))
			, m_up(glm::normalize(glm::cross(m_forward, m_right)))
	{ 
		assert(std::abs(glm::dot(m_forward, m_right)) < 1e-3);
	}



	void orientation::setOrientation(const glm::vec3& _forward, const glm::vec3& _right) noexcept
	{
		assert(std::abs(glm::dot(m_forward, m_right)) < 1e-3);

		m_forward = glm::normalize(_forward);
		m_right = glm::normalize(_right);

		m_up = glm::normalize(glm::cross(m_right, m_forward));
	}



	const glm::vec3& orientation::getForward() const noexcept
	{
		return m_forward;
	}
	const glm::vec3& orientation::getRight() const noexcept
	{
		return m_right;
	}
	const glm::vec3& orientation::getUp() const noexcept
	{
		return m_up;
	}



	bool orientation::putOnUI() noexcept
	{
		auto& UI_module = Engine::getApplicationUIModule();

		bool is_clicked = false;

		is_clicked |= UI_module->putSliderFloat3("Fowrdard", m_forward, -1.f, 1.f);
		is_clicked |= UI_module->putSliderFloat3("Right", m_right, -1.f, 1.f);
		is_clicked |= UI_module->putSliderFloat3("Up", m_up, -1.f, 1.f);

		return is_clicked;
	}



	auto orientation::serialize() const noexcept -> serialized_view_t
	{
		auto serialized_view = basic_component::serialize();

		serialized_view["component_name"] = component_name;

		serialized_view["forward"] = serialized_view_t::array({ m_forward.x, m_forward.y, m_forward.z });
		serialized_view["right"] = serialized_view_t::array({ m_right.x, m_right.y, m_right.z });

		return serialized_view;
	}



	void orientation::deserializeFrom(const serialized_view_t& _serialized_view) noexcept
	{
		basic_component::deserializeFrom(_serialized_view);

		auto forward_coord = _serialized_view.at("forward").begin();

		m_forward.x = *(forward_coord);		forward_coord++;
		m_forward.y = *(forward_coord);		forward_coord++;
		m_forward.z = *(forward_coord);

		auto right_coord = _serialized_view.at("right").begin();

		m_right.x = *(right_coord);		right_coord++;
		m_right.y = *(right_coord);		right_coord++;
		m_right.z = *(right_coord);

		m_up = glm::cross(m_forward, m_right);
	}
}