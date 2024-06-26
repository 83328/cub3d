/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:06:07 by ohoro             #+#    #+#             */
/*   Updated: 2024/06/26 14:54:39 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	has_wall_at(t_game game, float x, float y)
{
	int	map_grid_index_x;
	int	map_grid_index_y;
	int	value;

	map_grid_index_x = floor(x / TILE_SIZE);
	map_grid_index_y = floor(y / TILE_SIZE);
	if (x < 0 || x >= game.map_cols * 
		TILE_SIZE || y < 0 || y >= game.map_rows * TILE_SIZE)
	{
		return (true);
	}
	value = game.map_grid_2d[map_grid_index_y][map_grid_index_x];
	return (value != 0 && value != 2);
}

bool	is_inside_map(t_game game, float x, float y)
{
	return (x >= 0 && x <= game.map_cols * 
		TILE_SIZE && y >= 0 && y <= game.map_rows * TILE_SIZE);
}

int	get_map_at(t_game game, int i, int j)
{
	return (game.map_grid_2d[i][j]);
}
