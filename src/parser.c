/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:53:50 by alimpens          #+#    #+#             */
/*   Updated: 2024/04/23 20:03:56 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_validity(t_map *map)
{
	int		i;
	int		j;
	char	*valid_chars;
	char	*line;

	valid_chars = "01NSEW";
	i = 0;
	while (i < map->height)
	{
		line = map->map[i];
		if (i == 0 || i == map->height - 1 || line[0] != '1' || line[map->width - 1] != '1')
			return (0);
		j = 0;
		while (j < map->width)
		{
			if (ft_strchr(valid_chars, line[j]) == NULL)
				return (0);
			j++;
		}
		i++;
	}
	printf("Height: %d\n", map->height);
	printf("Width: %d\n", map->width);
	return (1);
}

int	load_map(t_game *game, char *filename)
{
	int		fd;
	char	*line;
	t_map	*map;
	int		i;
	char    first_char;

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
