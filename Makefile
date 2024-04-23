# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/18 14:52:04 by ohoro             #+#    #+#              #
#    Updated: 2024/04/23 17:26:51 by alimpens         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		:= clang
NAME	:= cub3D
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBFT	:= ./lib/libft
GNL		:= ./lib/get_next_line
LIBMLX	:= ./lib/MLX42

HEADERS	:= -I ./include -I $(LIBMLX)/include -I $(GNL)
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm $(LIBFT)/libft.a
SRCS	:= $(shell find ./src -iname "*.c") $(shell find $(GNL) -iname "*.c")
OBJS	:= ${SRCS:%.c=%.o}

all: libmlx libft $(NAME)

libmlx:
	@if [ ! -d "$(LIBMLX)" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX); \
	fi
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
	@make -C $(LIBFT)

%.o: %.c
	@$(CC) $(CFLAGS) $(HEADERS) -o $@ -c $< && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS)
	@$(CC) -v $(OBJS) $(LIBS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build
	@make -C $(LIBFT) clean

fclean: clean
	@rm -rf $(NAME)
	@rm -rf lib/MLX42
	@make -C $(LIBFT) fclean

re: clean all

alpha: all
	@./$(NAME)

.PHONY: all clean fclean re libmlx alpha libft
