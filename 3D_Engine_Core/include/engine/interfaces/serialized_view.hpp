#pragma once

#include <string>
#include <memory>



namespace engine::interfaces
{
	class serialized_view
	{
	public:

		struct virtual_iterator
		{

			virtual virtual_iterator& operator++() noexcept = 0;
			virtual serialized_view* operator*() noexcept = 0;
			virtual serialized_view* operator->() noexcept = 0;
			virtual const serialized_view* operator*() const noexcept = 0;
			virtual const serialized_view* operator->() const noexcept = 0;
			virtual bool operator!=(const virtual_iterator&) const noexcept = 0;

		};

		struct iterator
		{

			iterator(std::shared_ptr<virtual_iterator> _virtual_iter) noexcept;

			iterator& operator++() noexcept
			{
				++(*m_virtual_iter);
				return *this;
			}

			iterator operator++(int) noexcept
			{
				iterator tmp(m_virtual_iter);
				++(*m_virtual_iter);
				return tmp;
			}

			serialized_view* operator*() noexcept
			{
				return m_virtual_iter.get()->operator*();
			}

			serialized_view* operator->() noexcept
			{
				return m_virtual_iter.get()->operator*();
			}

			const serialized_view* operator*() const noexcept
			{
				return m_virtual_iter.get()->operator*();
			}

			const serialized_view* operator->() const noexcept
			{
				return m_virtual_iter.get()->operator*();
			}

			bool operator!=(const iterator& _right) const noexcept
			{
				return *m_virtual_iter != *_right.m_virtual_iter;
			}

		private:

			std::shared_ptr<virtual_iterator> m_virtual_iter = nullptr;

		};



		serialized_view() = default;

		virtual serialized_view& at(const char*) = 0;

		virtual serialized_view& to_array() noexcept = 0;
		virtual iterator begin() noexcept = 0;
		virtual iterator end() noexcept = 0;
		virtual void push_back(const serialized_view&) noexcept = 0;

		virtual void emplace(const char*, float) noexcept = 0;
		virtual void emplace(const char*, double) noexcept = 0;
		virtual void emplace(const char*, unsigned int) noexcept = 0;
		virtual void emplace(const char*, int) noexcept = 0;
		virtual void emplace(const char*, bool) noexcept = 0;
		virtual void emplace(const char*, std::string) noexcept = 0;
		virtual void emplace(const char*, const char*) noexcept = 0;

		virtual operator float() const noexcept = 0;
		virtual operator double() const noexcept = 0;
		virtual operator unsigned int() const noexcept = 0;
		virtual operator int() const noexcept = 0;
		virtual operator bool() const noexcept = 0;
		virtual operator std::string() const noexcept = 0;

		virtual ~serialized_view() = default;

	};
}