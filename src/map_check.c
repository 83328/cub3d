/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:30:36 by alimpens          #+#    #+#             */
/*   Updated: 2024/06/17 12:25:41 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_file(int argc, char **argv)
{
	int	i;

	if (argc < 2 || argc > 3)
		ft_error(ERR_ARGS, NULL);
	i = ft_strlen(argv[1]);
	if (ft_strnstr(&argv[1][i - 4], ".cub", 4) == NULL)
		ft_error(ERR_FILETYPE, NULL);
}

void check_map_surrounded(t_game *game)
{
	int i;

	// Check top and bottom rows
	i = 0;
	while (i < game->map_cols)
	{
		if (game->map_grid_2d[0][i] != 1 || game->map_grid_2d[game->map_rows - 1][i] != 1)
		{
			ft_error(ERR_MAP_NOT_CLOSED, NULL);
			return;
		}
		i++;
	}
	// Check left and right columns
	i = 0;
	while (i < game->map_rows)
	{
		if (game->map_grid_2d[i][0] != 1 || game->map_grid_2d[i][game->map_cols - 1] != 1)
		{
			ft_error(ERR_MAP_NOT_CLOSED, NULL);
			return;
		}
		i++;
	}
	printf("The map is surrounded by 1's\n");
}

/* int	check_map_validity(t_map *map)
{
	int		i;
	int		j;
	char	*valid_chars;
	char	*line;

	valid_chars = "01NSEW";
	i = 0;
	while (i < map->height)
	{
		line = map->map[i];
		if (i == 0 || i == map->height - 1 || line[0] != '1' || line[map->width - 1] != '1')
			return (0);
		j = 0;
		while (j < map->width)
		{
			if (ft_strchr(valid_chars, line[j]) == NULL)
				return (0);
			j++;
		}
		i++;
	}
	printf("Height: %d\n", map->height);
	printf("Width: %d\n", map->width);
	return (1);
} */
