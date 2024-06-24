/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_map_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:30:46 by alimpens          #+#    #+#             */
/*   Updated: 2024/06/23 18:51:21 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_map_surrounded(t_game *game)
{
	int	i;

	i = game->map_start;
	while (i < game->map_cols)
	{
		if (game->map_grid_2d[0][i] != 1 || 
			game->map_grid_2d[game->map_rows - 1][i] != 1)
		{
			ft_error(ERR_MAP_NOT_CLOSED, NULL);
			return ;
		}
		i++;
	}
	i = 0;
	while (i < game->map_rows)
	{
		if (game->map_grid_2d[i][0] != 1 || 
			game->map_grid_2d[i][game->map_cols - 1] != 1)
		{
			ft_error(ERR_MAP_NOT_CLOSED, NULL);
			return ;
		}
		i++;
	}
	printf("The map is surrounded by walls\n");
}

void	print_map_grid_2d(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_rows)
	{
		j = 0;
		while (j < game->map_cols)
		{
			printf("%d ", game->map_grid_2d[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}
