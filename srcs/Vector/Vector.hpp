/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Vector.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/25 15:19:02 by peerdb        #+#    #+#                 */
/*   Updated: 2020/09/26 14:50:41 by peerdb        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <limits>
# include <memory>
# include <iostream>
# include <cstddef>
# include <cstring>
# include <climits>
# include "../Iterators/RandomAccessIterator.hpp"
# include "../Traits.hpp"
# include "../Extra.hpp"

# if defined(unix) || defined(__unix__) || defined(__unix)
#  define PEER_MAX SSIZE_MAX
# else
#  define PEER_MAX SIZE_T_MAX
# endif

namespace ft {

	template<class T, class Alloc = std::allocator<T> >
	class vector {
	public:
		typedef T										value_type;
		typedef	Alloc									allocator_type;
		// typedef reference	allocator_type::reference;
		typedef value_type&								reference;
		typedef const value_type&						const_reference;
		typedef value_type*								pointer;
		typedef const value_type*						const_pointer;
		typedef RandomAccessIterator<T>					iterator;
		typedef ConstRandomAccessIterator<const T>		const_iterator;
		// typedef RevRandomAccessIterator<T> 				reverse_iterator;
		// typedef ConstRevRandomAccessIterator<const T>	const_reverse_iterator;
		typedef ptrdiff_t								difference_type;
		typedef size_t									size_type;

		explicit vector (const allocator_type& alloc = allocator_type()) : _alloc(alloc) {
			this->_array = 0;
			this->_size = 0;
			this->_capacity = 0;
		}
		explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _alloc(alloc) {
			this->_array = new value_type[n];
			this->_size = n;
			for (size_type i = 0; i < n; i++)
				this->_array[i] = val;
			this->_capacity = n;
		}
		template <class InputIterator>
		vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
				typename enable_if<is_iterator<typename InputIterator::iterator_category>::value, InputIterator>::type * = 0);
		vector (const vector& x) {
			*this = x;
		}
		// vector&	operator=(const vector& x) {
		// 	delete[] this->_array;
			
		// }
		~vector() {
			delete[] this->_array;
		}
	/* Iterators */
		iterator begin() {
			return iterator(this->_array);
		}
		const_iterator begin() const {
			return const_iterator(this->_array);
		}
		iterator end() {
			return iterator(&this->_array[this->_size]);
		}
		const_iterator end() const {
			return const_iterator(&this->_array[this->_size]);
		}
	/* Capacity */
		size_type	size() const {
			return this->_size;
		}
		size_type	max_size() const {
			return (PEER_MAX / sizeof(T));
		}
		void		resize (size_type n, value_type val = value_type()) {
			while (n < this->_size)
				pop_back();
			if (n > this->_capacity)
				resize(n);
			while (n > this->_size)
				push_back(val);
		}
		size_type	capacity() const {
			return this->_capacity;
		}
		void		reserve(size_type n) {
			if (n <= this->_capacity)
				return ;
			pointer tmp = new value_type[n];
			for (size_type i = 0; i < this->_size; i++) 
				tmp[i] = this->_array[i];
			delete[] this->_array;
			this->_array = tmp;
			this->_capacity = n;
		}
	/* Element Access */
		reference		operator[](size_type n) {
			return this->_array[n];
		}
		const_reference	operator[](size_type n) const {
			return this->_array[n];
		}
		reference		at(size_type n) {
			if (n >= this->_size)
				throw std::out_of_range();
			return this->_array[n];
		}
		reference		front() {
			return this->_array[0];
		}
		const_reference	front() const {
			return this->_array[0];
		}
		reference		back() {
			return this->_array[this->_size];
		}
		const_reference	back() const {
			return this->_array[this->_size];
		}
	/* Modifiers */
		template <class InputIterator>
		void assign (InputIterator first, InputIterator last) {
			this->clear();
			while (first != last) {
				push_back(*first);
				++first;
			}
		}
		void	push_back(const value_type& val) {
			if (this->_array == 0)
				resize(1);
			if (this->_size == this->_capacity)
				resize(this->_capacity * 2);
			this->_array[this->_size] = val;
			this->_size++;
		}
		void	pop_back() {
			// this->_array[this->_size] = 0;
			this->_size--;
		}
		iterator	erase(iterator position) {
			iterator tmp = position;
			while (position != end()) {
				*position = *(position + 1);
				++position;
			}
			return tmp;
		}
		void	clear() {
			while (this->_size)
				pop_back();
		}
	/* Non-member function overloads */
	private:
		pointer			_array;
		size_type		_size;
		size_type		_capacity;
		allocator_type	_alloc;
	};
}


#endif
