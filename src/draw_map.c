/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:44:27 by ohoro             #+#    #+#             */
/*   Updated: 2024/06/27 12:15:10 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_rectangle_white(t_game *game, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			mlx_put_pixel(game->image, x + i, y + j, 0xFFFFFFFF);
			j++;
		}
		i++;
	}
}

void	draw_map(void *param)
{
	t_game	*game;
	int		i;
	int		j;

	game = (t_game *)param;
	i = 0;
	while (i < game->map_rows)
	{
		j = 0;
		while (j < game->map_cols)
		{
			if (game->map_grid_2d[i][j] == 0 || game->map_grid_2d[i][j] == 2)
			{
				draw_rectangle(game, j * TILE_SIZE, i * TILE_SIZE);
			}
			else if (game->map_grid_2d[i][j] == 1)
			{
				fill_rectangle_white(game, j * TILE_SIZE, i * TILE_SIZE);
			}
			j++;
		}
		i++;
	}
}

void	draw_minimap(void *param)
{
	t_game	*game;
	int		i;
	int		j;

	game = (t_game *)param;
	i = 0;
	while (i < game->map_rows)
	{
		j = 0;
		while (j < game->map_cols)
		{
			if (game->map_grid_2d[i][j] == 0 || game->map_grid_2d[i][j] == 2)
			{
				draw_rectangle(game, j * TILE_SIZE, i * TILE_SIZE);
			}
			else if (game->map_grid_2d[i][j] == 1)
			{
				fill_rectangle_white(game, j * TILE_SIZE, i * TILE_SIZE);
			}
			j++;
		}
		i++;
	}
}
