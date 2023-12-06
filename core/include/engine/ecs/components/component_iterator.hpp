#pragma once

#include <engine/ecs/ecs.hpp>

#include <unordered_map>
#include <memory>



namespace engine::ecs::components
{
	template <typename BasicComponentType, typename ComponentType>
	class component_iterator
	{
	public:

		template <typename T>
		using component_ptr_t = std::shared_ptr<T>;

		template <typename T>
		using map_component_iterator_t = typename std::unordered_map<entities::entity_id_t, component_ptr_t<T>>::const_iterator;



		component_iterator(map_component_iterator_t<BasicComponentType> _map_iterator) noexcept;

		component_ptr_t<const ComponentType> operator*() const noexcept;
		component_ptr_t<ComponentType> operator*() noexcept;

		component_iterator& operator++() noexcept;
		component_iterator operator++(int) noexcept;

		bool operator==(const component_iterator& _right) const noexcept;
		bool operator!=(const component_iterator& _right) const noexcept;

		const ComponentType* const operator->() const noexcept;
		ComponentType* const operator->() noexcept;

	private:

		map_component_iterator_t<BasicComponentType> m_map_iterator;

	};


	
	template <typename BasicComponentType, typename ComponentType>
	component_iterator<BasicComponentType, ComponentType>::component_iterator(map_component_iterator_t<BasicComponentType> _map_iterator) noexcept
			: m_map_iterator(std::move(_map_iterator))
	{ }



	template <typename BasicComponentType, typename ComponentType>
	auto component_iterator<BasicComponentType, ComponentType>::operator*() const noexcept -> component_ptr_t<const ComponentType>
	{
		return std::dynamic_pointer_cast<const ComponentType>(m_map_iterator->second);
	}



	template <typename BasicComponentType, typename ComponentType>
	auto component_iterator<BasicComponentType, ComponentType>::operator*() noexcept -> component_ptr_t<ComponentType>
	{
		return std::dynamic_pointer_cast<ComponentType>(m_map_iterator->second);
	}



	template <typename BasicComponentType, typename ComponentType>
	auto component_iterator<BasicComponentType, ComponentType>::operator++() noexcept -> component_iterator&
	{
		return ++m_map_iterator;
	}



	template <typename BasicComponentType, typename ComponentType>
	auto component_iterator<BasicComponentType, ComponentType>::operator++(int) noexcept -> component_iterator
	{
		component_iterator<BasicComponentType, ComponentType> prev_iter(m_map_iterator++);
		return prev_iter;
	}



	template <typename BasicComponentType, typename ComponentType>
	auto component_iterator<BasicComponentType, ComponentType>::operator==(const component_iterator& _right) const noexcept -> bool
	{
		return m_map_iterator == _right.m_map_iterator;
	}



	template <typename BasicComponentType, typename ComponentType>
	auto component_iterator<BasicComponentType, ComponentType>::operator!=(const component_iterator& _right) const noexcept -> bool
	{
		return m_map_iterator != _right.m_map_iterator;
	}



	template <typename BasicComponentType, typename ComponentType>
	auto component_iterator<BasicComponentType, ComponentType>::operator->() const noexcept -> const ComponentType* const
	{
		return dynamic_cast<ComponentType* const>(m_map_iterator->second.get());
	}



	template <typename BasicComponentType, typename ComponentType>
	auto component_iterator<BasicComponentType, ComponentType>::operator->() noexcept -> ComponentType* const
	{
		return dynamic_cast<ComponentType* const>(m_map_iterator->second.get());
	}
}