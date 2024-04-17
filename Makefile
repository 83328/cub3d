NAME		=	cub3d

CC			= cc
CCFLAGS		= -Wall -Wextra -Werror

RM			= rm -rf

MLX42_DIR	= ./MLX42/
MLX42_GIT	= git clone https://github.com/codam-coding-college/MLX42.git $(MLX42_DIR)
MLX42_LIB	= $(MLX42_DIR)/build/libmlx42.a
MLX42_FLG	= -L$(MLX_PATH)/build -lglfw -ldl -lm -pthread

SRCS = cub3d.c \

OBJS = $(SRCS:.c=.o)

%.o: %.c $(DEPS)
	$(CC) $(CCFLAGS) -c $< -o $@

all: mlx42_clone mlx42_build $(NAME)

$(NAME): $(OBJS) $(MLX42_LIB)
	$(CC) $(CFLAGS) $(MLX42_FLG) -o $@ $^

clean:
	$(RM) $(OBJS)
	$(RM) $(MLX42_DIR)/build

fclean: clean
	$(RM) $(NAME)
	$(RM) $(MLX42_DIR)
	$(RM) $(MUSIC_DIR)

re: fclean all

mlx42_clone:
	@if [ ! -d $(MLX42_DIR) ]; then \
		$(MLX42_GIT); \
    fi

mlx42_build:
	@if [ ! -d $(MLX42_DIR)/build ]; then \
		cmake $(MLX42_DIR) -B $(MLX42_DIR)/build; \
		make -C $(MLX42_DIR)/build -j4; \
    fi

.PHONY: all clean fclean re bonus