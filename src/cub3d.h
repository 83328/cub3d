/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:56:41 by ohoro             #+#    #+#             */
/*   Updated: 2024/04/18 17:33:23 by ohoro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <MLX42/MLX42.h>

#define WIDTH 512
#define HEIGHT 512
#define M_PI_2 1.57079632679489661923

typedef struct s_player
{
	float	x;
	float	y;
	float	width;
	float	height;
	float	rotation_angle;
}	t_player;

typedef struct line
{
	int32_t	x0;
	int32_t	y0;
	int32_t	x1;
	int32_t	y1;
}	t_line;

// key_commands.c
void	handle_rotation(mlx_key_data_t keydata, t_player *player);
void	handle_movement(mlx_key_data_t keydata, t_player *player);
void	handle_escape(mlx_key_data_t keydata);
void	my_keyhook(mlx_key_data_t keydata, void	*param);
// graphics_helper.c
int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void	put_pixel(int32_t x, int32_t y, mlx_image_t *image);
int32_t	get_step(int32_t start, int32_t end);
int32_t	get_error(int32_t dx, int32_t dy);
void	bresenham(t_line line, mlx_image_t *image);