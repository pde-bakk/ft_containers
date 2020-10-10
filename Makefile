# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: Peer <pde-bakk@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2020/07/25 17:28:30 by pde-bakk      #+#    #+#                  #
#    Updated: 2020/10/10 21:50:18 by peerdb        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = containers.out

ifdef COMPILER
 CXX = $(COMPILER)
endif

CXXFLAGS = -W -Wall -Wextra -Werror -pedantic -std=c++98 -ansi 
ifdef DEBUG
 CXXFLAGS += -g -fsanitize=address
endif

FILES = main.cpp
ifdef STD
 FILES = stdmain.cpp
endif

# all: $(NAME)

# $(NAME):
# 	$(CXX) $(FILES) $(CXXFLAGS) -o $(NAME)

list: fclean
	$(CXX) $(CXXFLAGS) list_$(FILES) -o $(NAME)

vector: fclean
	$(CXX) $(CXXFLAGS) vector_$(FILES) -o $(NAME)

map: fclean
	$(CXX) $(CXXFLAGS) map_$(FILES) -o $(NAME)
	
clean:

fclean: clean
	@rm -f $(NAME)

fuckingclean: fclean
	@rm -f std.txt ft.txt *stdmain.cpp diff.txt

re: fclean

 