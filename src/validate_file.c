/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:44:02 by ohoro             #+#    #+#             */
/*   Updated: 2024/07/18 11:13:11 by ohoro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int line_contains_only_one_f(char *line)
{
	int i = 0;
	int count = 0;
	while (line[i] != '\n' && line[i] != '\0')
	{
		if (line[i] == 'F')
			count++;
		i++;
	}
	if (count == 1)
	{	printf("count: %d\n only one F", count);
		return (1);
	}
	return (0);
}

int line_contains_only_one_c(char *line)
{
	int i = 0;
	int count = 0;
	while (line[i] != '\n' && line[i] != '\0')
	{
		if (line[i] == 'C')
			count++;
		i++;
	}
	if (count == 1)
		return (1);
	return (0);
}





int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int is_double_digit(char *line, int i)
{
	if (is_digit(line[i]) && is_digit(line[i + 1]))
		return (1);
	return (0);
}

int is_triple_digit(char *line, int i)
{
	if (is_digit(line[i]) && is_digit(line[i + 1]) && is_digit(line[i + 2]))
		return (1);
	return (0);
}

int is_quadruple_digit(char *line, int i)
{
	if (is_digit(line[i]) && is_digit(line[i + 1]) && is_digit(line[i + 2]) && is_digit(line[i + 3]))
		return (1);
	return (0);
}


int is_only_valid_color_tokens(char *line, int i)
{
	if (line [i] == 'C' || line[i] == 'F' || line[i] == ',' || is_digit(line[i]))
		return (1);
	return (0);
}
void assign_rgb(char *line, int i, char *rgb) {
    size_t length = ft_strlen(line + i); // Länge der verbleibenden Zeichenkette ab Index `i`

    if (length >= 3 && is_triple_digit(line, i)) {
        rgb[0] = line[i];
        rgb[1] = line[i + 1];
        rgb[2] = line[i + 2];
    } else if (length >= 2 && is_double_digit(line, i)) {
        rgb[0] = '0';
        rgb[1] = line[i];
        rgb[2] = line[i + 1];
    } else if (length >= 1 && is_digit(line[i])){
        rgb[0] = '0';
        rgb[1] = '0';
        rgb[2] = line[i];
    }
}
void	check_rgba_format(char *line)
{
	char	rgb[3] = "000";
	int		temp = 0;
	int		i = 0;
	while(line[i] == 'F' || line[i] == 'C' || line[i] == ' ')
		i++;
	while(line[i] == ' ')
		i++;
	if (is_quadruple_digit(line, i))
	{
		ft_error(ERR_COLOR_FORMAT, NULL);
	}
	/* else if (is_triple_digit(line, i))
	{
		rgb[0] = line[i];
		rgb[1] = line[i + 1];
		rgb[2] = line[i + 2];
	}
	else if (is_double_digit(line, i))
	{
		rgb[0] = '0';
		rgb[1] = line[i];
		rgb[2] = line[i + 1];
	}
	else
	{
		rgb[0] = '0';
		rgb[1] = '0';
		rgb[2] = line[i];
	} */
	else
		assign_rgb(line, i, rgb);
	temp = atoi(rgb);
	printf("temp: %d\n", temp);
}


void	color_check(char *line, t_validation *validation)
{
	(void)validation;
	int i = 0;
	while (line[i] != '\n' && line[i] != '\0')
	{
		int x = is_only_valid_color_tokens(line, i);
		printf("x: %d\n", x);
		i++;	
	}
}

void	line_check_textures(char *line, t_validation *validation)
{
	int	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
	{
		if (line[i] == ' ' || line[i] == '\t')
			i++;
		if ((line[i] == 'N' && line[i +1] == 'O'))
			validation->north_texture += 1;
		else if (line[i] == 'S' && line[i +1] == 'O')
			validation->south_texture += 1;
		else if (line[i] == 'W' && line[i +1] == 'E')
			validation->west_texture += 1;
		else if (line[i] == 'E' && line[i +1] == 'A')
			validation->east_texture += 1;
		else if (line[i] == 'F')
		{
			//color_check(line, validation);
			validation->floor_color = 1;
		}
		else if (line[i] == 'C')
		{
			validation->ceiling_color = 1;
		}
		i++;
	}
}

void	validate_file(t_game *game, char *file, t_validation *validation)
{
	validation->map_start_line = game->map_start;
	validation->north_texture = 0;
	validation->south_texture = 0;
	validation->west_texture = 0;
	validation->east_texture = 0;
	validation->floor_color = 0;
	validation->ceiling_color = 0;
	
	int		fd;
	char	*line = NULL;
	int i = validation->map_start_line;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line && i)
	{
		line_check_textures(line, validation);
	//	color_check(line, validation);
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
	 if (validation->floor_color == 0 || validation->ceiling_color == 0)
		ft_error(ERR_COLOR, NULL); 

	printf("huhu from the VALIDATE FILE\n");
}
