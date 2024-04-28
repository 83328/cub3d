/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:11:36 by ohoro             #+#    #+#             */
/*   Updated: 2024/04/28 18:11:59 by ohoro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void normalize_angle(float *angle)
{
    *angle = remainder(*angle, TWO_PI);
    if (*angle < 0)
        *angle = TWO_PI + *angle;
}