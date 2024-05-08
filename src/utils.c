/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:02:49 by alimpens          #+#    #+#             */
/*   Updated: 2024/05/08 16:34:05 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(char *str, t_game *game)
{
	write(2, "Error\n", 6);
	write(2, str, (int)ft_strlen(str));
	if (game)
		free_game(game);
	exit(EXIT_FAILURE);
}

void free_game(t_game *game)
{
	int i;

	if (game)
	{
		if (game->map)
		{
			i = 0;
			while (i < game->map->height)
			{
				free(game->map->map[i]);
				i++;
			}
			free(game->map);
		}
		if (game->mlx)
			free(game->mlx);
		if (game->image)
			free(game->image);
		if (game->map_grid_2d)
		{
			i = 0;
			while (i < game->map_rows)
			{
				free(game->map_grid_2d[i]);
				i++;
			}
			free(game->map_grid_2d);
		}
		free(game);
	}
}
