/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_draw_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:44:27 by ohoro             #+#    #+#             */
/*   Updated: 2024/06/27 10:55:26 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_vertical_line_left(t_game *game, int x, int y)
{
	t_line	line;

	line.x0 = x;
	line.y0 = y;
	line.x1 = x;
	line.y1 = y + TILE_SIZE;
	bresenham(line, game->image);
}

void	draw_vertical_line_right(t_game *game, int x, int y)
{
	t_line	line;

	line.x0 = x + TILE_SIZE;
	line.y0 = y;
	line.x1 = x + TILE_SIZE;
	line.y1 = y + TILE_SIZE;
	bresenham(line, game->image);
}

void	draw_horizontal_line_top(t_game *game, int x, int y)
{
	t_line	line;

	line.x0 = x;
	line.y0 = y;
	line.x1 = x + TILE_SIZE;
	line.y1 = y;
	bresenham(line, game->image);
}

void	draw_horizontal_line_bottom(t_game *game, int x, int y)
{
	t_line	line;

	line.x0 = x;
	line.y0 = y + TILE_SIZE;
	line.x1 = x + TILE_SIZE;
	line.y1 = y + TILE_SIZE;
	bresenham(line, game->image);
}

void	draw_rectangle(t_game *game, int x, int y)
{
	draw_vertical_line_left(game, x, y);
	draw_vertical_line_right(game, x, y);
	draw_horizontal_line_top(game, x, y);
	draw_horizontal_line_bottom(game, x, y);
}

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
