/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:08:39 by ohoro             #+#    #+#             */
/*   Updated: 2024/06/18 14:23:24 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    load_map_dimensions_from_file(t_game *game, char *argv)
{
	int fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		printf("Failed to open file\n");
		return;
	}
	game->map_rows = get_map_height(fd);
	game->map_cols = get_max_line_length(fd);
	game->map_end = game->map_start + game->map_rows;
	close(fd);
}

void    allocate_map(t_game *game)
{
	int i;

	game->map_grid_2d = malloc(sizeof(int *) * game->map_rows);
	if (game->map_grid_2d == NULL)
	{
		printf("Failed to allocate memory for map\n");
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
			printf("Failed to allocate memory for map\n");
			return ;
		}
		i++;
	}
}

void    fill_2d_map_from_file(t_game *game, char argv[1])
{
	int fd = open(argv, O_RDONLY);
	int direction_count;
	
	direction_count = 0;
	if (fd < 0)
	{
		printf("Failed to open file\n");
		return;
	}
	int i = game->map_start;
	while (i < game->map_rows)
	{
		char *line = get_next_line(fd);
		if (line == NULL)
		{
			printf("Failed to read line\n");
			close(fd);
			return;
		}
		int j = 0;
		while (j < game->map_cols)
		{
			if (line[j] == '0')
				game->map_grid_2d[i][j] = 0;
			else if (line[j] == '1')
				game->map_grid_2d[i][j] = 1;
			else if (line[j] == 'N' || line[j] == 'W' || line[j] == 'E' || line[j] == 'S')
			{
				game->map_grid_2d[i][j] = 2;
				game->start_direction = line[j];
				direction_count++;
			}
			else
			{
				ft_error(ERR_INVALID_MAP_CHAR, NULL);
				//printf("Invalid character in map. Only '0' and '1' are allowed.\n");
				free(line);
				close(fd);
				return;
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
		return;
	}
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

/* void    print_map_2d(t_game *game)
{
	for (int i = 0; i < game->map_rows; i++)
	{
		for (int j = 0; j < game->map_cols; j++)
		{
			printf("%d", game->map_grid_2d[i][j]);
		}
		printf("\n");
	}
} */
