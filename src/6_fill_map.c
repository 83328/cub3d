/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_fill_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:01:43 by alimpens          #+#    #+#             */
/*   Updated: 2024/06/23 15:41:34 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_2d_map_from_file(t_game *game, char argv[1])
{
	int	fd;
	int	direction_count;
	int	i;

	fd = open(argv, O_RDONLY);
	direction_count = 0;
	if (fd < 0)
	{
		printf("Failed to open file\n");
		return ;
	}
	i = game->map_start;
	while (i < game->map_rows)
	{
		char	*line = get_next_line(fd);
		if (line == NULL)
		{
			printf("Failed to read line\n");
			close(fd);
			return ;
		}
		int j = 0;
		while (j < game->map_cols)
		{
			if (line[j] == '0')
				game->map_grid_2d[i][j] = 0;
			else if (line[j] == '1')
				game->map_grid_2d[i][j] = 1;
			else if (line[j] == 'N' || line[j] == 'W' || 
				line[j] == 'E' || line[j] == 'S')
			{
				game->map_grid_2d[i][j] = 2;
				game->start_direction = line[j];
				direction_count++;
			}
			else
			{
				ft_error(ERR_INVALID_MAP_CHAR, NULL);
				free(line);
				close(fd);
				return ;
			}
			j++;
		}
		free(line);
		i++;
	}
	close(fd);
	if (direction_count != 1)
	{
		ft_error(ERR_START_POINT, NULL);
		return ;
	}
}
