/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:44:02 by ohoro             #+#    #+#             */
/*   Updated: 2024/07/18 16:36:50 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_textures_and_colors(t_validation *validation)
{
	if (validation->north_texture != 1 || validation->south_texture != 1 
		|| validation->west_texture != 1 || validation->east_texture != 1)
	{
		ft_error(ERR_TEX, NULL);
	}
	if (validation->floor_color_num != 1 || validation->ceiling_color_num != 1)
		ft_error(ERR_COLOR, NULL); 
}

void	process_file_lines(int fd, t_validation *validation, int map_start_line)
{
	char	*line;
	int		i;

	i = map_start_line;
	line = get_next_line(fd);
	while (line && i)
	{
		line_check_textures(line, validation);
		color_check(line, validation);
		free(line);
		line = get_next_line(fd);
		i--;
	}
}

void	validate_file(t_game *game, char *file, t_validation *validation)
{
	int	fd;

	validation->map_start_line = game->map_start;
	validation->north_texture = 0;
	validation->south_texture = 0;
	validation->west_texture = 0;
	validation->east_texture = 0;
	validation->floor_color_num = 0;
	validation->ceiling_color_num = 0;
	validation->f_red = 0;
	validation->f_green = 0;
	validation->f_blue = 0;
	validation->c_red = 0;
	validation->c_green = 0;
	validation->c_blue = 0;
	fd = open(file, O_RDONLY);
	process_file_lines(fd, validation, validation->map_start_line);
	close(fd);
	validate_textures_and_colors(validation);
}
