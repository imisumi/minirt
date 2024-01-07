# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/28 00:51:40 by ichiro            #+#    #+#              #
#    Updated: 2024/01/03 16:16:06 by imisumi-wsl      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CYAN=\033[1;36m
NC=\033[0m

miniz.o: miniz.c
	gcc -O2 -c -I./ miniz.c -lm
	@echo "$(CYAN)[Compiled miniz.o]$(NC)"

all: miniz.o

clean:
	rm -rf *.o

