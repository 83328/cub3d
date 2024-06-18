/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:53:50 by alimpens          #+#    #+#             */
/*   Updated: 2024/06/18 11:27:43 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_map_height(int fd)
{
	char	c;
	int		map_height;
	int		non_empty_line_count;
	int		non_empty_line;
	//int		map_start;

	map_height = 0;
	non_empty_line_count = 0;
	non_empty_line = 0;
	while (read(fd, &c, 1) > 0)
	{
		if(c == '\n')
		{
			/*
			this line checks the file and jumps to the seventh line of the file
			the actual map coordinates start there
			
			if (non_empty_line && ++non_empty_line_count > 6)
			
			*/
			if (non_empty_line && non_empty_line_count >= 0)
				map_height++;
			non_empty_line = 0;
		}
		else if (c != ' ' && c != '\t')
			non_empty_line = 1;
	}
	if (non_empty_line && non_empty_line_count >= 6)
		map_height++;
	return (map_height + 1);
}

/* int	get_map_start(int fd)
{
	char	*line;
	int		total_line_count;
	int		non_empty_line_count;

	total_line_count = 0;
	non_empty_line_count = 0;
	while(read(fd, &line, 1) > 0)
	{
		total_line_count++;
		if(line[0] != '\0' && ++non_empty_line_count == 7)
		{
			free(line);
			return (total_line_count);
		}
		free(line);
	}
	if(non_empty_line_count == 6)
		return (total_line_count + 1);
	return -1;
} */

/* int get_max_line_length(int fd)
{
	char ch;
	int max_length;
	int current_length;

	max_length = 0;
	current_length = 0;
	lseek(fd, 0, SEEK_SET);
	while(read(fd, &ch, 1) > 0)
	{
		if(ch == '\n')
		{
			if(current_length > max_length)
			{
				max_length = current_length;
			}
			current_length = 0;
		}
		else
			current_length++;
	}
	if(current_length > max_length)
		max_length = current_length;
	lseek(fd, 0, SEEK_SET);
	return (max_length);
} */

int get_max_line_length(int fd)
{
	char ch;
	int max_length;
	int current_length;

	max_length = 0;
	current_length = 0;
	lseek(fd, 0, SEEK_SET);
	while(read(fd, &ch, 1) > 0)
	{
		if(ch == '\n')
		{
			if(current_length > max_length)
			{
				max_length = current_length;
			}
			current_length = 0;
		}
		else if (ch != ' ')  // ignore spaces
			current_length++;
	}
	if(current_length > max_length)
		max_length = current_length;
	lseek(fd, 0, SEEK_SET);
	return (max_length);
}
