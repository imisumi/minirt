# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#              #
#    Updated: 2023/06/25 23:58:24 by ichiro           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME       := math.a
HEADER     := includes/math.h
CC         := gcc
CFLAGS     := -Wall -Werror -Wextra
OBJS_DIR   := .obj/
SRC_DIR    := src/
INCLUDES   := -I includes/math.h

SRCS := vec3/vec3_add.c \
        vec3/vec3_cross.c \
        vec3/vec3_div.c \
        vec3/vec3_dot.c \
        vec3/vec3_mul.c \
        vec3/vec3_normalize.c \
        vec3/vec3_sub.c \
        vec2/vec2.c \
        vec/vec_fill.c \
        vec/vec_create.c \
        vec4/vec4.c 


OBJS := $(addprefix $(OBJS_DIR),$(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	ar -r $(NAME) $(OBJS)

$(OBJS_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -rf $(OBJS_DIR)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
