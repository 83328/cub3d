/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:14:32 by alimpens          #+#    #+#             */
/*   Updated: 2024/06/27 12:15:20 by alimpens         ###   ########.fr       */
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
