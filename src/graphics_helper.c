/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:59:32 by ohoro             #+#    #+#             */
/*   Updated: 2024/04/18 16:00:02 by ohoro            ###   ########.fr       */
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