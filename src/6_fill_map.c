/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_fill_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:01:43 by alimpens          #+#    #+#             */
/*   Updated: 2024/06/25 11:21:47 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_2d_map_from_file(t_game *game, char argv[1])
{
	int		fd;
	int		direction_count;
	int		i;
	char	*line;

	fd = open(argv, O_RDONLY);
	direction_count = 0;
	if (fd < 0)
	{
		printf("Failed to open file\n");
		return ;
	}
	i = 0;
	while (i < game->map_start)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			printf("Failed to read line\n");
			close(fd);
			return ;
		}
		free(line);
		i++;
	}
	i = 0;
	while (i < game->map_rows)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			printf("Failed to read line\n");
			close(fd);
			return ;
		}
		int	j = 0;
		int	k = 0;
		while (line[j] != '\n' && line[j] != '\0')
		{
			if (line[j] == '0')
				game->map_grid_2d[i][k++] = 0;
			else if (line[j] == '1')
				game->map_grid_2d[i][k++] = 1;
			else if (line[j] == 'N' || line[j] == 'W' || 
				line[j] == 'E' || line[j] == 'S')
			{
				game->map_grid_2d[i][k++] = 2;
				game->start_direction = line[j];
				direction_count++;
			}
			j++;
		}
		free(line);
		i++;
	}
	close(fd);
	if (direction_count != 1)
		printf("Invalid map: there should be exactly one starting direction\n");
}


/* void	fill_2d_map_from_file(t_game *game, char argv[1])
{
	int		fd;
	int		direction_count;
	int		i;
	char	*line;

	fd = open(argv, O_RDONLY);
	direction_count = 0;
	if (fd < 0)
	{
		printf("Failed to open file\n");
		return ;
	}
	i = 0;
 	while (i < game->map_start)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			printf("Failed to read line\n");
			close(fd);
			return ;
		}
		free(line);
		i++;
	}
	i = 0;
	while (i < game->map_rows)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			printf("Failed to read line\n");
			close(fd);
			return ;
		}
		int	j = 0;
		int	k = 0;
		while (line[j] != '\n' && line[j] != '\0')
		{
			if (line[j] == '0')
				game->map_grid_2d[i][k++] = 0;
			else if (line[j] == '1')
				game->map_grid_2d[i][k++] = 1;
			else if (line[j] == 'N' || line[j] == 'W' || 
				line[j] == 'E' || line[j] == 'S')
			{
				game->map_grid_2d[i][k++] = 2;
				game->start_direction = line[j];
				direction_count++;
			}
			j++;
		}
		free(line);
		i++;
	}
	close(fd);
	if (direction_count != 1)
		printf("Invalid map: there should be exactly one starting direction\n");
} */