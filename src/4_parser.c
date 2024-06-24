/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:53:50 by alimpens          #+#    #+#             */
/*   Updated: 2024/06/24 10:59:54 by alimpens         ###   ########.fr       */
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
	if (!game->file_path_no || !game->file_path_so || !game->file_path_we || !game->file_path_ea)
	{
		ft_error(ERR_TEX, NULL);
		return (-1);
	}
	return (0);
}

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
		if (c == '\n')
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

int	get_max_line_length(int fd)
{
	char	ch;
	int		max_length;
	int		current_length;

	max_length = 0;
	current_length = 0;
	lseek(fd, 0, SEEK_SET);
	while (read(fd, &ch, 1) > 0)
	{
		if (ch == '\n')
		{
			if (current_length > max_length)
			{
				max_length = current_length;
			}
			current_length = 0;
		}
		else if (ch != ' '&& ch != '\t')
			current_length++;
	}
	if (current_length > max_length)
		max_length = current_length;
	lseek(fd, 0, SEEK_SET);
	return (max_length);
}