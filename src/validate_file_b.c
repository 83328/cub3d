/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file_b.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:51:53 by ohoro             #+#    #+#             */
/*   Updated: 2024/07/18 16:20:41 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_color_value(char *line, int *i)
{
	int	value;

	value = ft_atoi(&line[*i]);
	while (ft_isdigit(line[*i]))
	{
		(*i)++;
	}
	if (line[*i] != ',' && line[*i] != ' ' && line[*i] != '\t' && line[*i] != '\n' && line[*i] != '\0')
	{
		ft_error(ERR_COLOR_VAL, NULL);
	}
	return (value);
}

void	parse_color_line_f(char *line, int *i, t_validation *v)
{
	ft_skip_spaces(line, i);
	v->f_red = parse_color_value(line, i);
	if (line[*i] == ',')(*i)++;
		v->f_green = parse_color_value(line, i);
	if (line[*i] == ',')(*i)++;
		v->f_blue = parse_color_value(line, i);
	ft_skip_spaces(line, i);
	if (line[*i] != '\n')
	{
		ft_error(ERR_COLOR_NUM, NULL);
	}
}

void	parse_color_line_c(char *line, int *i, t_validation *v)
{
	ft_skip_spaces(line, i);
		v->c_red = parse_color_value(line, i);
	if (line[*i] == ',')(*i)++;
		v->c_green = parse_color_value(line, i);
	if (line[*i] == ',')(*i)++;
		v->c_blue = parse_color_value(line, i);
	ft_skip_spaces(line, i);
	if (line[*i] != '\n')
	{
		ft_error(ERR_COLOR_NUM, NULL);
	}
}

void	color_check(char *line, t_validation *v)
{
	int	i;

	i = 0;
	ft_skip_spaces(line, &i);

	if (line[i] == 'F')
	{
		i++;
		parse_color_line_f(line, &i, v);
	}
	else if (line[i] == 'C')
	{
		i++;
		parse_color_line_c(line, &i, v);
	}
	if (v->f_red < 0 || v->f_red > 255 || v->f_green < 0 || v->f_green > 255 || v->f_blue < 0 || v->f_blue > 255)
	{
		ft_error(ERR_COLOR_VAL, NULL);
	}
	if (v->c_red < 0 || v->c_red > 255 || v->c_green < 0 || v->c_green > 255 || v->c_blue < 0 || v->c_blue > 255)
	{
		ft_error(ERR_COLOR_VAL, NULL);
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
			validation->floor_color_num = 1;
		}
		else if (line[i] == 'C')
		{
			validation->ceiling_color_num = 1;
		}
		i++;
	}
}
