/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_load_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:08:39 by ohoro             #+#    #+#             */
/*   Updated: 2024/07/19 14:22:39 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_map_dimensions_from_file(t_game *game, char *argv)
{
	int	fd;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		ft_error(ERR_OPEN, NULL);
		return ;
	}
	game->map_start = get_map_start(fd);
	lseek(fd, 0, SEEK_SET);
	game->map_rows = get_map_height(fd, game->map_start);
	game->map_cols = get_max_line_length(fd, game->map_start, game->map_rows);
	game->map_end = game->map_start + game->map_rows;
	close(fd);
}

void	allocate_map(t_game *game)
{
	int	i;

	game->map_grid_2d = malloc(sizeof(int *) * game->map_rows);
	if (game->map_grid_2d == NULL)
	{
		ft_error(ERR_MEM, NULL);
		return ;
	}
	i = 0;
	while (i < game->map_rows)
	{
		game->map_grid_2d[i] = malloc(sizeof(int) * game->map_cols);
		if (game->map_grid_2d[i] == NULL)
		{
			while (i >= 0)
			{
				free(game->map_grid_2d[i]);
				i--;
			}
			free(game->map_grid_2d);
			ft_error(ERR_MEM, NULL);
			return ;
		}
		i++;
	}
}
