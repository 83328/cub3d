/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:53:50 by alimpens          #+#    #+#             */
/*   Updated: 2024/05/06 11:45:54 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int get_map_height(int fd)
{
	char	c;
	int		map_height;
	int		non_empty_line_count;
	int		non_empty_line;

	map_height = 0;
	non_empty_line_count = 0;
	non_empty_line = 0;
	while (read(fd, &c, 1) > 0)
	{
		if(c == '\n')
		{
			if (non_empty_line && ++non_empty_line_count > 6)
				map_height++;
			non_empty_line = 0;
		}
		else if (c != ' ' && c != '\t')
			non_empty_line = 1;
	}
	if (non_empty_line && non_empty_line_count >= 6)
		map_height++;
	return (map_height);
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
		else
			current_length++;
	}
	if(current_length > max_length)
		max_length = current_length;
	lseek(fd, 0, SEEK_SET);
	return (max_length);
}

int	load_map(t_game *game, char *filename)
{
	int		fd;
	char	*line;
	t_map	*map;
	int		i;
	char	first_char;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("Could not open file %s\n", filename);
		return (0);
	}
	// Read the first character of the file, ust as a test, will remove later
	if (read(fd, &first_char, 1) != 1)
	{
		printf("Could not read from file %s\n", filename);
		close(fd);
		return (0);
	}
	printf("First character of the file: %c\n", first_char);
	// Move the file pointer back to the beginning of the file
	lseek(fd, 0, SEEK_SET);

	map = malloc(sizeof(t_map));
	if (map == NULL)
	{
		close(fd);
		return (0);
	}
	map->height = get_map_height(fd);
 	map->width = get_max_line_length(fd);
	//map->start = get_map_start(fd);
	map->map = malloc(sizeof(char *) * map->height);
	if (map->map == NULL)
	{
		free(map);
		close(fd);
		return (0);
	}
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		map->map[i] = line;
		i++;
	}
	game->map = map;
	printf("Height: %d\n", map->height);
	printf("Width: %d\n", map->width);
	close(fd);
	return (1);
}

/* void	parse_cub_file(char *path, t_player *player, mlx_t *mlx)
{
	int fd;
	char *line;
	char **words;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		// Handle error
		return ;
	}
	while (get_next_line(fd, &line) > 0)
	{
		words = ft_split(line, ' ');
		if (words[0][0] == 'N' && words[0][1] == 'O')
			load_texture(mlx, player, words[1], 0);
		else if (words[0][0] == 'S' && words[0][1] == 'O')
			load_texture(mlx, player, words[1], 1);
		else if (words[0][0] == 'W' && words[0][1] == 'E')
			load_texture(mlx, player, words[1], 2);
		else if (words[0][0] == 'E' && words[0][1] == 'A')
			load_texture(mlx, player, words[1], 3);
		else if (words[0][0] == 'F')
			set_floor_color(ft_split(words[1], ','));
		else if (words[0][0] == 'C')
			set_ceiling_color(ft_split(words[1], ','));
		else if (ft_strchr("012NSEW", words[0][0]))
			add_map_line(words[0]);
		free(line);
		free(words);
	}
	validate_map();
	close(fd);
} */
