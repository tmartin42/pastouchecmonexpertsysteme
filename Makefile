#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fperruch <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/02 19:32:46 by fperruch          #+#    #+#              #
#    Updated: 2017/12/21 17:47:20 by tmartin          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC = g++ # -Wall -Wextra -Werror -g

name = expert_system
SOURCESC = expert.cpp Expr.cpp Fact.cpp main.cpp
SOURCESO = $(SOURCESC:.cpp=.o)
SOURCESH = expert.hpp IElement.hpp Expr.hpp Fact.hpp

OTHER =

all :  $(name)

.cpp.o :
	$(CC) -c $<  -o $@ -I.

$(name) : $(SOURCESO) $(SOURCESH)
	$(CC) -o $(name) $(SOURCESO) -I.

clean :
	/bin/rm -f $(SOURCESO)
	/bin/rm -f *~

fclean : clean
	/bin/rm -f $(name)

re : fclean all

add : fclean
	git add Makefile auteur $(SOURCESC) $(SOURCESH) $(OTHER)
	git commit -m "modif"
	git push
	git status
