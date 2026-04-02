#pragma once

#include <cstddef>
		
namespace mogger {
	template <typename T> 
	class Vector {
		private:
			static const std::size_t START_CAPACITY;

			T* arr = nullptr;
			std::size_t capacity = START_CAPACITY;
			std::size_t size = 0;

		public:
			Vector();
			Vector(const Vector&) = delete;
			Vector& operator = (const Vector&) = delete;
			~Vector();
			
			std::size_t get_size() const noexcept;
			bool has_item(const T& value) const noexcept;
			bool insert(const std::size_t position, const T& value);
			void print() const noexcept;
			void push_back(const T& value);
			bool remove_first(const T& value);

		private:
    		T* allocate_and_copy(std::size_t new_capacity);
			void expand_capacity();
			void reduce_capacity();
			void shift_right(std::size_t position);
			void shift_left(std::size_t position);
	};
}
