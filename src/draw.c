/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:52:14 by alimpens          #+#    #+#             */
/*   Updated: 2024/04/22 11:07:20 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* void draw_map(mlx_image_t *image, t_player *player)
{
	int y;
	int x;
	int tile_type;
	int color;
	int dy;
	int dx;

	y = -1;
	while (++y < HEIGHT / TILE_SIZE)
	{
		x = -1;
		while (++x < WIDTH / TILE_SIZE)
		{
			tile_type = map[y][x];
			color = get_tile_color(tile_type);
			dy = -1;
			while (++dy < TILE_SIZE)
			{
				dx = -1;
				while (++dx < TILE_SIZE)
				{
					if (tile_type == WALL)
						put_texture_pixel(x * TILE_SIZE + dx, y * TILE_SIZE + dy, player->textures[get_wall_direction(x, y, player)].image, image);
					else
						put_pixel(x * TILE_SIZE + dx, y * TILE_SIZE + dy, color, image);
				}
			}
		}
	}
} */