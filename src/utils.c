/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:02:49 by alimpens          #+#    #+#             */
/*   Updated: 2024/06/26 09:50:17 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(char *str, t_game *game)
{
	write(2, "Error: \n", 8);
	write(2, str, (int)ft_strlen(str));
	if (game)
		free_game(game);
	exit(EXIT_FAILURE);
}

void	free_map(t_game *game)
{
	int	i;

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
}

void	free_map_grid_2d(t_game *game)
{
	int	i;

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
}

void	free_game(t_game *game)
{
	if (game)
	{
		free_map(game);
		if (game->mlx)
			free(game->mlx);
		if (game->image)
			free(game->image);
		free_map_grid_2d(game);
		free(game);
	}
}

/* void	free_game(t_game *game)
{
	int	i;

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
} */
