/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_fill_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:01:43 by alimpens          #+#    #+#             */
/*   Updated: 2024/06/24 11:07:41 by alimpens         ###   ########.fr       */
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
			else if (line[j] == ' ' || line[j] == '\t' || line[j] == '\v' || line[j] == '\f' || line[j] == '\r')
			{
				j++;
				continue;
			}
			else if (line[j] == '\n' || line[j] == '\0')
			{
				while (j < game->map_cols)
				{
					game->map_grid_2d[i][j] = 1;
					j++;
				}
				break;
			}
			printf("%c", line[j]);
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

/* void	fill_2d_map_from_file(t_game *game, char argv[1])
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
			else if (line[j] == ' ' || line[j] == '\t' || line[j] == '\v' || line[j] == '\f' || line[j] == '\r')
			{
				j++;
				continue;
			}
			else if (line[j] == '\n' || line[j] == '\0')
				{
					while (j < game->map_cols)
					{
						game->map_grid_2d[i][j] = 1;
						j++;
					}
					// WARNING: This break statement is not in the original code
					break;
					// WARNING: \n might not be needed
					//line[j] = '\n';
				}
				
			 else
			{
				ft_error(ERR_INVALID_MAP_CHAR, NULL);
				free(line);
				close(fd);
				return ;
			}
			printf("%c", line[j]);
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
} */
