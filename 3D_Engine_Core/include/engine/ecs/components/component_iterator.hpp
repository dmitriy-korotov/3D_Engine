#pragma once

#include <engine/ecs/ecs.hpp>

#include <engine/ecs/components/fwd/basic_component.hpp>

#include <unordered_map>
#include <memory>



namespace engine::ecs::components
{
	template <typename ComponentType>
	class component_iterator
	{
	public:

		template <typename T>
		using component_ptr_t = std::shared_ptr<T>;

		template <typename T>
		using map_component_iterator_t = typename std::unordered_map<entities::entity_id_t, component_ptr_t<T>>::const_iterator;


		component_iterator(map_component_iterator_t<basic_component> _map_iterator) noexcept;

		component_ptr_t<const ComponentType> operator*() const noexcept;
		component_ptr_t<ComponentType> operator*() noexcept;

		component_iterator& operator++() noexcept;
		component_iterator operator++(int) noexcept;

		bool operator==(const component_iterator& _right) const noexcept;
		bool operator!=(const component_iterator& _right) const noexcept;

		const ComponentType* const operator->() const noexcept;
		ComponentType* const operator->() noexcept;

	private:

		map_component_iterator_t<basic_component> m_map_iterator;

	};


	
	template <typename ComponentType>
	component_iterator<ComponentType>::component_iterator(map_component_iterator_t<basic_component> _map_iterator) noexcept
			: m_map_iterator(std::move(_map_iterator))
	{ }



	template <typename ComponentType>
	typename component_iterator<ComponentType>::component_ptr_t<const ComponentType>
	component_iterator<ComponentType>::operator*() const noexcept
	{
		return std::dynamic_pointer_cast<const ComponentType>(m_map_iterator->second);
	}



	template <typename ComponentType>
	typename component_iterator<ComponentType>::component_ptr_t<ComponentType>
		component_iterator<ComponentType>::operator*() noexcept
	{
		return std::dynamic_pointer_cast<ComponentType>(m_map_iterator->second);
	}



	template <typename ComponentType>
	component_iterator<ComponentType>& component_iterator<ComponentType>::operator++() noexcept
	{
		return ++m_map_iterator;
	}



	template <typename ComponentType>
	component_iterator<ComponentType> component_iterator<ComponentType>::operator++(int) noexcept
	{
		component_iterator<ComponentType> prev_iter(m_map_iterator++);
		return prev_iter;
	}



	template <typename ComponentType>
	bool component_iterator<ComponentType>::operator==(const component_iterator& _right) const noexcept
	{
		return m_map_iterator == _right.m_map_iterator;
	}



	template <typename ComponentType>
	bool component_iterator<ComponentType>::operator!=(const component_iterator& _right) const noexcept
	{
		return m_map_iterator != _right.m_map_iterator;
	}



	template <typename ComponentType>
	const ComponentType* const component_iterator<ComponentType>::operator->() const noexcept
	{
		return dynamic_cast<ComponentType* const>(m_map_iterator->second.get());
	}



	template <typename ComponentType>
	ComponentType* const component_iterator<ComponentType>::operator->() noexcept
	{
		return dynamic_cast<ComponentType* const>(m_map_iterator->second.get());
	}
}