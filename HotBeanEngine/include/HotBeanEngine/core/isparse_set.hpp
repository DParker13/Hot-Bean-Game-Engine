/**
 * @file isparse_set.hpp
 * @author Daniel Parker (DParker13)
 * @brief Sparse set data structure.
 * 
 * @details Keeps track of two arrays, dense array and sparse array.
 * The Dense array is a packed array with no gaps. This array is iterated through.
 * The Sparse array is an array that can have gaps, each element is an index in the Dense array.
 * @version 0.1
 * @date 2025-02-23
 * 
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <array>
#include <any>
#include <cassert>
#include <type_traits>
#include <cstddef>

#include <HotBeanEngine/core/component.hpp>

namespace HBE::Core {

	/**
	 * @brief Interface for type-erased sparse set operations.
	 * Provides common operations for all sparse set implementations.
	 */
	struct ISparseSet {
		virtual ~ISparseSet() = default;
		virtual bool Add(std::any value) = 0;
		virtual bool Insert(size_t index, const std::any value) = 0;
		virtual bool InsertEmpty(size_t index) = 0;
		virtual bool Remove(size_t index) = 0;
		virtual std::any GetElementPtrAsAny(size_t index) = 0;
		virtual size_t Size() const = 0;
		virtual bool HasElement(size_t index) const = 0;
	};

	/**
	 * @brief Efficient data structure for sparse component storage
	 * 
	 * Uses dense and sparse arrays for fast iteration and O(1) lookup.
	 * Optimized for ECS component storage with minimal memory overhead.
	 */
	template <typename T, size_t MAX_ITEMS>
	class SparseSet : public ISparseSet {
	private:
		// Current size of the m_dense array
		size_t m_size;

		// The packed array with no gaps
		std::array<T, MAX_ITEMS> m_dense;

		// Sparse array that can have gaps, each element is an index in the m_dense array
		std::array<int, MAX_ITEMS> m_sparse;

		// Reverse mapping: maps dense index back to sparse index for O(1) removal
		std::array<size_t, MAX_ITEMS> m_dense_to_sparse;

	public:
		SparseSet() : m_size(0) {
			m_sparse.fill(-1);
		}

		/**
		 * @brief Copy constructor
		 * @param other Other sparse set reference
		 */
		SparseSet(const SparseSet& other) : m_size(other.m_size),
			m_dense(other.m_dense), m_sparse(other.m_sparse), m_dense_to_sparse(other.m_dense_to_sparse) {}
	
		/**
		 * @brief Move constructor
		 * @param other Other sparse set reference
		 */
		SparseSet(SparseSet&& other) noexcept : m_size(other.m_size),
			m_dense(std::move(other.m_dense)), m_sparse(std::move(other.m_sparse)),
			m_dense_to_sparse(std::move(other.m_dense_to_sparse)) {
			other.m_size = 0;
		}

		/**
		 * @brief Subscript operator for element access
		 * @param index Index of the element
		 * @return T& Reference to the element at the given index
		 */
		T& operator[](size_t index) {
			return GetElementAsRef(index);
		}

		const T& operator[](size_t index) const {
			return GetElementAsRef(index);
		}
	
		/**
		 * @brief Adds an element sequentially to the set
		 * @param value Value to add
		 */
		bool Add(std::any value) {
			// Check if the set is full
			if (m_size >= MAX_ITEMS) {
				return false;
			}

			return this->Insert(m_size, value);
		}

		/**
		 * @brief Inserts an element into the set
		 * 
		 * @param index Index to insert at
		 * @param value Value to insert
		 */
		bool Insert(size_t index, const std::any value) override {
			if (index >= MAX_ITEMS || m_sparse[index] != -1) {
				return false;
			}

			const T* typed_value_ptr = std::any_cast<T>(&value);
			if (typed_value_ptr == nullptr) {
				return false;
			}

			// Maps typed value to end of m_dense array
			m_dense[m_size] = *typed_value_ptr;

			// Maps this typed value's m_dense array index (m_size) to the m_sparse array index (value)
			m_sparse[index] = static_cast<int>(m_size);

			// Store reverse mapping
			m_dense_to_sparse[m_size] = index;

			// Update m_dense array size
			m_size++;

			return true;
		}

		/**
		 * @brief Inserts an element into the set
		 * 
		 * @param index Index to insert at
		 * @param value Value to insert
		 * @return True if successful
		 */
		bool Insert(size_t index, const T& value) {
			if (index >= MAX_ITEMS || m_sparse[index] != -1) {
				return false;
			}

			// Maps value to end of m_dense array
			m_dense[m_size] = value;

			// Maps this value's m_dense array index (m_size) to the m_sparse array index (value)
			m_sparse[index] = static_cast<int>(m_size);

			// Store reverse mapping
			m_dense_to_sparse[m_size] = index;

			// Update m_dense array size
			m_size++;

			return true;
		}

		/**
		 * @brief Inserts an element into the set
		 * 
		 * @param index Index to insert at
		 */
		bool InsertEmpty(size_t index) override {
			if (index >= MAX_ITEMS || m_size >= MAX_ITEMS || m_sparse[index] != -1) {
				return false;
			}

			// Maps this typed value's m_dense array index (m_size) to the m_sparse array index (value)
			m_sparse[index] = static_cast<int>(m_size);

			// Store reverse mapping
			m_dense_to_sparse[m_size] = index;

			// Set value to default
			m_dense[m_size++] = T{};

			return true;
		}

		/**
		 * @brief Checks if the set has an element at the given index
		 * 
		 * @param index Index of the element
		 * @return true Element exists
		 * @return false Element does not exist
		 */
		bool HasElement(size_t index) const override {
			if (index >= MAX_ITEMS) {
				return false;
			}

			return m_sparse[index] != -1;
		}

		/**
		 * @brief Get the Element object
		 * @todo Find a way to do this without static_cast to Component
		 * @param index Index of the element
		 * @return std::any Element from the set
		 */
		std::any GetElementPtrAsAny(size_t index) override {
			static_assert(std::is_base_of_v<IComponent, T>, "T must inherit from IComponent for this function.");
			if (index >= MAX_ITEMS || m_sparse[index] == -1) {
				return std::any();
			}

			return static_cast<IComponent*>(&m_dense[m_sparse[index]]);
		}

		/**
		 * @brief Get the Element object safely with nullptr on failure
		 * 
		 * @param index Index of the element
		 * @return T* Pointer to element, or nullptr if not found
		 */
		T* GetElement(size_t index) {
			if (index >= MAX_ITEMS || m_sparse[index] == -1) {
				return nullptr;
			}

			return &m_dense[m_sparse[index]];
		}

		/**
		 * @brief Get the Element object safely with nullptr on failure (const version)
		 * 
		 * @param index Index of the element
		 * @return const T* Const pointer to element, or nullptr if not found
		 */
		const T* GetElement(size_t index) const {
			if (index >= MAX_ITEMS || m_sparse[index] == -1) {
				return nullptr;
			}

			return &m_dense[m_sparse[index]];
		}

		/**
		 * @brief Get the Element object (assumes caller validated existence)
		 * Must validate existence with HasElement() before calling this function for safety.
		 * 
		 * @param index Index of the element
		 * @return T& Reference to element
		 */
		T& GetElementAsRef(size_t index) {
			assert(index < MAX_ITEMS && "Index out of range.");
			assert(m_sparse[index] != -1 && "Element does not exist.");

			return m_dense[m_sparse[index]];
		}

		/**
		 * @brief Get the Element object (assumes caller validated existence)
		 * Must validate existence with HasElement() before calling this function for safety.
		 * 
		 * @param index Index of the element
		 * @return T& Reference to element
		 */
		const T& GetElementAsRef(size_t index) const {
			assert(index < MAX_ITEMS && "Index out of range.");
			assert(m_sparse[index] != -1 && "Element does not exist.");

			return m_dense[m_sparse[index]];
		}

		/**
		 * @brief Removes an element from the set at the given index.
		 * 
		 * @param index The index of the element to remove.
		 */
		bool Remove(size_t index) override {
			if (index >= MAX_ITEMS || m_sparse[index] == -1 || m_size == 0) {
				return false;
			}

			// Get the dense index of the element to remove
			int dense_index = m_sparse[index];
			
			// If this isn't the last element, swap it with the last element
			if (static_cast<size_t>(dense_index) != m_size - 1) {
				// Get the sparse index of the last element using reverse mapping (O(1))
				size_t last_sparse_index = m_dense_to_sparse[m_size - 1];
				
				// Move the last element to the removed element's position
				m_dense[dense_index] = m_dense[m_size - 1];
				
				// Update the sparse mapping for the moved element
				m_sparse[last_sparse_index] = dense_index;

				// Update the reverse mapping
				m_dense_to_sparse[dense_index] = last_sparse_index;
			}
			
			// Clear the removed element's sparse entry
			m_sparse[index] = -1;
			
			// Clear the last dense element and decrease size
			m_dense[m_size - 1] = T{};
			m_size--;

			return true;
		}

		/**
		 * Returns the number of elements in the set.
		 * @return The number of elements in the set.
		 */
		size_t Size() const override {
			return m_size;
		}

		// Forward iterator for range-based loops
		class Iterator {
			public:
				using value_type = T;
				using difference_type = std::ptrdiff_t;
				using pointer = T*;
				using reference = T&;
				using iterator_category = std::forward_iterator_tag;

				Iterator(T* ptr): ptr(ptr) {}
				
				Iterator& operator++() { ++ptr; return *this; }
				Iterator operator++(int) { Iterator tmp = *this; ++ptr; return tmp; }
				
				bool operator==(const Iterator& other) const { return ptr == other.ptr; }
				bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
				
				T& operator*() const { return *ptr; }
				T* operator->() const { return ptr; }
			private:
				T* ptr;
		};

		// Const iterator for range-based loops
		class ConstIterator {
			public:
				using value_type = T;
				using difference_type = std::ptrdiff_t;
				using pointer = const T*;
				using reference = const T&;
				using iterator_category = std::forward_iterator_tag;

				ConstIterator(const T* ptr): ptr(ptr) {}
				
				ConstIterator& operator++() { ++ptr; return *this; }
				ConstIterator operator++(int) { ConstIterator tmp = *this; ++ptr; return tmp; }
				
				bool operator==(const ConstIterator& other) const { return ptr == other.ptr; }
				bool operator!=(const ConstIterator& other) const { return ptr != other.ptr; }
				
				const T& operator*() const { return *ptr; }
				const T* operator->() const { return ptr; }
			private:
				const T* ptr;
		};

		Iterator begin() { return Iterator(m_dense.data()); }
		Iterator end() { return Iterator(m_dense.data() + m_size); }
		
		ConstIterator begin() const { return ConstIterator(m_dense.data()); }
		ConstIterator end() const { return ConstIterator(m_dense.data() + m_size); }
		
		ConstIterator cbegin() const { return ConstIterator(m_dense.data()); }
		ConstIterator cend() const { return ConstIterator(m_dense.data() + m_size); }
	};
}