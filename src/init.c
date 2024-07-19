/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 15:04:53 by alimpens          #+#    #+#             */
/*   Updated: 2024/07/19 15:05:06 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	init_direction(char direction)
{
	if (direction == 'W')
		return (3.10);
	else if (direction == 'S')
		return (1.50);
	else if (direction == 'N')
		return (4.70);
	else if (direction == 'E')
		return (6.20);
	else
		return (-1);
}

void	init_game(t_game *game)
{
	game->mlx = NULL;
	game->image = NULL;
	game->player_width = 1;
	game->player_height = 1;
	game->player_rotation_angle = init_direction(game->start_direction);
	game->floor_color = 0;
	game->ceiling_color = 0;
}

void	init_test_line(t_line *line)
{
	line->x0 = 100;
	line->y0 = 100;
	line->x1 = 200;
	line->y1 = 200;
}

void	open_and_get_textures(char *filepath, t_game *game)
{
	int	fd;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
	{
		ft_error(ERR_OPEN, NULL);
	}
	get_textures(fd, game);
	close(fd);
}

void	load_all_textures_set_colors(t_game *game, t_validation *v)
{
	load_test_texture_north(game);
	load_test_texture_east(game);
	load_test_texture_south(game);
	load_test_texture_west(game);
	game->ceiling_color = get_rgba(v->c_red, v->c_green, 
			v->c_blue, 255);
	game->floor_color = get_rgba(v->f_red, v->f_green, 
			v->f_blue, 255);
}
