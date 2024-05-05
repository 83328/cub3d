/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:11:36 by ohoro             #+#    #+#             */
/*   Updated: 2024/05/05 11:36:33 by ohoro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void normalize_angle(float *angle)
{
    *angle = remainder(*angle, TWO_PI);
    if (*angle < 0)
        *angle = TWO_PI + *angle;
}

float distance_between_points(float x1, float y1, float x2, float y2)
{
    return (sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
