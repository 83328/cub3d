/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:56:41 by ohoro             #+#    #+#             */
/*   Updated: 2024/04/21 18:27:32 by ohoro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <MLX42/MLX42.h>

#define WIDTH 512
#define HEIGHT 512
#define M_PI_2 1.57079632679489661923

typedef struct s_game
{
	mlx_t						*mlx;
	mlx_image_t					*image;
	float						player_x;
	float						player_y;
	float						player_width;
	float						player_height;
	float						player_rotation_angle;
	bool						key_a_pressed;
	bool						key_s_pressed;
	bool						key_d_pressed;
	bool						key_w_pressed;
	bool						key_left_pressed;
	bool						key_right_pressed;
	
}	t_game;


typedef struct line
{
	int32_t	x0;
	int32_t	y0;
	int32_t	x1;
	int32_t	y1;
}	t_line;

// key_commands.c
void	handle_rotation_keys(mlx_key_data_t keydata,	t_game *game);
void	handle_movement_keys(mlx_key_data_t keydata,	t_game *game);
void	handle_escape_key(mlx_key_data_t keydata);
void	my_keyhook(mlx_key_data_t keydata, void	*param);
void	reset_keys(t_game *game);

// graphics_helper.c
int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void	put_pixel(int32_t x, int32_t y, mlx_image_t *image);
void	erase_pixel(int32_t x, int32_t y, mlx_image_t *image);
int32_t	get_step(int32_t start, int32_t end);
int32_t	get_error(int32_t dx, int32_t dy);
void	bresenham(t_line line, mlx_image_t *image);
// player_movements.c
void	erase_old_player(t_game *game);
void	update_player(t_game *game);
void	draw_new_player(t_game *game);
void	redraw_player(void *param);
// player_rays.c
void	draw_player_middle_ray(t_game *game);
