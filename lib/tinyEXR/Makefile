# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/28 00:51:40 by ichiro            #+#    #+#              #
#    Updated: 2024/04/22 20:35:36 by imisumi-wsl      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CYAN=\033[1;36m
NC=\033[0m


# tinyexr.o: tinyexr.cc
# 	g++ -O2 -c -I./dep tinyexr.cc main.c -lm
# 	@echo "$(CYAN)[Compiled tinyexr.o]$(NC)"


# all: tinyexr.o

# clean:
# 	rm -rf *.o




SRC = tinyexr.cc

OBJ = tinyexr.o

CFLAGS = -O2 -I./dep

$(OBJ): $(SRC)
	g++ $(CFLAGS) -c $< -o $@
	@echo "$(CYAN)[Compiled $@]$(NC)"

all: $(OBJ)

clean:
	rm -f $(OBJ)

re: clean all
