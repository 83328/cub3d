/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:06:07 by ohoro             #+#    #+#             */
/*   Updated: 2024/05/03 11:07:07 by ohoro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool has_wall_at(t_game game, float  x, float y)
 {
	 if (x < 0 || x >= MAP_NUM_COLS * TILE_SIZE || y < 0 || y >= MAP_NUM_ROWS * TILE_SIZE)
	 {
		 return (true);
	 }
	 int map_grid_index_x = floor(x / TILE_SIZE);
	 int map_grid_index_y = floor(y / TILE_SIZE);
	 return (game.map_grid[map_grid_index_y][map_grid_index_x] != 0);
 }

bool is_inside_map(float x, float y)
{
	return (x >= 0 && x <= MAP_NUM_COLS * TILE_SIZE && y >= 0 && y <= MAP_NUM_ROWS * TILE_SIZE);
}

int get_map_at(t_game game, int i, int j)
{
	return (game.map_grid[i][j]);
}