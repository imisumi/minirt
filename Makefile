# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/28 00:51:40 by ichiro            #+#    #+#              #
#    Updated: 2024/08/07 13:29:45 by imisumi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

CFLAGS = -I$(INCDIR)
CFLAGS += -I./lib/libft/includes/
CFLAGS += -I./lib/lib3d/includes/
CFLAGS += -I./lib/MLX42/include/
CFLAGS += -I./lib/tinyEXR/

CC = gcc -O2
CC += -Wall -Wextra -Werror -g -fsanitize=address
# CC += -g -fsanitize=thread -pthread
# CC += -Wuninitialized -Wall -Wextra -Werror

SRCDIR		:= src
INCDIR		:= includes
OBJDIR		:= .obj

MLX = lib/MLX42/build/libmlx42.a
LIBFT = lib/libft/libft.a
LIB3D = lib/lib3d/lib3d.a
TINYEXR = ./lib/tinyEXR/tinyexr.o ./lib/tinyEXR/dep/miniz.o

SOURCES		= $(wildcard $(SRCDIR)/**/*.c) $(wildcard $(SRCDIR)/*.c)
SOURCES += ./lib/MLX42/lib/png/lodepng.c
OBJECTS		= $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

RED=\033[1;31m
PINK=\033[1;35m
CYAN=\033[1;36m
GREEN=\033[0;32m
NC=\033[0m

#	MLX42
LFLAGS = -lglfw -L./lib/MLX42/build/ -lmlx42
#	libft
LFLAGS += -L./lib/libft/ -lft
#	lib3d
LFLAGS += -L./lib/lib3d/ -l3d
# c++ for tinyexr
LFLAGS += -lstdc++


OS := $(shell uname -m)
UNAME_S := $(shell uname -s)

ifeq ($(OS), arm64)
ifeq ($(UNAME_S), Darwin)
# Try pkg-config first, fallback to homebrew paths
GLFW_CFLAGS := $(shell pkg-config --cflags glfw3 2>/dev/null || echo "-I/opt/homebrew/include")
GLFW_LDFLAGS := $(shell pkg-config --libs-only-L glfw3 2>/dev/null || echo "-L/opt/homebrew/lib")
CFLAGS += $(GLFW_CFLAGS)
LFLAGS += $(GLFW_LDFLAGS)
endif
LFLAGS += -framework Cocoa -framework OpenGl -framework IOKit -lglfw
$(info arm64)
else ifeq ($(OS),x86_64)
ifeq ($(UNAME_S), Darwin)
# Try pkg-config first, fallback to standard paths
GLFW_CFLAGS := $(shell pkg-config --cflags glfw3 2>/dev/null || echo "-I/usr/local/include")
GLFW_LDFLAGS := $(shell pkg-config --libs-only-L glfw3 2>/dev/null || echo "-L/usr/local/lib")
CFLAGS += $(GLFW_CFLAGS)
LFLAGS += $(GLFW_LDFLAGS)
endif
LFLAGS += -ldl -lglfw -pthread -lm
$(info x86_64)
endif


$(NAME): $(OBJECTS) $(MLX) $(LIBFT) $(LIB3D) $(TINYEXR)
	@$(CC) $(CFLAGS) $^ -o $@ $(LFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(CYAN)[Created $@]$(NC)"

$(MLX):
	git submodule update --init --recursive lib/MLX42
	cd ./lib/MLX42 && cmake -B build && cmake --build build --parallel

$(LIBFT):
	$(MAKE) -C lib/libft

$(LIB3D):
	@$(MAKE) -C lib/lib3d

$(TINYEXR):
	$(MAKE) -C lib/tinyEXR/dep
	$(MAKE) -C lib/tinyEXR
	$(eval OBJECTS += ./lib/tinyEXR/tinyexr.o ./lib/tinyEXR/dep/miniz.o)

	
all: $(NAME)
	@echo "$(GREEN)[Compiled $(NAME)]$(NC)"


run: all
	./$(NAME)

norm:
	norminette $(SRCDIR) includes/constants.h includes/darray.h includes/minirt.h includes/struct.h
	norminette lib/libft/src lib/libft/includes
	norminette lib/lib3d/srcs lib/lib3d/includes

rerun: re
	./$(NAME)

clean:
	@rm -rf $(OBJDIR)
	@echo "$(RED)[Deleted $(NAME) objects]$(NC)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(RED)[Deleted $(NAME)]$(NC)"

re: fclean all

libclean:
	$(MAKE) -C lib/tinyEXR clean
	$(MAKE) -C lib/tinyEXR/dep clean
	$(MAKE) -C lib/lib3d fclean
	$(MAKE) -C lib/libft fclean

.PHONY: all clean fclean re
