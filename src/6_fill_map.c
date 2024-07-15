/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_fill_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:01:43 by alimpens          #+#    #+#             */
/*   Updated: 2024/07/15 15:07:12 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	skip_lines_before_map(int fd, t_game *game)
{
	int		i;
	char	*line;

	i = 0;
	while (i < game->map_start)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			ft_error(ERR_READ_LINE, NULL);
			close(fd);
			exit(1);
		}
		free(line);
		i++;
	}
}

/* void	process_line(char *line, t_game *game, int i, int *direction_count)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (line[j] != '\n' && line[j] != '\0')
	{
		if (line[j] == '0')
			game->map_grid_2d[i][k++] = 0;
		else if (line[j] == '1')
			game->map_grid_2d[i][k++] = 1;
		else if (line[j] == 'N' || line[j] == 'W' || 
			line[j] == 'E' || line[j] == 'S')
		{
			game->map_grid_2d[i][k] = 2;
			game->start_direction = line[j];
			game->player_x = k * TILE_SIZE + (TILE_SIZE / 2);
			game->player_y = i * TILE_SIZE + (TILE_SIZE / 2);
			(*direction_count)++;
			k++;
		}
		j++;
	}
} */

void process_line(char *line, t_game *game, int i, int *direction_count, int line_length)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (line[j] != '\n' && line[j] != '\0')
	{
		if (line[j] == '0')
			game->map_grid_2d[i][k++] = 0;
		else if (line[j] == '1')
			game->map_grid_2d[i][k++] = 1;
		else if (line[j] == 'N' || line[j] == 'W' || 
				 line[j] == 'E' || line[j] == 'S')
		{
			game->map_grid_2d[i][k] = 2;
			game->start_direction = line[j];
			game->player_x = k * TILE_SIZE + (TILE_SIZE / 2);
			game->player_y = i * TILE_SIZE + (TILE_SIZE / 2);
			(*direction_count)++;
			k++;
		}
		j++;
	}
	while (k < line_length)
		game->map_grid_2d[i][k++] = 8;
}

void	fill_map_grid(int fd, t_game *game)
{
	int		i;
	int		direction_count;
	char	*line;

	i = 0;
	direction_count = 0;
	while (i < game->map_rows)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			ft_error(ERR_READ_LINE, NULL);
			close(fd);
			exit(1);
		}
//		process_line(line, game, i, &direction_count);
		process_line(line, game, i, &direction_count, game->map_cols);
		free(line);
		i++;
	}
	if (direction_count != 1)
	{
		ft_error(ERR_START_POINT, NULL);
		close(fd);
		exit(1);
	}
}

void	fill_2d_map_from_file(t_game *game, char argv[1])
{
	int		fd;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		ft_error(ERR_OPEN, NULL);
		return ;
	}
	skip_lines_before_map(fd, game);
	fill_map_grid(fd, game);
	close(fd);
}
