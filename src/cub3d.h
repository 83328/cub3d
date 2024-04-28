/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:56:41 by ohoro             #+#    #+#             */
/*   Updated: 2024/04/28 18:12:28 by ohoro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>
#include <fcntl.h>
#include <MLX42/MLX42.h>
#include "../lib/get_next_line/get_next_line.h"

#define WIDTH 512
#define HEIGHT 512
#define PI 3.14159265358979323846
#define M_PI_2 1.57079632679489661923
#define FOV_ANGLE (60 * (PI / 180))

typedef struct s_map
{
	int width;
	int height;
	//int start;
	char **map;
} t_map;

typedef struct ray
{
	float	ray_angle;
}	t_ray;

typedef struct s_game
{
	mlx_t						*mlx;
	mlx_image_t					*image;
	float						player_x;
	float						player_y;
	float						player_width;
	float						player_height;
	float						player_rotation_angle;
	t_map						*map;
	t_ray						rays[WIDTH];
}	t_game;

typedef struct line
{
	int32_t	x0;
	int32_t	y0;
	int32_t	x1;
	int32_t	y1;
}	t_line;

// key_commands.c
void	handle_movement_and_rotation_keys(mlx_key_data_t keydata, t_game *game);
void	update_player_position(t_game *game, float dx, float dy);
void	update_movement(t_game *game, float move_speed, mlx_key_data_t keydata);
void	handle_escape_key(mlx_key_data_t keydata);
void	my_keyhook(mlx_key_data_t keydata, void	*param);
// key_commands_helper.c
void	update_rotation(t_game *game, mlx_key_data_t keydata);
void	move_forward(t_game *game, float move_speed);
void	move_backward(t_game *game, float move_speed);
void	move_left(t_game *game, float move_speed);
void	move_right(t_game *game, float move_speed);

// graphics_helper.c
int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void	put_pixel(int32_t x, int32_t y, mlx_image_t *image);
void	erase_pixel(int32_t x, int32_t y, mlx_image_t *image);
int32_t	get_step(int32_t start, int32_t end);
int32_t	get_error(int32_t dx, int32_t dy);
void	bresenham(t_line line, mlx_image_t *image);
// player_movements.c
void	draw_new_player(t_game *game);
void	redraw_player(void *param);
void	clear_image(t_game *game);
// player_rays.c
void	draw_player_middle_ray(t_game *game);
void	cast_all_rays(void *param);
// parser.c
int	load_map(t_game *game, char *filename);
//map_check.c
int	check_map_validity(t_map *map);
// math_helper.c
void normalize_angle(float *angle);