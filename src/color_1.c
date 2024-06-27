/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:40:58 by alimpens          #+#    #+#             */
/*   Updated: 2024/06/27 12:09:54 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	put_pixel_color(mlx_image_t *img, int x, int y)
{
	uint32_t	*px;

	px = (uint32_t *)(img->pixels + (img->width * y + x) * sizeof(uint32_t));
	return (*px);
}

void	convert_rgba_to_abgr(uint32_t *color)
{
	*color = (*color >> 24)
		| ((*color << 8) & 0x00FF0000)
		| ((*color >> 8) & 0x0000FF00)
		| (*color << 24);
}

void	our_mlx_draw_pixel(uint8_t *pixel, uint32_t color)
{
	*(pixel++) = (uint8_t)(color >> 24);
	*(pixel++) = (uint8_t)(color >> 16);
	*(pixel++) = (uint8_t)(color >> 8);
	*(pixel++) = (uint8_t)(color & 0xFF);
}

void	our_mlx_put_pixel(mlx_image_t *image, uint32_t x, 
	uint32_t y, uint32_t color)
{
	uint8_t	*pixelstart;

	pixelstart = &image->pixels[(y * image->width + x) * sizeof(int32_t)];
	our_mlx_draw_pixel(pixelstart, color);
}

void	reverse_bits(uint32_t *color)
{
	*color = (*color >> 24)
		| ((*color << 8) & 0x00FF0000)
		| ((*color >> 8) & 0x0000FF00)
		| (*color << 24);
}
