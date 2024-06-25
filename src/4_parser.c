/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:53:50 by alimpens          #+#    #+#             */
/*   Updated: 2024/06/25 16:49:52 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_textures(int fd, t_game *game)
{
	char	*line;

	while ((line = get_next_line(fd)) != NULL)
	{
		if (ft_strncmp(line, "NO ", 3) == 0)
			game->file_path_no = ft_strdup(line + 3);
		else if (ft_strncmp(line, "SO ", 3) == 0)
			game->file_path_so = ft_strdup(line + 3);
		else if (ft_strncmp(line, "WE ", 3) == 0)
			game->file_path_we = ft_strdup(line + 3);
		else if (ft_strncmp(line, "EA ", 3) == 0)
			game->file_path_ea = ft_strdup(line + 3);
		free(line);
	}
	if (!game->file_path_no || !game->file_path_so || 
		!game->file_path_we || !game->file_path_ea)
	{
		ft_error(ERR_TEX, NULL);
		return (-1);
	}
	return (0);
}

int	get_map_height(int fd, int map_start)
{
	char	c;
	int		map_height;
	int		line_count;
	int		non_empty_line;

	map_height = 0;
	line_count = 0;
	non_empty_line = 0;
	while (read(fd, &c, 1) > 0)
	{
		if (c == '\n')
		{
			if (non_empty_line && line_count >= map_start)
				map_height++;
			non_empty_line = 0;
			line_count++;
		}
		else if (c != ' ' && c != '\t')
			non_empty_line = 1;
	}
	if (non_empty_line && line_count >= map_start)
		map_height++;
	return (map_height);
}

int	get_map_start(int fd)
{
	char	*line;
	int		i;
	int		consecutive_ones;

	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		int j = 0;
		int valid_line = 1;
		consecutive_ones = 0;
		while (line[j])
		{
			if (line[j] == '1')
				consecutive_ones++;
			else if (line[j] != ' ' && line[j] != '\t')
			{
				valid_line = 0;
				break;
			}
			if (consecutive_ones == 3)
			{
				if (valid_line)
				{
					free(line);
					return (i);
				}
				else
					break;
			}
			j++;
		}
		free(line);
		i++;
	}
	return (-1);
}

int	get_max_line_length(int fd, int map_start, int map_rows)
{
	char	ch;
	int		max_length;
	int		current_length;
	int		line_count;

	max_length = 0;
	current_length = 0;
	line_count = 0;
	lseek(fd, 0, SEEK_SET);
	while (read(fd, &ch, 1) > 0)
	{
		if (ch == '\n')
		{
			if (line_count >= map_start && line_count < map_start + map_rows && current_length > max_length)
				max_length = current_length;
			current_length = 0;
			line_count++;
			if (line_count >= map_start + map_rows)
				break ;
		}
		else if (ch != ' ' && ch != '\t' && line_count >= map_start)
			current_length++;
	}
	if (line_count >= map_start && line_count < map_start + map_rows && current_length > max_length)
		max_length = current_length;
	lseek(fd, 0, SEEK_SET);
	return (max_length);
}
