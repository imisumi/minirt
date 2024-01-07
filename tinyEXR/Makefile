# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/28 00:51:40 by ichiro            #+#    #+#              #
#    Updated: 2024/01/03 23:26:31 by imisumi-wsl      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CYAN=\033[1;36m
NC=\033[0m

# MINIZ = ./dep/miniz.o

# $(MINIZ):
# 	$(MAKE) -C dep

tinyexr.o: tinyexr.cc
	g++ -O2 -c -I./dep tinyexr.cc main.c -lm
	@echo "$(CYAN)[Compiled tinyexr.o]$(NC)"


all: tinyexr.o

clean:
	rm -rf *.o
