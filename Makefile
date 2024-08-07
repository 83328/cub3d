# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/18 14:52:04 by ohoro             #+#    #+#              #
#    Updated: 2024/07/19 11:44:31 by alimpens         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		:= clang
NAME	:= cub3d
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
	@$(CC) $(OBJS) $(LIBS) -o $(NAME)
	@echo "\n"
	@echo "---------------------------------------------------------------------------"
	@echo "\n"
	@echo "                                 bb      333333       dd                   "
	@echo "                    cccc uu   uu bb         3333      dd                   "
	@echo "                  cc     uu   uu bbbbbb    3333   dddddd                   "
	@echo "                  cc     uu   uu bb   bb     333 dd   dd                   "
	@echo "                   ccccc  uuuu u bbbbbb  333333   dddddd                   \n"
	@echo "---------------------------------------------------------------------------"
	@echo "\n"
 
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
	@./$(NAME) ./maps/map2.cub

.PHONY: all clean fclean re libmlx alpha libft
