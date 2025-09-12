/**
 * @file sparse_set.hpp
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
 * 
 */

#pragma once

#include <array>
#include <unordered_map>
#include <stdexcept>
#include <any>

namespace HBE::Core {

	struct ISparseSet {
		virtual ~ISparseSet() = default;
		virtual void Add(std::any value) = 0;
		virtual void Insert(size_t index, const std::any value) = 0;
		virtual void InsertEmpty(size_t index) = 0;
		virtual void Remove(size_t index) = 0;
		virtual std::any GetElementPtrAsAny(size_t index) = 0;
		virtual size_t Size() const = 0;
		virtual bool HasElement(size_t index) const = 0;
	};

	template <typename T, size_t MAX_ITEMS>
	class SparseSet : public ISparseSet {
		// Creates two arrays, one with a m_dense array and one with a m_sparse array.
		public:
			SparseSet() : m_size(0) {
				for (size_t i = 0; i < MAX_ITEMS; i++) {
					m_sparse[i] = -1;
				}
			}

			/**
			 * @brief Copy constructor
			 * 
			 * @param other Other sparse set reference
			 */
			SparseSet(const SparseSet& other) {
				for (size_t i = 0; i < other.m_size; i++) {
					this->Insert(i, other.GetElementAsRef(i));
				}
			}
		
			/**
			 * @brief Move constructor
			 * 
			 * @param other Other sparse set rvalue
			 */
			SparseSet(SparseSet&& other) noexcept {
				for (size_t i = 0; i < other.m_size; i++) {
					this->Insert(i, other.GetElementAsRef(i));
				}
			}

			T& operator[](size_t index) {
				return GetElementAsRef(index);
			}

			const T& operator[](size_t index) const {
				return GetElementAsRef(index);
			}

			/**
			 * @brief Adds an element to the set
			 * 
			 * @param value Value to add
			 */
			void Add(std::any value) {
				if (m_size >= MAX_ITEMS) {
					throw std::overflow_error("Sparse set is full.");
				}

				this->Insert(m_size, value);
			}

			/**
			 * @brief Inserts an element into the set
			 * 
			 * @param index Index to insert at
			 * @param value Value to insert
			 */
			void Insert(size_t index, const std::any value) override {
				if (index < 0 || index > MAX_ITEMS) {
					throw std::out_of_range("Index out of range.");
				}

				try {
					T typed_value = std::any_cast<T>(value);

					// Maps typed value to end of m_dense array
					m_dense[m_size] = typed_value;
	
					// Maps this typed value's m_dense array index (m_size) to the m_sparse array index (value)
					m_sparse[index] = m_size;
	
					// Update m_dense array size
					m_size++;
				}
				catch (const std::bad_any_cast& e) {
					throw;
				}
			}

			/**
			 * @brief Inserts an element into the set
			 * 
			 * @param index Index to insert at
			 * @param value Value to insert
			 */
			void Insert(size_t index, const T& value) {
				if (index < 0 || index > MAX_ITEMS) {
					throw std::out_of_range("Index out of range.");
				}

				// Maps value to end of m_dense array
				m_dense[m_size] = value;

				// Maps this value's m_dense array index (m_size) to the m_sparse array index (value)
				m_sparse[index] = m_size;

				// Update m_dense array size
				m_size++;
			}

			/**
			 * @brief Inserts an element into the set
			 * 
			 * @param index Index to insert at
			 */
			void InsertEmpty(size_t index) override {
				if (index < 0 || index > MAX_ITEMS) {
					throw std::out_of_range("Index out of range.");
				}

				// Maps this typed value's m_dense array index (m_size) to the m_sparse array index (value)
				m_sparse[index] = m_size;

				// Update m_dense array size
				m_size++;
			}

			/**
			 * @brief Checks if the set has an element at the given index
			 * 
			 * @param index Index of the element
			 * @return true
			 * @return false 
			 */
			bool HasElement(size_t index) const override {
				if (index < 0 || index > MAX_ITEMS) {
					throw std::out_of_range("Index out of range.");
				}

				return m_sparse[index] != -1;
			}

			/**
			 * @brief Get the Element object
			 * 
			 * @param index Index of the element
			 * @return std::any Element from the set
			 */
			std::any GetElementPtrAsAny(size_t index) override {
				if (index < 0 || index > MAX_ITEMS) {
					throw std::out_of_range("Index out of range.");
				}

				return &m_dense[m_sparse[index]];
			}

			/**
			 * @brief Get the Element object
			 * 
			 * @param index Index of the element
			 * @return std::any Element from the set
			 */
			T& GetElementAsRef(size_t index) {
				if (index < 0 || index > MAX_ITEMS) {
					throw std::out_of_range("Index out of range.");
				}

				return m_dense[m_sparse[index]];
			}

			/**
			 * @brief Removes an element from the set at the given index.
			 * 
			 * @param index The index of the element to remove.
			 */
			void Remove(size_t index) override {
				if (m_sparse[index] == -1) {
					throw std::out_of_range("Element does not exist.");
				}

				// Replaces the element in the m_dense array with the last element in the m_dense array
				GetElementAsRef(index) = m_dense[m_size];
				m_sparse[index] = -1;
				m_dense[m_size] = T{};
				m_size--;
			}

			/**
			 * Returns the number of elements in the set.
			 *
			 * @return The number of elements in the set.
			 */
			size_t Size() const override {
				return m_size;
			}

			// Range based Iterator
			class Iterator {
				public:
					Iterator(T* ptr): ptr(ptr) {}
					Iterator operator++() { ++ptr; return *this; }
					bool operator!=(const Iterator & other) const { return ptr != other.ptr;  }
					T& operator*() const { return *ptr; }
				private:
					T* ptr;
			};

			Iterator begin() { return Iterator(m_dense.data()); }
			Iterator end() { return Iterator(m_dense.data() + m_size); }

		private:
			// Current size of the m_dense array
			size_t m_size;

			// The packed array with no gaps
			std::array<T, MAX_ITEMS> m_dense;

			// Sparse array that can have gaps, each element is an index in the m_dense array
			std::array<int, MAX_ITEMS> m_sparse;
	};
}