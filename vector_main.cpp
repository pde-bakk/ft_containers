/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_main.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/25 21:10:23 by peerdb        #+#    #+#                 */
/*   Updated: 2020/09/27 18:24:15 by peerdb        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/Vector/Vector.hpp"
#include <vector>
#include <string>
#include <iostream>

template< typename T >
void	print_container_content(ft::vector<T> &vec, std::string name) {
	std::cout << name << " contains:";
	for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << ' ' << *it;
	std::cout << " $" << std::endl;
}

void	constructors_test() {
	ft::vector<int> def;
	print_container_content(def, "default constructor");
	ft::vector<int>	fill(8, 42);
	for (int i = 0; i < 8; i++)
		fill.push_back( i );
	print_container_content(fill, "fill constructor");
	ft::vector<int> range(fill.begin(), fill.end());
	print_container_content(range, "range constructor");
	ft::vector<int> copy(range);
	print_container_content(copy, "copy constructor");
	copy = def;
	print_container_content(copy, "assignation operator");
}

void	iterators_test() {
	ft::vector<int> hats;
	for (int i = 0; i < 72; i++)
		hats.push_back(i * 10);
	ft::vector<int>::iterator		it = hats.begin();
	ft::vector<int>::iterator		ite = hats.end();
									ite--;
	ft::vector<int>::const_iterator	cit = hats.begin();
	ft::vector<int>::const_iterator	cite = hats.end();
									cite--;
	std::cout << "*it = " << *it << ", *ite = " << *ite << std::endl;
	ft::vector<int>::reverse_iterator		rit = hats.rbegin();
	ft::vector<int>::reverse_iterator		rite = hats.rend();
	ft::vector<int>::const_reverse_iterator	crit = hats.rbegin();
	ft::vector<int>::const_reverse_iterator	crite = hats.rend();
	std::cout << "*rit = " << *rit << ", *rite = " << *rite << std::endl;
	if (it == cit && cit == it)
		std::cout << "equal works" << std::endl;
	std::cout << "first: " << (it != cite) << ", second: " << (cite != it) << std::endl;
	if (it != cite && cite != it)
		std::cout << "unequal works" << std::endl;
	if (it < cite && !(cite < it))
		std::cout << "smaller than works" << std::endl;
	if (it <= ite && !(cite <= it))
		std::cout << "smaller/equal works" << std::endl;
	if (ite > cit && !(cit > ite))
		std::cout << "bigger than works" << std::endl;
	if (cite >= it && !(it >= cite))
		std::cout << "bigger/equal works" << std::endl;
	ite = it;
	if (rit == crit && crit == rit)
		std::cout << "equal works" << std::endl;
	if (rit != crite && crite != rit)
		std::cout << "unequal works" << std::endl;
	if (rit < crite && !(crite < rit))
		std::cout << "smaller than works" << std::endl;
	if (rit <= rite && !(crite <= rit))
		std::cout << "smaller/equal works" << std::endl;
	if (rite > crit && !(crit > rite))
		std::cout << "bigger than works" << std::endl;
	if (crite >= rit && !(rit >= crite))
		std::cout << "bigger/equal works" << std::endl;
	std::cout << "dereference operator on iterators: " << it[2] << ", " << cit[3] << ", " << rit[4] << ", " << crit[5] << " WORK!" << std::endl;
}

void	capacity_test() {
	ft::vector<int>	papajohns;

	std::cout << "papajohns.empty(): " << papajohns.empty() << std::endl;
	for (int i = 0; i < 10; ++i)
		papajohns.push_back(i);
	std::cout << "papajohns.size(): " << papajohns.size() << std::endl;
	std::cout << "papajohns.max_size(): " << papajohns.max_size() << std::endl;
	std::cout << "papajohns.capacacity(): " << papajohns.capacity() << std::endl;
	std::cout << "papajohns.empty(): " << papajohns.empty() << std::endl;
}

void	element_access_test() {
	ft::vector<int> kokkita;

	for (int i = 0; i < 10; ++i)
		kokkita.push_back(-3 * i);

	const ft::vector<int> constkita(kokkita);
	std::cout << "kokkita[3]: " << kokkita[3] << ", constkita[4]: " << constkita[4] << std::endl;
	try {
		std::cout << "the [] operator does not check if the input value is inbounds of the array" << std::endl;
		std::cout << "the function .at() does check and throws an exception if it is out of bounds, here I'll show you:" << std::endl;
		std::cout << "kokkita.at(13): " << kokkita.at(13) << std::endl;
	}
	catch (std::out_of_range& e) {
		std::cout << "See? it threw an exception" << std::endl;
		// I didnt print e.what(), because diff will see it as different (and wrong) sadface
	}
	std::cout << "kokkita.front() = " << kokkita.front() << ", constkita.front() = " << constkita.front() << std::endl;
	std::cout << "kokkita.back() = " << kokkita.back() << ", constkita.back() = " << constkita.back() << std::endl;
}

void	modifiers_test() {
	ft::vector<int>	tocopy;
	for (int i = 0; i < 14; ++i)
		tocopy.push_back(14 * i);
	ft::vector<int> wap;
	wap.assign(5, 69);
	print_container_content(wap, "after the first assign, wapwap");
	wap.assign(tocopy.begin(), tocopy.end());
	print_container_content(wap, "and after the second, wapwap");
	while (!(tocopy.empty()))
		tocopy.pop_back();
	print_container_content(wap, "wap");
	ft::vector<int>::iterator it = wap.begin() + 2;
	std::cout << "*it = " << *it << std::endl;
	wap.insert(it, 800);
	print_container_content(wap, "after insert, wap");
	tocopy.insert(tocopy.begin(), 1);
	print_container_content(tocopy, "after insert, tocopy");
	
}

int	main() {
	// constructors_test();
	// iterators_test();
	// capacity_test();
	// element_access_test();
	modifiers_test();
	// peer();
}
