/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:44:02 by ohoro             #+#    #+#             */
/*   Updated: 2024/07/18 15:27:40 by ohoro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_file(t_game *game, char *file, t_validation *validation)
{
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
	
	int		fd;
	char	*line = NULL;
	int i = validation->map_start_line;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line && i)
	{
		line_check_textures(line, validation);
		color_check(line, validation);
		free(line);
		line = get_next_line(fd);
		i--;
	}
	close(fd);
	if (validation->north_texture != 1 || validation->south_texture != 1 
		|| validation->west_texture != 1 || validation->east_texture != 1)
		{
			printf("YES XXX ITS AN ERROR\n");
		ft_error(ERR_TEX, NULL);
		}
	 if (validation->floor_color_num != 1 || validation->ceiling_color_num != 1)
		ft_error(ERR_COLOR, NULL); 

	printf("huhu from the VALIDATE FILE\n");
	// printf red green blue
	printf("f_red: %d\n", validation->f_red);
	printf("f_green: %d\n", validation->f_green);
	printf("f_blue: %d\n", validation->f_blue);
}
