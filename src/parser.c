/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:53:50 by alimpens          #+#    #+#             */
/*   Updated: 2024/04/25 11:31:15 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* int get_file_line_count(int fd)
{
	char ch;
	int line_count = 0;

	// Move the file pointer back to the beginning of the file
	lseek(fd, 0, SEEK_SET);

	while(read(fd, &ch, 1) > 0)
	{
		if(ch == '\n')
		{
			line_count++;
		}
	}
	// Move the file pointer back to the beginning of the file
	lseek(fd, 0, SEEK_SET);

	return line_count;
}

int get_max_line_length(int fd)
{
	char ch;
	int max_length = 0;
	int current_length = 0;

	// Move the file pointer back to the beginning of the file
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
		{
			current_length++;
		}
	}

	// Check if the last line is the longest
	if(current_length > max_length)
	{
		max_length = current_length;
	}

	// Move the file pointer back to the beginning of the file
	lseek(fd, 0, SEEK_SET);

	return max_length;
} */

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

	// Read the first character of the file
	if (read(fd, &first_char, 1) != 1)
	{
		printf("Could not read from file %s\n", filename);
		close(fd);
		return (0);
	}
	printf("First character of the file: %c\n", first_char);

	// Move the file pointer back to the beginning of the file
	lseek(fd, 0, SEEK_SET);

	// Determine the height and width of the map
	//map->height = get_file_line_count(fd);
 	//map->width = get_max_line_length(fd);

	map = malloc(sizeof(t_map));
	if (map == NULL)
	{
		close(fd);
		return (0);
	}
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
	close(fd);
	return (1);
}

/* int	load_map(t_game *game, char *filename)
{
	int fd;
	char *line;
	t_map *map;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("Could not open file %s\n", filename);
		return (0);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		map = malloc(sizeof(t_map));
		if (map == NULL)
		{
			free(line);
			close(fd);
			return (0);
		}
		map->map = line;
		game->map = map;
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
} */
/* 
int	load_map(t_game *game, char *filename)
{
	int fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("Could not open file %s\n", filename);
		return (0);
	}
	char *line;
	while ((line = get_next_line(fd)) != NULL)
	{
		// Create a new t_map structure and set its map field to the line.
		t_map *map = malloc(sizeof(t_map));
		map->map = line;

		// Assign the new t_map structure to the map field of the game structure.
		game->map = map;
		free(line);
	}
	free(line);
	close(fd);
	return (1);
} */

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
