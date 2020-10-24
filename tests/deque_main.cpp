//
// Created by Peer De bakker on 10/24/20.
//

#include "Deque.hpp"
#include <deque>
#include <string>
#include <iostream>
#include <sys/time.h>
#include <cstring>
#include <stdlib.h>

# if defined(unix) || defined(__unix__) || defined(__unix)
#  define LINUX 1
# else
#  define LINUX 0
# endif

size_t begintime;
size_t endtime;
struct timeval	tv;

template< typename K, typename V >
void	print_container_content(ft::deque<K, V>& mappie, const std::string& name = "container") {
	std::cout << name << " contains:\n";
	for (typename ft::deque<K, V>::const_iterator it = mappie.begin(); it != mappie.end(); it++)
		std::cout << it->first << " => " << it->second << std::endl;
	std::cout << " $" << std::endl;
}

void 	peer() {
	ft::deque<int>	hats;
	hats.insert(0);
	hats.insert(2);
	hats.insert(4);
	hats.insert(0);
	hats.insert(8);

	print_container_content(hats);
	std::cout << "hats size = " << hats.size();
	std::cout << "count of 'a' = " << hats.count('a');
	std::cout << "count of 'b' = " << hats.count('b');
	std::cout << "count of 'c' = " << hats.count('c');
}


int	main(int argc, char **argv) {
	if (argc >= 2 && strcmp(argv[1], "time") == 0) {
		gettimeofday(&tv, NULL);
		begintime = tv.tv_usec;
	}
	peer();
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
