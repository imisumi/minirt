# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/07 14:31:38 by imisumi           #+#    #+#              #
#    Updated: 2023/09/09 00:07:30 by imisumi-wsl      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	lib3d.a
CC			:=	gcc
CFLAGS 		:=	-g
LFLAGS		:=	-lm

HEADERS		:=	./includes/lib3d.h

OBJ_DIR		:=	.objs/
SRC_DIR		:=	srcs/

VEC2_DIR	:=	$(SRC_DIR)vec2/
VEC3_DIR	:=	$(SRC_DIR)vec3/
VEC4_DIR	:=	$(SRC_DIR)vec4/
MAT4_DIR	:=	$(SRC_DIR)mat4/
QUAT_DIR	:=	$(SRC_DIR)quat/

SRCS		:=	$(VEC2_DIR)vec2.c \
				$(VEC3_DIR)vec3.c \
				$(VEC4_DIR)vec4.c \
				$(MAT4_DIR)mat4.c \
				$(QUAT_DIR)quat.c


INCLUDES	:=	$(addprefix -I, $(sort $(dir $(HEADERS))))
OBJS		:=	$(addprefix $(OBJ_DIR),$(SRCS:c=o))

GREEN		:=	\033[1;32m
RED			:=	\033[1;31m
BLUE		:=	\033[1;34m
PINK		:=	\033[1;38;5;206m
NC			:=	\033[0m
# RESET_LINE	:=	\033[1A\033[K

$(NAME): $(OBJS)
	@echo "$(PINK)[Creating $(NAME)]$(NC)"
	@ar -rcs $(NAME) $(OBJS)
				
$(OBJ_DIR)%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ $(LFLAGS)
	@echo "$(BLUE)[Compiling $<]$(NC)"
	@printf "$(RESET_LINE)"

all: $(NAME)
	@echo "$(GREEN)[Done]$(NC)"

clean:
	@if [ -d "$(OBJ_DIR)" ]; then \
		rm -rf "$(OBJ_DIR)"; \
		echo "$(RED)[Removed $(NAME) obj files]$(NC)"; \
	fi

fclean: clean
	@if [ -e "$(NAME)" ]; then \
		rm -f "$(NAME)"; \
		echo "$(RED)[Removed $(NAME)]$(NC)"; \
	fi

re: fclean all

.PHONY:	all clean fcleam re
