/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/06 12:46:40 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/09/16 21:22:50 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "srcs/List/list.hpp"
#include <list>
#include <string>
#include <cstdlib>

void	constants(void)
{
	ft::list<int> myList;
	std::cout << "myList.empty() = " << myList.empty() << std::endl;
	std::cout << "myList.front() = " << myList.front() << std::endl;
	std::cout << "myList.back() = " << myList.back() << std::endl;
	for (int i = 0; i < 20; i++)
		myList.push_front(i * 7);
	std::cout << "myList.front() = " << myList.front() << std::endl;
	std::cout << "myList.back() = " << myList.back() << std::endl;
	
	std::cout << "before making myConstLIst" << std::endl;
	const ft::list<int> myConstList(size_t(8), 7);
	ft::list<int>::const_iterator cit = myConstList.begin();
	ft::list<int>::const_iterator cite = myConstList.end();
	while (cit != cite)
	{
		// std::cout << *cit << "\t";
		cit++;
	}
	std::cout << std::endl;
	std::cout << "haha" << std::endl;
}

int peer() {
	ft::list<int> l((size_t)8, 42);
	
	for (int i = 0; i < 10; i++)
		l.push_front(i * 3);
	while (l.size())
		l.pop_front();
	std::cout << "l.size() = " << l.size() << std::endl;
	std::cout << "l.max_size() = " << l.max_size() << std::endl;
	return 0;
}

int main() {
	srand(time(0));
	// peer();
	constants();
	// system("leaks containers.out");
	//thx djevayo for the pr
}
