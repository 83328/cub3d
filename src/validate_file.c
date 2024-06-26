/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:44:02 by ohoro             #+#    #+#             */
/*   Updated: 2024/06/26 19:10:26 by ohoro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void check_rgba_format(char *line)
{
    // there should be 2 commas in the line
    // it starts with a
    (void)line;
    char rgb[3] = "123";
    int temp = 0;
    temp = atoi(rgb);
    printf("temp: %d\n", temp);
}

void color_check(char *line, t_validation *validation)
{
    if (line[0] == 'F')
    {
        validation->floor_color = 1;
        check_rgba_format(line);
    }    
    else if (line[0] == 'C')
    {
        validation->ceiling_color = 1;
        check_rgba_format(line);
    }
}

void line_check_textures(char *line, t_validation *validation)
{
    int i = 0;
    while(line[i] != '\n' && line[i] != '\0')
    {  
        if (line[i] == ' ')
            i++;
        if (line[i] == 'N' && line[i+1] == 'O')
           validation->north_texture = 1;
        else if (line[i] == 'S' && line[i+1] == 'O')
            validation->south_texture = 1;
        else if (line[i] == 'W' && line[i+1] == 'E')
            validation->west_texture = 1;
        else if (line[i] == 'E' && line[i+1] == 'A')
            validation->east_texture = 1;
        i++;  
    } 
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
