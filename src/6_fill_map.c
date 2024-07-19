/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_fill_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:01:43 by alimpens          #+#    #+#             */
/*   Updated: 2024/07/19 15:07:03 by alimpens         ###   ########.fr       */
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

void	process_line(char *line, t_game *game, t_process_args args)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (line[j] != '\n' && line[j] != '\0')
	{
		if (line[j] == '0')
			game->map_grid_2d[args.i][k++] = 0;
		else if (line[j] == '1')
			game->map_grid_2d[args.i][k++] = 1;
		else if (line[j] == 'N' || line[j] == 'W' || 
			line[j] == 'E' || line[j] == 'S')
		{
			game->map_grid_2d[args.i][k] = 2;
			game->start_direction = line[j];
			game->player_x = k * TILE_SIZE + (TILE_SIZE / 2);
			game->player_y = args.i * TILE_SIZE + (TILE_SIZE / 2);
			(*args.direction_count)++;
			k++;
		}
		j++;
	}
	while (k < args.line_length)
		game->map_grid_2d[args.i][k++] = 8;
}

void	process_map_line(int fd, t_game *game, int *direction_count, int i)
{
	char			*line;
	t_process_args	args;

	line = get_next_line(fd);
	if (line == NULL)
	{
		handle_read_line_error(fd);
	}
	args.i = i;
	args.direction_count = direction_count;
	args.line_length = game->map_cols;
	process_line(line, game, args);
	free(line);
}

void	fill_map_grid(int fd, t_game *game)
{
	int	i;
	int	direction_count;

	i = 0;
	direction_count = 0;
	while (i < game->map_rows)
	{
		process_map_line(fd, game, &direction_count, i);
		i++;
	}
	if (direction_count != 1)
	{
		ft_error(ERR_START_POINT, NULL);
		close(fd);
	}
}

void	fill_2d_map_from_file(t_game *game, char argv[1])
{
	int	fd;

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
