/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/06 12:46:40 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/09/16 22:40:55 by pde-bakk      ########   odam.nl         */
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
	
	const ft::list<int> myConstList(size_t(8), 7);
	ft::list<int>::const_iterator cit = myConstList.begin();
	ft::list<int>::const_iterator cite = myConstList.end();
	while (cit != cite)
	{
		// *cit = 8; // won't compile, because its a const_iterator!
		cit++;
	}
	std::cout << std::endl;
	ft::list<int>::iterator einde = myList.end();
	std::cout << "myList.end() = " << *einde << std::endl;
}

int peer() {
	ft::list<int> l;
	for (int i = 0; i < 8; i++)
		l.push_back(i * 2);
	ft::list<int>::iterator myIt = l.end();
	std::cout << "*myIt = " << *myIt << std::endl;
	myIt--;
	
	for (int i = 0; i < 10; i++)
		l.push_back(i * 3);
	ft::list<int>::iterator tmp = l.insert(myIt, -800);
	std::cout << "tmp = " << &tmp << std::endl;
	for (ft::list<int>::iterator it = l.begin(); it != l.end(); it++)
		std::cout << "*it = " << *it << std::endl;
	// while (l.size())
	// 	l.pop_front();
	// std::cout << "l.size() = " << l.size() << std::endl;
	// std::cout << "l.max_size() = " << l.max_size() << std::endl;
	return 0;
}

int main() {
	srand(time(0));
	// peer();
	constants();
	// system("leaks containers.out");
	//thx djevayo for the pr
}
