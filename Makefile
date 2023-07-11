# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/28 00:51:40 by ichiro            #+#    #+#              #
#    Updated: 2023/07/11 03:08:38 by ichiro           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = raytracer

HEADER = ./includes/main.h

CFLAGS = -g 

cc = gcc 

LFLAGS = -framework Cocoa -framework OpenGl -framework IOKit -lm -Ofast -O3 -ffast-math -flto

UNAME := $(shell uname -m)

ifeq ($(UNAME), x86_64)
	LFLAGS += -lglfw3
else
	LFLAGS += -lglfw
endif

MLX = lib/MLX42/build/libmlx42.a
LIBFT = lib/libft/libft.a
MATH = lib/ft_math/math.a

OBJ_DIR = .obj
SRC_DIR = src

GREEN := \033[1;32m
RED := \033[1;31m
BLUE := \033[1;34m
PINK := \033[1;38;5;206m
NC := \033[0m

INC := -I $(INCLUDE_DIR)

SRC =	main.c \
		utils.c \
		camera.c


OBJ = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))

all: $(MLX) $(LIBFT) $(MATH) $(NAME)
	@echo "$(GREEN)[Completed]$(NC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p $(dir $@)
	@echo "$(BLUE)[Compiling $<]$(NC)"
	@$(cc) $(CFLAGS) -I -I -c -o $@ $<
	
$(MLX):
	@echo "$(BLUE)[Compiling MLX]$(NC)"
	@cd ./lib/MLX42 && cmake -DBUILD_TESTS=ON -B build && cmake --build build --parallel
	@echo "$(GREEN)[Completed MLX]$(NC)"

$(LIBFT):
	@$(MAKE) -C lib/libft

$(MATH):
	@$(MAKE) -C lib/ft_math

$(NAME): $(MLX) $(LIBFT) $(MATH) $(OBJ)
	$(cc) $(CFLAGS) -I -I $(LFLAGS) $^ -o $(NAME)

run: all
	./raytracer

test: all
	$(cc) $(CFLAGS) -I -I $(LFLAGS) $(MLX) temp.c -o $(NAME)
	./raytracer

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)[Deleted objects]$(NC)"

fclean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(NAME)
	@echo "$(RED)[Deleted objects]$(NC)"
	@echo "$(RED)[Deleted]$(NC)"

mlxclean:
	@rm -rf ./lib/MLX42/build
	@echo "$(RED)[Deleted MLX]$(NC)"

re: fclean all
	cd ./lib/ft_math && make re

.PHONY: all clean fclean re
