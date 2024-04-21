/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:59:32 by ohoro             #+#    #+#             */
/*   Updated: 2024/04/20 19:18:46 by ohoro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	put_pixel(int32_t x, int32_t y, mlx_image_t *image)
{
	uint32_t	color;

	color = ft_pixel(255, 255, 255, 255);
	mlx_put_pixel(image, x, y, color);
}

// erase pixel
void	erase_pixel(int32_t x, int32_t y, mlx_image_t *image)
{
	uint32_t	color;

	color = ft_pixel(0, 0, 0, 0);
	mlx_put_pixel(image, x, y, color);
}

int32_t	get_step(int32_t start, int32_t end)
{
	if (start < end)
		return (1);
	else
		return (-1);
}

int32_t	get_error(int32_t dx, int32_t dy)
{
	if (dx > dy)
		return (dx / 2);
	else
		return (-dy / 2);
}

void	bresenham(t_line line, mlx_image_t *image)
{
	int32_t		dx;
	int32_t		dy;
	int32_t		err;
	int32_t		e2;

	dx = abs(line.x1 - line.x0);
	dy = abs(line.y1 - line.y0);
	err = get_error(dx, dy);
	while (true) 
	{
		put_pixel(line.x0, line.y0, image);
		if (line.x0 == line.x1 && line.y0 == line.y1)
			break ;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			line.x0 += get_step(line.x0, line.x1);
		}
		if (e2 < dy)
		{
			err += dx;
			line.y0 += get_step(line.y0, line.y1);
		}
	}
}
