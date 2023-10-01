#pragma once

#include <engine/ecs/ecs.hpp>

#include <unordered_map>
#include <memory>



namespace engine::ecs::components
{
	template <typename ComponentType>
	class component_iterator
	{
	public:

		template <typename T>
		using component_ptr = std::shared_ptr<T>;

		template <typename T>
		using map_component_iterator = typename std::unordered_map<entities::entity_id, component_ptr<T>>::iterator;


		component_iterator(map_component_iterator<ComponentType> _map_iterator) noexcept;

		const component_ptr<const ComponentType>& operator*() const noexcept;
		const component_ptr<ComponentType>& operator*() noexcept;

		component_iterator& operator++() noexcept;
		component_iterator operator++(int) noexcept;

		bool operator==(const component_iterator& _right) const noexcept;
		bool operator!=(const component_iterator& _right) const noexcept;

		const ComponentType* const operator->() const noexcept;
		ComponentType* const operator->() noexcept;

	private:

		map_component_iterator<ComponentType> m_map_iterator;

	};


	
	template <typename ComponentType>
	component_iterator<ComponentType>::component_iterator(map_component_iterator<ComponentType> _map_iterator) noexcept
			: m_map_iterator(std::move(_map_iterator))
	{ }



	template <typename ComponentType>
	const typename component_iterator<ComponentType>::component_ptr<const ComponentType>& 
	component_iterator<ComponentType>::operator*() const noexcept
	{
		return m_map_iterator->second;
	}



	template <typename ComponentType>
	const typename component_iterator<ComponentType>::component_ptr<ComponentType>&
		component_iterator<ComponentType>::operator*() noexcept
	{
		return m_map_iterator->second;
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
		return m_map_iterator->second.get();
	}



	template <typename ComponentType>
	ComponentType* const component_iterator<ComponentType>::operator->() noexcept
	{
		return m_map_iterator->second.get();
	}
}