/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_parser_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:17:02 by alimpens          #+#    #+#             */
/*   Updated: 2024/07/18 16:40:48 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	assign_texture_path(char *line, char *prefix, char **file_path)
{
	if (ft_strncmp(line, prefix, 3) == 0)
		*file_path = ft_strdup(line + 3);
}

int	get_textures(int fd, t_game *game)
{
	char	*line;
	int		read_status;

	read_status = 1;
	while (read_status)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		assign_texture_path(line, "NO ", &(game->file_path_no));
		assign_texture_path(line, "SO ", &(game->file_path_so));
		assign_texture_path(line, "WE ", &(game->file_path_we));
		assign_texture_path(line, "EA ", &(game->file_path_ea));
		free(line);
	}
	if (!game->file_path_no || !game->file_path_so || 
		!game->file_path_we || !game->file_path_ea)
	{
		ft_error(ERR_TEX, NULL);
		return (-1);
	}
	return (0);
}
