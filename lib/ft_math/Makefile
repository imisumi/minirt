# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#              #
#    Updated: 2023/07/14 02:05:52 by ichiro           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME       := math.a
HEADER     := includes/math.h
CC         := gcc
CFLAGS     := 
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
        vec4/vec4.c \
        temp.c


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
