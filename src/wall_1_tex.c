/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_1_tex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:47:04 by alimpens          #+#    #+#             */
/*   Updated: 2024/06/27 11:48:57 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_test_texture_north(t_game *game)
{
	game->north_texture = mlx_load_png("textures/32_tri.png");
	game->image_north_texture = 
		mlx_texture_to_image(game->mlx, game->north_texture);
}

void	load_test_texture_south(t_game *game)
{
	game->south_texture = mlx_load_png("textures/32_bronto.png");
	game->image_south_texture = 
		mlx_texture_to_image(game->mlx, game->south_texture);
}

void	load_test_texture_west(t_game *game)
{
	game->west_texture = mlx_load_png("textures/32_ptero.png");
	game->image_west_texture = 
		mlx_texture_to_image(game->mlx, game->west_texture);
}

void	load_test_texture_east(t_game *game)
{
	game->east_texture = mlx_load_png("textures/32_tyr.png");
	game->image_east_texture = 
		mlx_texture_to_image(game->mlx, game->east_texture);
}

void	project_test_texture_north(void *param)
{
	t_game		*game;
	uint32_t	x;
	uint32_t	y;
	uint32_t	color;

	game = (t_game *)param;
	x = 0;
	y = 0;
	while (y < game->image_north_texture->width)
	{
		while (x < game->image_north_texture->height)
		{
			color = put_pixel_color(game->image_north_texture, x, y);
			reverse_bits(&color);
			mlx_put_pixel(game->image, x, y, color);
			x++;
		}
		x = 0;
		y++;
	}
}
