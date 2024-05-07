/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_draw_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:44:27 by ohoro             #+#    #+#             */
/*   Updated: 2024/05/07 16:25:42 by ohoro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_vertical_line_left(t_game *game, int x, int y)
{
	t_line line;
	line.x0 = x;
	line.y0 = y;
	line.x1 = x;
	line.y1 = y + TILE_SIZE;
	bresenham(line, game->image);
}

void draw_vertical_line_right(t_game *game, int x, int y)
{
	t_line line;
	line.x0 = x + TILE_SIZE;
	line.y0 = y;
	line.x1 = x + TILE_SIZE;
	line.y1 = y + TILE_SIZE;
	bresenham(line, game->image);
}

void draw_horizontal_line_top(t_game *game, int x, int y)
{
	t_line line;
	line.x0 = x;
	line.y0 = y;
	line.x1 = x + TILE_SIZE;
	line.y1 = y;
	bresenham(line, game->image);
}

void draw_horizontal_line_bottom(t_game *game, int x, int y)
{
	t_line line;
	line.x0 = x;
	line.y0 = y + TILE_SIZE;
	line.x1 = x + TILE_SIZE;
	line.y1 = y + TILE_SIZE;
	bresenham(line, game->image);
}

void draw_rectangle(t_game *game, int x, int y)
{
	draw_vertical_line_left(game, x, y);
	draw_vertical_line_right(game, x, y);
	draw_horizontal_line_top(game, x, y);
	draw_horizontal_line_bottom(game, x, y);
}

void fill_rectangle_white(t_game *game, int x, int y)
{
	for (int i = 0; i < TILE_SIZE; i++)
	{
		for (int j = 0; j < TILE_SIZE; j++)
		{
			mlx_put_pixel(game->image, x + i, y + j, 0xFFFFFFFF);
		}
	}
}

void draw_map(void *param)
{
	t_game *game = (t_game *)param;	
	for (int i = 0; i < MAP_NUM_ROWS; i++)
	{
		for (int j = 0; j < MAP_NUM_COLS; j++)
		{
			if (game->map_grid[i][j] == 0)
			{
				draw_rectangle(game, j * TILE_SIZE, i * TILE_SIZE);
                //printf("0");
			}
			else if (game->map_grid[i][j] == 1)
			{
				fill_rectangle_white(game, j * TILE_SIZE, i * TILE_SIZE);
                //printf("1");
			}
		}
	}
	
}

void draw_minimap(void *param)
{
	t_game *game = (t_game *)param;

	for (int i = 0; i < game->map_rows; i++)
	{
		for (int j = 0; j < game->map_cols; j++)
		{
			if (game->map_grid[i][j] == 0)
			{
				draw_rectangle(game, j * TILE_SIZE, i * TILE_SIZE);
			//	printf("0");
			}
			else if (game->map_grid[i][j] == 1)
			{
				fill_rectangle_white(game, j * TILE_SIZE, i * TILE_SIZE);
			//	printf("1");
			}
		}
	}
	
}
