/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:44:02 by ohoro             #+#    #+#             */
/*   Updated: 2024/06/26 18:34:09 by ohoro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void color_check(char *line, t_validation *validation)
{
    if (line[0] == 'F')
        validation->floor_color = 1;
    else if (line[0] == 'C')
        validation->ceiling_color = 1;
}

void line_check_textures(char *line, t_validation *validation)
{
    if (line[0] == 'N' && line[1] == 'O')
        validation->north_texture = 1;
    else if (line[0] == 'S' && line[1] == 'O')
        validation->south_texture = 1;
    else if (line[0] == 'W' && line[1] == 'E')
        validation->west_texture = 1;
    else if (line[0] == 'E' && line[1] == 'A')
        validation->east_texture = 1;  
}

void	validate_file(char *file, t_validation *validation)
{
    validation->north_texture = 0;
    validation->south_texture = 0;
    validation->west_texture = 0;
    validation->east_texture = 0;
    validation->floor_color = 0;
    validation->ceiling_color = 0;
    
    int fd = open(file, O_RDONLY);
    char *line = get_next_line(fd);
    while (line)
    {
        line_check_textures(line, validation);
        color_check(line, validation);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    if (validation->north_texture == 0 || validation->south_texture == 0 || validation->west_texture == 0 || validation->east_texture == 0)
    {
        printf(ERR_TEX_ID);
        exit(1);
    }
    if (validation->floor_color == 0 || validation->ceiling_color == 0)
    {
        printf(ERR_COLOR);
        exit(1);
    }
}
