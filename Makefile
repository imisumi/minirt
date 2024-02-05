# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/28 00:51:40 by ichiro            #+#    #+#              #
#    Updated: 2024/02/05 14:32:05 by imisumi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minirt

CFLAGS = -I$(INCDIR)
# CFLAGS += -I./lib/MLX42/include/MLX42
CFLAGS += -I./lib/libft/includes/
CFLAGS += -I./lib/lib3d/includes/
CFLAGS += -I./lib/MLX42/include/
CFLAGS += -I./tinyEXR/

# CFLAGS = -I./includes

CC = gcc -O2
# CC += -g -fsanitize=thread -pthread
# CC += -Wuninitialized -Wall -Wextra -Werror

SRCDIR		:= src
INCDIR		:= includes
OBJDIR		:= .obj

MLX = lib/MLX42/build/libmlx42.a
LIBFT = lib/libft/libft.a
LIB3D = lib/lib3d/lib3d.a

SOURCES		= $(wildcard $(SRCDIR)/**/*.c) $(wildcard $(SRCDIR)/*.c)
SOURCES += ./lib/MLX42/lib/png/lodepng.c
OBJECTS		= $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

RED=\033[1;31m
PINK=\033[1;35m
CYAN=\033[1;36m
GREEN=\033[0;32m
NC=\033[0m

#	MLX42
LFLAGS = -lglfw -L./lib/MLX42/build/ -lmlx42 -g
#	libft
LFLAGS += -L./lib/libft/ -lft
#	lib3d
LFLAGS += -L./lib/lib3d/ -l3d

# c++ for tinyexr
LFLAGS += -lstdc++


OS := $(shell uname -m)
ifeq ($(OS), arm64)
LFLAGS += -framework Cocoa -framework OpenGl -framework IOKit -lglfw
$(info arm64)
else ifeq ($(OS),x86_64)
LFLAGS += -ldl -lglfw -pthread -lm
$(info x86_64)
endif

# tinyEXR:
# 	$(MAKE) -C tinyEXR


# include ./tinyEXR/Makefile

# $(NAME): $(OBJECTS) $(MLX) $(LIBFT) $(LIB3D)
# 	$(CC) $(CFLAGS) $(LFLAGS) $^ -o $@ ./tinyEXR/tinyexr.o ./tinyEXR/dep/miniz.o -lstdc++ $(LFLAGS)

# OBJECTS += ./tinyEXR/tinyexr.o ./tinyEXR/dep/miniz.o

TINYEXR = ./tinyEXR/tinyexr.o ./tinyEXR/dep/miniz.o

$(TINYEXR):
	$(MAKE) -C tinyEXR
	$(MAKE) -C tinyEXR/dep
	$(eval OBJECTS += ./tinyEXR/tinyexr.o ./tinyEXR/dep/miniz.o)

# tinyEXR:
# 	$(MAKE) -C tinyEXR

$(NAME): $(OBJECTS) $(MLX) $(LIBFT) $(LIB3D) $(TINYEXR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LFLAGS)
# $(CC) $(CFLAGS) $^ ./tinyEXR/tinyexr.o ./tinyEXR/dep/miniz.o -o $@ -lstdc++ $(LFLAGS)


# $(NAME): $(OBJECTS) $(MLX) $(LIBFT) $(LIB3D)
# 	$(CC) $(CFLAGS) $(LFLAGS) $^ -o $@ $(LFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ 
	@echo "$(CYAN)[Compiled $@]$(NC)"

$(MLX):
	git submodule update --init --recursive lib/MLX42
	cd ./lib/MLX42 && cmake -B build && cmake --build build --parallel

$(LIBFT):
	$(MAKE) -C lib/libft

$(LIB3D):
	@$(MAKE) -C lib/lib3d
# -I./tinyEXR/ -I./tinyEXR/dep/ ./tinyEXR/tinyexr.o ./tinyEXR/dep/miniz.o -lstdc++
all: $(NAME)
	@echo "$(GREEN)[Compiled $(NAME)]$(NC)"
#	@$(CC) -O3 $(CFLAGS) $(LFLAGS) $(SOURCES)

run: all
	./$(NAME)

val: all
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

rerun: re
	./$(NAME)

clean:
	@rm -rf $(OBJDIR)
	@echo "$(RED)[Deleted $(NAME) objects]$(NC)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(RED)[Deleted $(NAME)]$(NC)"

re: fclean all

.PHONY: all clean fclean re
