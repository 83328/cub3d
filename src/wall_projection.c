/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_projection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:27:21 by ohoro             #+#    #+#             */
/*   Updated: 2024/05/06 18:28:18 by ohoro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_strip(int x, int y, int width, int height, int color, t_game *game)
{
    int i;
    int j;

    i = 0;
    while (i < height)
    {
        j = 0;
        while (j < width)
        {
            mlx_put_pixel(game->image, x + j, y + i, color);
            j++;
        }
        i++;
    }
}

void wall_projection(t_game *game)
{    
    for (int x = 0; x < NUM_RAYS; x++) {
        float perpDistance = game->rays[x].distance * cos(game->rays[x].ray_angle - game->player_rotation_angle);
        float projectedWallHeight = (TILE_SIZE / perpDistance) * DIST_PROJ_PLANE;

        int wallStripHeight = (int)projectedWallHeight;

        int wallTopPixel = (WINDOW_HEIGHT / 2) - (wallStripHeight / 2);
        wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;

        int wallBottomPixel = (WINDOW_HEIGHT / 2) + (wallStripHeight / 2);
        wallBottomPixel = wallBottomPixel > WINDOW_HEIGHT ? WINDOW_HEIGHT : wallBottomPixel;
        int color = 0xFFFFFF;
        draw_strip(x * WALL_STRIP_WIDTH, wallTopPixel, WALL_STRIP_WIDTH, wallBottomPixel - wallTopPixel, color, game);

        // set the color of the ceiling
        for (int y = 0; y < wallTopPixel; y++) {
           // drawPixel(x, y, 0xFF444444);
           mlx_put_pixel(game->image, x, y, 0xFF444444);
        }

       // int textureOffsetX;
       // if (game->rays[x].was_hit_vertical)
       //     textureOffsetX = (int)game->rays[x].wall_hit_y % TILE_SIZE;
       // else
       //     textureOffsetX = (int)game->rays[x].wall_hit_content % TILE_SIZE;

        // get the correct texture id number from the map content
    //    int texNum = game->rays[x].wall_hit_content - 1;

       // int texture_width = wallTextures[texNum].width;
       // int texture_height = wallTextures[texNum].height;

        // render the wall from wallTopPixel to wallBottomPixel
        //for (int y = wallTopPixel; y < wallBottomPixel; y++) {
        //    int distanceFromTop = y + (wallStripHeight / 2) - (WINDOW_HEIGHT / 2);
        //    int textureOffsetY = distanceFromTop * ((float)texture_height / wallStripHeight);

            // set the color of the wall based on the color from the texture
        //    color_t texelColor = wallTextures[texNum].texture_buffer[(texture_width * textureOffsetY) + textureOffsetX];

            // Make the pixel color darker if the ray hit was vertical
        //    if (rays[x].wasHitVertical) {
        //        changeColorIntensity(&texelColor, 0.7);
        //    }

        //    drawPixel(x, y, texelColor);
       // }

      //   set the color of the floor to a light grey
        for (int y = wallBottomPixel; y < WINDOW_HEIGHT; y++) {
        //    drawPixel(x, y, 0xFF888888);
        // the color should be light grey
            mlx_put_pixel(game->image, x, y, 0xFF884288);
        }
    }
}
