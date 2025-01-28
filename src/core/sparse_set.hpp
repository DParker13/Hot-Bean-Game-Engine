#pragma once

#include <array>
#include <cassert>
#include <unordered_map>
#include <stdexcept>

#include "ecs.hpp"

namespace Core {

	template <typename T, size_t MAX_ITEMS>
	class SparseSet : public ISparseSet {
		// Creates two arrays, one with a _dense array and one with a _sparse array.
		public:
			SparseSet() : _size(0) {};

			std::string ToString() const override {
				std::string str;

				for (size_t i = 0; i < _size; i++) {
					const Object* object = dynamic_cast<const Object*>(&_dense[i]);

					if (object != nullptr) {
						str += "  Index: " + std::to_string(i) + "\n";
						str += object->ToString();
					}
				}

				return str;
			}

			/**
			 * Inserts a new element into the set at the given index.
			 *
			 * @param index The index to insert the element at.
			 * @param data The element to insert.
			 *
			 * @throws assertion failure if the index is out of range.
			 */
			void Insert(size_t index, T data) {
				assert(0 <= index && index <= MAX_ITEMS && "Adding element outside of valid range.");

				// Maps data to end of _dense array
				_dense[_size] = data;

				// Maps this data's _dense array index (_size) to the _sparse array index (data)
				_sparse[index] = _size;

				// Update _dense array size
				_size++;
			}

			T& GetElement(size_t index) {
				assert(0 <= index && index <= MAX_ITEMS && "Element out of range.");

				// if (_dense[_sparse[index]] == T()) {
				// 	throw std::runtime_error("Element is nullptr");
				// }

				// Return a reference to the value
				return _dense[_sparse[index]];
			}

			/**
			 * Removes an element from the set by its index in the _sparse array.
			 *
			 * @param index The index of the element to remove.
			 *
			 * @throws assertion failure if the index is out of range.
			 * @throws assertion failure if the element does not exist in the set.
			 */
			void Remove(size_t index) override {
				assert(0 <= index && index <= MAX_ITEMS && "Removing item out of range.");
				assert(_sparse[index] == -1 && "Removing non-existent element.");

				// Replaces the element in the _dense array with the last element in the _dense array
				_dense[_sparse[index]] = _dense[_size];

				_sparse[index] = -1;

				_dense[_size] = T{};

				_size--;
			}

			/**
			 * Returns the number of elements in the set.
			 *
			 * @return The number of elements in the set.
			 */
			size_t Size() const override {
				return _size;
			}

			// Range based Iterator
			class Iterator {
			public:
				Iterator(T * ptr): ptr(ptr) {}
				Iterator operator++() { ++ptr; return *this; }
				bool operator!=(const Iterator & other) const { return ptr != other.ptr;  }
				T& operator*() const { return *ptr; }
			private:
				T* ptr;
			};

			Iterator begin() { return Iterator(_dense.data()); }
			Iterator end() { return Iterator(_dense.data() + _size); }

		private:
			// Current size of the _dense array
			size_t _size;

			// The packed array with no gaps
			std::array<T, MAX_ITEMS> _dense;

			// Sparse array that can have gaps, each element is an index in the _dense array
			std::array<size_t, MAX_ITEMS> _sparse;
	};
}