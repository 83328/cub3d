/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_parser_a.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:53:50 by alimpens          #+#    #+#             */
/*   Updated: 2024/07/17 11:41:12 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	process_line2(char *line, int *consecutive_ones)
{
	int	j;
	int	valid_line;

	j = 0;
	valid_line = 1;
	while (line[j])
	{
		if (line[j] == '1')
			(*consecutive_ones)++;
		else if (line[j] != ' ' && line[j] != '\t')
		{
			valid_line = 0;
			break ;
		}
		if (*consecutive_ones == 3 && valid_line)
			return (1);
		j++;
	}
	if (valid_line)
		return (0);
	return (-1);
}

int	get_map_start(int fd)
{
	char	*line;
	int		i;
	int		consecutive_ones;
	int		valid_line;
	int		read_status;

	i = 0;
	read_status = 1;
	while (read_status)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		consecutive_ones = 0;
		valid_line = process_line2(line, &consecutive_ones);
		free(line);
		if (valid_line == 1)
			return (i);
		i++;
	}
	return (-1);
}

void	update_max_length(t_max_length *data)
{
	if (data->line_count >= data->map_start && 
		data->line_count < data->map_start + data->map_rows 
		&& data->current_length > data->max_length)
		data->max_length = data->current_length;
}

int	get_max_line_length(int fd, int map_start, int map_rows)
{
	char			ch;
	t_max_length	data;

	data.max_length = 0;
	data.current_length = 0;
	data.line_count = 0;
	data.map_start = map_start;
	data.map_rows = map_rows;
	lseek(fd, 0, SEEK_SET);
	while (read(fd, &ch, 1) > 0)
	{
		if (ch == '\n')
		{
			update_max_length(&data);
			data.current_length = 0;
			data.line_count++;
			if (data.line_count >= data.map_start + data.map_rows)
				break ;
		}
		else if (ch != ' ' && ch != '\t' && data.line_count >= data.map_start)
			data.current_length++;
	}
	update_max_length(&data);
	lseek(fd, 0, SEEK_SET);
	return (data.max_length);
}
