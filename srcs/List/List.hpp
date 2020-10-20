/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   List.hpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/06 12:23:59 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/10/20 14:31:14 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP

# include <limits>
# include <memory>
# include <cstddef>
# include "ListNode.hpp"
# include "../Iterators/BidirectionalIterator.hpp"
# include "../Traits.hpp"
# include "../Extra.hpp"

namespace ft {
	
	template < class T, class Alloc = std::allocator<T> >
	class list {
	public:
		typedef T			value_type;
		typedef Alloc		allocator_type;
		typedef T			&reference;
		typedef const T		&const_reference;
		typedef T			*pointer;
		typedef const T		*const_pointer;
		typedef node<T> 	*node_pointer;
		typedef ptrdiff_t	difference_type;
		typedef size_t		size_type;
		typedef BidirectionalIterator<value_type, node_pointer>			iterator;
		typedef ConstBidirectionalIterator<value_type, node_pointer>	const_iterator;
		typedef RevBidirectionalIterator<value_type, node_pointer>		reverse_iterator;
		typedef ConstRevBidirectionalIterator<value_type, node_pointer>	const_reverse_iterator;
	private:
		node_pointer		head;
		node_pointer 		tail;
		allocator_type		alloc;
		size_type			length;
	public:

	/* Constructors, destructor and operator= */
		explicit list(const allocator_type& alloc = allocator_type()) : alloc(alloc), length(0) /* Default constructor */
		{
			this->head = new node<T>();
			this->tail = new node<T>();
			this->head->next = this->tail;
			this->tail->prev = this->head;
		}
		explicit list (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : alloc(alloc), length(0)
		{
			this->head = new node<T>();
			this->tail = new node<T>();
			this->head->next = this->tail;
			this->tail->prev = this->head;
			this->assign(n, val);
		}
		template <class InputIterator>
		list (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), 
				typename enable_if<is_iterator<typename InputIterator::iterator_category>::value, InputIterator>::type * = 0)
				: alloc(alloc), length(0) {
			this->head = new node<T>();
			this->tail = new node<T>();
			this->head->next = this->tail;
			this->tail->prev = this->head;
			this->assign(first, last);
		}
		list (const list& x) : alloc(x.alloc), length(0) {
			this->head = new node<T>();
			this->tail = new node<T>();
			this->head->next = this->tail;
			this->tail->prev = this->head;
			this->assign(x.begin(), x.end());
		}
		list&	operator=(const list& x) {
			this->clear();
			this->head->next = this->tail;
			this->tail->prev = this->head;
			this->length = 0;
			this->assign(x.begin(), x.end());
			return *this;
		}
		~list() {
			this->clear();
			delete this->tail;
			delete this->head;
		}
	/* Iterators */
		iterator	begin() {
			return iterator(this->head->next);
		}
		const_iterator	begin() const {
			return const_iterator(this->head->next);
		}
		iterator	end() {
			return iterator(this->tail);
		}
		const_iterator	end() const {
			return const_iterator(this->tail);
		}
		reverse_iterator		rbegin() {
			return reverse_iterator(this->tail->prev);
		}
		const_reverse_iterator	rbegin() const {
			return const_reverse_iterator(this->tail->prev);
		}
		reverse_iterator		rend() {
			return reverse_iterator(this->head);
		}
		const_reverse_iterator	rend() const {
			return const_reverse_iterator(this->head);
		}		

	/* Capacity */
		bool		empty() const {
			return (this->length == 0);
		}
		size_type	size() const {
			return this->length;
		}
		size_type	max_size() const {
			return (std::numeric_limits<size_type>::max() / (sizeof(node<value_type>)));
		}
		
	/* Element access */
		reference		front() {
			return this->head->next->data;
		}
		const_reference	front() const {
			return this->head->next->data;
		}
		reference		back() {
			return this->tail->prev->data;
		}
		const_reference	back() const {
			return this->tail->prev->data;
		}
	
	/* Modifiers */
		template <class InputIterator>
 		void assign(InputIterator first, InputIterator last,
				typename enable_if<is_iterator<typename InputIterator::iterator_category>::value, InputIterator>::type * = 0) {
			this->clear();
			while (first != last) {
				push_back(*first);
				++first;
			} 
		}
		void	assign(size_type n, const value_type& val) {
			this->clear();
			while (n > 0) {
				push_back(val);
				--n;
			}
		}
		void	push_front(const value_type &val) {
			node<T> *ptr = new node<T>(val);
			ptr->prev = this->head;
			ptr->next = this->head->next;
			this->head->next->prev = ptr;
			this->head->next = ptr;
			this->length++;
		}
		void	pop_front() {
			if (this->length)
			{
				node<T> *tmp = this->head->next->next;
				tmp->prev = this->head;
				delete this->head->next;
				this->head->next = tmp;
				this->length--;
			}
		}
		void	push_back(const value_type &val) {
			node<T>	*ptr = new node<T>(val);
			ptr->next = this->tail;
			ptr->prev = this->tail->prev;
			this->tail->prev->next = ptr;
			this->tail->prev = ptr;
			this->length++;
		}
		void	pop_back() {
			if (this->length)
			{
				node<T>	*tmp = this->tail->prev->prev;
				tmp->next = this->tail;
				delete this->tail->prev;
				this->tail->prev = tmp;
				this->length--;
			}
		}
		iterator	insert(iterator position, const value_type& val) {
			node<T> *insertion = new node<T>(val);
			insertion->prev = position.getptr()->prev;
			insertion->next = position.getptr();
			insertion->prev->next = insertion;
			insertion->next->prev = insertion;
			this->length++;
			return iterator(insertion);
		}
		void		insert(iterator position, size_type n, const value_type& val) {
			while (n > 0) {
				insert(position, val);
				--n;
			}
		}
		template <class InputIterator>
		void		insert(iterator position, InputIterator first, InputIterator last,
		typename enable_if<is_iterator<typename InputIterator::iterator_category>::value, InputIterator>::type * = 0) {
			while (first != last) {
				insert(position, *first);
				first++;
			}
		}
		iterator	erase(iterator position) {
			node<T> *tmp = position.getptr();
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
			position++;
			delete tmp;
			this->length--;
			return position;
		}
		iterator	erase(iterator first, iterator last) {
			while (first != last) {
				if (first != this->head && first != this->tail)
					first = erase(first);
				else
					first++;
			}
			return first;
		}
		void	swap(list& x) {
			list tmp(x);
			x = *this;
			*this = tmp;
		}
		void	resize(size_type n, value_type val = value_type()) {
			while (this->length > n) {
				pop_back();
			}
			while (this->length < n) {
				push_back(val);
			}
		}
		void	clear() {
			while (this->length) {
				pop_back();
			}
		}
	/* Operations */
		void	splice(iterator position, list& x) {
			this->insert(position, x.begin(), x.end());
			x.clear();			
		}
		void	splice(iterator position, list&x, iterator i) {
			this->insert(position, i.getptr()->data);
			x.erase(i);
		}
		void	splice(iterator position, list&x, iterator first, iterator last) {
			this->insert(position, first, last);
			x.erase(first, last);
		}
		void	remove(const value_type& val) {
			iterator	it = begin();
			while (it != end()) {
				if (*it == val)
					it = erase(it);
				else
					++it;
			}
		}
		template <class Predicate>
		void remove_if (Predicate pred) {
			iterator it = begin();
			while (it != end()) {
				if (pred(*it) == true)
					it = erase(it);
				else
					++it;
			}
			
		}
		void	unique() { /* Not truly unique, only removes consecutive same-value elements */
			iterator it = begin();
			++it;
			while (it != end()) {
				if (*it == it.getprev()->data)
					it = erase(it);
				else
					++it;
			}
		}
		template <class BinaryPredicate>
		void	unique(BinaryPredicate binary_pred) {
			iterator it = begin();
			++it;
			while (it != end()) {
				if (binary_pred(*it, it.getprev()->data))
					it = erase(it);
				else
					++it;
			}
		}
		void	sort() {
			iterator it = begin();
			++it;
			while (it != end()) {
				if (*it < it.getprev()->data) {
					this->swap(it.getptr(), it.getprev());
					it = begin();
				}
				++it;
			}
		}
		template <class Compare>
		void	sort(Compare comp) {
			iterator it = begin();
			++it;
			while (it != end()) {
				if (comp(it, it.getprev()->data)) {
					this->swap(it.getptr(), it.getprev());
					it = begin();
				}
				++it;
			}
		}
		void	merge(list& x) {
			if (&x == this)
				return ;
			iterator it = begin();
			iterator xit = x.begin();
			while (it != end() && xit != x.end()) {
				while (it != end() && *it < *xit) {
					++it;
				}
				++xit;
				this->splice(it, x, xit.getprev());
			}
		}
		template <class Compare>
		void merge (list& x, Compare comp) {
			if (&x == this)
				return ;
			iterator it = begin();
			iterator xit = x.begin();
			while (it != end()) {
				while (it != end() && comp(it, xit)) {
					++it;
				}
				++xit;
				this->splice(it, x, xit.getprev());
			}
		}

		void	reverse() {
			iterator it = begin();	
			while (it != end()) {
				itemswap(it.getptr()->prev, it.getptr()->next);
				it--;
			}
			itemswap(head->prev, head->next);
			itemswap(tail->prev, tail->next);
			itemswap(head, tail);
		}
	private:
		void	trulyunique() {
			iterator	it = begin();
			while (it != end()) {
				value_type val = *it;
				iterator rem = it;
				rem++;
				while (rem != end()) {
					if (*rem == val)
						rem = erase(rem);
					else
						++rem;
				}
				++it;
			}
		}
		void	refreshouterpointers(node<T> *a) {
			if (a->prev)
				a->prev->next = a;
			if (a->next)
				a->next->prev = a;
		}
		void	swap(node<T> *first, node<T> *second) {
			if (first == second)
				return ;
			if (second->next == first) {
        		node<T> *temp = first;
       			first = second;
        		second = temp;
    		}
			node<T>	*swappervector[4] = { first->prev, second->prev, first->next, second->next };
			first->prev = swappervector[2];
			second->prev = swappervector[0];
			first->next = swappervector[3];
			second->next = swappervector[1];
			refreshouterpointers(first);
			refreshouterpointers(second);
		}
	};

/* Relational operators (list) */
template <class T, class Alloc>
bool operator== (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs) {
	return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <class T, class Alloc>
bool operator!= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
	return !(lhs == rhs);
}

template <class T, class Alloc>
bool operator<  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class T, class Alloc>
bool operator>  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
	return (rhs < lhs);
}

template <class T, class Alloc>
bool operator<= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
	return !(rhs < lhs);
}

template <class T, class Alloc>
bool operator>= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
	return !(lhs < rhs);
}

template <class T, class Alloc>
void swap (list<T,Alloc>& x, list<T,Alloc>& y) {
	list<T, Alloc> tmp(x);
	x = y;
	y = tmp;
}
  
} // namespace ft
#endif
