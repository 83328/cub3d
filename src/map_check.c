/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:30:36 by alimpens          #+#    #+#             */
/*   Updated: 2024/05/08 15:15:23 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_file(int argc, char **argv)
{
	int	i;

	if (argc < 2 || argc > 3)
		printf("Error: Not enough arguments\n");
	i = ft_strlen(argv[1]);
	if (ft_strnstr(&argv[1][i - 4], ".cub", 4) == NULL)
		printf("Error: Invalid file extension: use .cub for map files\n");
}
/* void	check_map_start(t_game *game, int fd)
{

} */

/* int	check_map_validity(t_map *map)
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
} */
