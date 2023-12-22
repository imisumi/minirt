# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/06 12:43:01 by imisumi           #+#    #+#              #
#    Updated: 2023/09/05 20:46:48 by imisumi-wsl      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

HEADER = includes/libft.h

CC = gcc

CFLAGS = -Wall -Werror -Wextra

OBJS_DIR = objs
SRC_DIR = src

GREEN := \033[1;32m
RED := \033[1;31m
BLUE := \033[1;34m
PINK := \033[1;38;5;206m
NC := \033[0m

INCLUDES = -I includes

SRCS =	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
		ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
		ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
		ft_atoi.c \
		ft_calloc.c ft_strdup.c \
		ft_substr.c ft_strjoin.c \
		ft_strtrim.c ft_split.c ft_itoa.c \
		ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
		ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		gnl/get_next_line.c gnl/get_next_line_utils.c

OBJS = $(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))

all: $(NAME)
	@echo "$(GREEN)[Completed libft]$(NC)"

$(NAME): $(OBJS)
	@echo "$(PINK)[Creating libary: libft]$(NC)"
	@ar -r $(NAME) $(OBJS) >/dev/null 2>&1

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)[Compiling $<]$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@printf "\033[1A\033[K"

clean:
	@rm -rf $(OBJS_DIR)
	@echo "$(RED)[Deleted libft objects]$(NC)"

fclean: clean
	@rm -rf $(OBJS_DIR)
	@rm -rf $(NAME)
	@echo "$(RED)[Deleted libft.a]$(NC)"

re: fclean all

.PHONY: all clean fclean re bonus
