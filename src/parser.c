/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:53:50 by alimpens          #+#    #+#             */
/*   Updated: 2024/04/22 14:39:10 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
