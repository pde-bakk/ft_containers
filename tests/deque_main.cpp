//
// Created by Peer De bakker on 10/24/20.
//

#include "Deque.hpp"
#include <deque>
#include <string>
#include <iostream>
#include <sys/time.h>
#include <cstring> // for strcmp
#include <stddef.h>
#include <stdlib.h> // for system()

# if defined(unix) || defined(__unix__) || defined(__unix)
#  define LINUX 1
# else
#  define LINUX 0
# endif

size_t begintime;
size_t endtime;
struct timeval	tv;

template< typename T>
void	print_container_content(ft::deque<T>& d, const std::string& name = "container") {
	std::cout << name << " contains:\n";
	for (typename ft::deque<T>::iterator it = d.begin(); it != d.end(); it++)
		std::cout << *it << std::endl;
	std::cout << " $" << std::endl;
}

void	ctors_dtors() {
	ft::deque<int> def;
	def.push_back(80);
	print_container_content(def, "def");
	ft::deque<int> fill(8, 400);
	print_container_content(fill, "fill");
}

void	capacity() {
	ft::deque<int> eval;
	std::cout << std::boolalpha << "deque is empty? : " << eval.empty() << std::endl;
	for (int i = 0; i < 18; ++i)
		eval.push_back(i);
	std::cout << std::boolalpha << "deque is empty? : " << eval.empty() << std::endl;
	std::cout << "deque.size() = " << eval.size() << std::endl;
	std::cout << "deque.max_size() : " << eval.max_size() << std::endl;
	print_container_content(eval, "eval");
}

void	element_access() {
	ft::deque<int> oldtoothbrush;
	for (int i = 0; i < 389; ++i) {
		std::cout << "i is " << i << std::endl;
		// oldtoothbrush.push_back(i);
		oldtoothbrush.push_front(-i);
	}
	int access[] = {8, 87, 67, 9, 400, 700, 699};
	for (int i = 0; i < 6; ++i)
		std::cout << "deque[" << i << "] gives " << oldtoothbrush[i] << std::endl;
	try {
		for (int i = 0; i < 6; ++i)
			std::cout << "deque.at( " << i << " ) gives " << oldtoothbrush.at(access[i]) << std::endl;
		std::cout << "this one is going to throw an error: " << std::endl;
		std::cout << "deque.at(1000) gives: " << oldtoothbrush.at(1000) << std::endl;	
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		std::cout << "exception msg is allowed to differ from STL" << std::endl;
	}
	std::cout << "deque.front(): " << oldtoothbrush.front() << std::endl;
	std::cout << "deque.back(): " << oldtoothbrush.back() << std::endl;
}


int	main(int argc, char **argv) {
	if (argc >= 2 && strcmp(argv[1], "time") == 0) {
		gettimeofday(&tv, NULL);
		begintime = tv.tv_usec;
	}
	ctors_dtors();
	capacity();
	element_access();
	if (argc >= 2 && strcmp(argv[1], "time") == 0) {
		gettimeofday(&tv, NULL);
		endtime = tv.tv_usec;
		std::cerr << "Time elapsed in total! = " << endtime - begintime << " nanoseconds" << std::endl;
	}
	if (argc == 3 && strcmp(argv[2], "leaks") == 0 && !LINUX) {
		int a = system("leaks containers.out | grep \"total leaked bytes\" >&2");
		(void)a;
	}
}
