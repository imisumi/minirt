# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/28 00:51:40 by ichiro            #+#    #+#              #
#    Updated: 2023/06/07 12:26:16 by imisumi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

HEADER = includes/fdf.h

CFLAGS = -g -I include

LEAKS = -fsanitize=address

cc = gcc 

UNAME := $(shell uname -m)
LFLAGS = -framework Cocoa -framework OpenGl -framework IOKit -lm

ifeq ($(UNAME), x86_64)
	LFLAGS += -lglfw3
else
	LFLAGS += -lglfw
endif

MLX = lib/MLX42/build/libmlx42.a
LIBFT = lib/libft/libft.a

OBJS_DIR = objs
SRC_DIR = src

GREEN := \033[1;32m
RED := \033[1;31m
BLUE := \033[1;34m
PINK := \033[1;38;5;206m
NC := \033[0m

INC := -I $(INCLUDE_DIR)

SRCS = main.c \
		vec.c \
		key_hook.c
		
OBJS = $(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))

all: $(LIBFT) $(MLX) $(NAME)
	@echo "$(GREEN)[Completed fdf]$(NC)"

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)[Compiling $<]$(NC)"
	@$(cc) $(CFLAGS) $(INC) -I -c -o $@ $<

$(LIBFT):
	@$(MAKE) -C lib/libft

$(MLX):
	@echo "$(BLUE)[Compiling MLX]$(NC)"
	@cd ./lib/MLX42 && cmake -DBUILD_TESTS=ON -B build && cmake --build build --parallel
	@echo "$(GREEN)[Completed MLX]$(NC)"
	
$(NAME): $(MLX) $(LIBFT) $(OBJS)
	@$(cc) $(CFLAGS) $(INC) -I $^ -o $(NAME) $(LFLAGS)

run: all
	./miniRT
	
git:
	git add .
	git commit -m "$(m)"
	git push

clean:
	@rm -rf $(OBJS_DIR)
	@rm -f libmlx.dylib
	@make clean -C lib/libft
	@echo "$(RED)[Deleted fdf objects]$(NC)"

fclean:
	@rm -rf $(OBJS_DIR)
	@rm -rf $(NAME)
	@make fclean -C lib/libft
	@echo "$(RED)[Deleted fdf objects]$(NC)"
	@echo "$(RED)[Deleted fdf]$(NC)"

mlxclean:
	@rm -rf ./lib/MLX42/build
	@echo "$(RED)[Deleted MLX]$(NC)"

re: fclean all

.PHONY: all clean fclean re
