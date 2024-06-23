/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_projection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:27:21 by ohoro             #+#    #+#             */
/*   Updated: 2024/06/21 16:30:34 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t put_pixel_color(mlx_image_t *img, int x, int y)
{
    uint32_t *px;
    px = (uint32_t *)(img->pixels + (img->width * y + x) * sizeof(uint32_t));
    return(*px);
}

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}


// Get the red channel.
int get_r(int rgba)
{
    return ((rgba >> 24) & 0xFF);
}

// Get the green channel.
int get_g(int rgba)
{
    return ((rgba >> 16) & 0xFF);
}

// Get the blue channel.
int get_b(int rgba)
{
    return ((rgba >> 8) & 0xFF);
}

// Get the alpha channel.
int get_a(int rgba)
{
    return (rgba & 0xFF);
}

void convert_rgba_to_abgr(uint32_t *color)
{
    *color = (*color >> 24) | 
         ((*color << 8) & 0x00FF0000) |
         ((*color >> 8) & 0x0000FF00) |
         (*color << 24);
}

void our_mlx_draw_pixel(uint8_t* pixel, uint32_t color)
{
	*(pixel++) = (uint8_t)(color >> 24);
	*(pixel++) = (uint8_t)(color >> 16);
	*(pixel++) = (uint8_t)(color >> 8);
	*(pixel++) = (uint8_t)(color & 0xFF);
}

// old code for that 
//  void our_mlx_draw_pixel(uint8_t* pixel, uint32_t color)
//  {
//       pixel[0] = (uint8_t)(color >> 24); // Alpha
//       pixel[1] = (uint8_t)(color >> 16); // Rot
//       pixel[2] = (uint8_t)(color >> 8);  // Grün
//       pixel[3] = (uint8_t)(color & 0xFF);// Blau
//  }

void our_mlx_put_pixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color)
{
	
	uint8_t* pixelstart = &image->pixels[(y * image->width + x) * sizeof(int32_t)];
	our_mlx_draw_pixel(pixelstart, color);
}

void load_test_texture_north(t_game *game)
{
    game->north_texture = mlx_load_png("textures/32_tri.png");
    game->image_north_texture = mlx_texture_to_image(game->mlx, game->north_texture);
    //printf("north texture loaded into image\n");
}

void load_test_texture_south(t_game *game)
{
    game->south_texture = mlx_load_png("textures/32_bronto.png");
    game->image_south_texture = mlx_texture_to_image(game->mlx, game->south_texture);
    //printf("south texture loaded into image\n");
}

void load_test_texture_west(t_game *game)
{
    game->west_texture = mlx_load_png("textures/32_ptero.png");
    game->image_west_texture = mlx_texture_to_image(game->mlx, game->west_texture);
    //printf("west texture loaded into image\n");
}

void load_test_texture_east(t_game *game)
{
    game->east_texture = mlx_load_png("textures/32_tyr.png");
    game->image_east_texture = mlx_texture_to_image(game->mlx, game->east_texture);
    //printf("east texture loaded into image\n");
}

void	select_texture(t_ray *ray, t_game *game)
{
	float	angle;

	angle = ray->ray_angle;
	normalize_angle(&angle);
	if (ray->was_hit_vertical)
    {
        if (angle >= M_PI / 2 && angle < 3 * M_PI / 2)
        {
            ray->current_texture = game->west_texture;
            ray->current_texture_image = game->image_west_texture;
            //printf("west texture selected\n");
        }
        else
        {
            ray->current_texture = game->east_texture;
            ray->current_texture_image = game->image_east_texture;
            //printf("east texture selected\n");
        }
    }
    else
    {
        if (angle >= 0 && angle < M_PI)
        {
            ray->current_texture = game->south_texture;
            ray->current_texture_image = game->image_south_texture;
            //printf("south texture selected\n");
        }
        else
        {
            ray->current_texture = game->north_texture;
            ray->current_texture_image = game->image_north_texture;
            //printf("north texture selected\n");
        }
    }
}

mlx_image_t *return_texture_image(t_ray *ray)
{
    return (ray->current_texture_image);
}

void reverse_bits(uint32_t *n)
{
    *n = (*n >> 24) | 
         ((*n << 8) & 0x00FF0000) |
         ((*n >> 8) & 0x0000FF00) |
         (*n << 24);
}

void project_test_texture_north(void *param)
{
    t_game *game;
    game = (t_game *)param;
    uint32_t x = 0;
    uint32_t y = 0;
    uint32_t color;
      
    while (y < game->image_north_texture->width)
    {
        while (x < game->image_north_texture->height)
        {
             color = put_pixel_color(game->image_north_texture, x, y);
                reverse_bits(&color);
             mlx_put_pixel(game->image, x, y, color);
             x++;
        }
        x = 0;
        y++;
    }
}

void draw_wall_strip_green(int x, int y, int width, int height, t_game *game)
{
    int i;
    int j;
    i = 0;
    while (i < height)
    {
        j = 0;
        while (j < width)
        {
            mlx_put_pixel(game->image, x + j, y + i, 0x00FF00);
            j++;
        }
        i++;
    }
}


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
    for (int x = 0; x < NUM_RAYS; x++)
    {
        float perpDistance = game->rays[x].distance * cos(game->rays[x].ray_angle - game->player_rotation_angle);
        float projectedWallHeight = (TILE_SIZE / perpDistance) * DIST_PROJ_PLANE;

        int wallStripHeight = (int)projectedWallHeight;

        int wallTopPixel = (WINDOW_HEIGHT / 2) - (wallStripHeight / 2);
        wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;

        int wallBottomPixel = (WINDOW_HEIGHT / 2) + (wallStripHeight / 2);
        wallBottomPixel = wallBottomPixel > WINDOW_HEIGHT ? WINDOW_HEIGHT : wallBottomPixel;
        //this is the actual wall
   //     int color = 0xFFFFFF;
   //     draw_strip(x * WALL_STRIP_WIDTH, wallTopPixel, WALL_STRIP_WIDTH, wallBottomPixel - wallTopPixel, color, game);
   //here ends the actual wall
   
        // set the color of the ceiling
        for (int y = 0; y < wallTopPixel; y++)
        {
           // drawPixel(x, y, 0xFF444444);
           our_mlx_put_pixel(game->image, x, y, 0xFF444444);
        }

        int textureOffsetX;
        if (game->rays[x].was_hit_vertical)
            textureOffsetX = (int)game->rays[x].wall_hit_y % TILE_SIZE;
        else
            textureOffsetX = (int)game->rays[x].wall_hit_x % TILE_SIZE;
        
        select_texture(&game->rays[x], game);

        // get the correct texture id number from the map content
        //int texNum = game->rays[x].wall_hit_content - 1;
       // int texture_width = wallTextures[texNum].width;
        //int texture_width = game->north_texture->width;
        int texture_height = game->north_texture->height;

        // render the wall from wallTopPixel to wallBottomPixel
        for (int y = wallTopPixel; y < wallBottomPixel; y++) {
            int distanceFromTop = y + (wallStripHeight / 2) - (WINDOW_HEIGHT / 2);
            int textureOffsetY = distanceFromTop * ((float)texture_height / wallStripHeight);

            // set the color of the wall based on the color from the texture
        //    color_t texelColor = wallTextures[texNum].texture_buffer[(texture_width * textureOffsetY) + textureOffsetX];
        //    uint32_t texelColor = put_pixel_color(game->image_north_texture, texture_width * textureOffsetY, textureOffsetX);
        game->rays[x].current_texture_image = return_texture_image(&game->rays[x]);
        // uint32_t texelColor = put_pixel_color(game->image_south_texture, textureOffsetX ,textureOffsetY);
          uint32_t texelColor = put_pixel_color(game->rays[x].current_texture_image, textureOffsetX ,textureOffsetY);

            reverse_bits(&texelColor);
        //    uint32_t texelColor = put_pixel_color(game->image_north_texture, textureOffsetX, textureOffsetY);
			our_mlx_put_pixel(game->image, x, y, texelColor);
            // Make the pixel color darker if the ray hit was vertical
        //    if (rays[x].wasHitVertical) {
        //        changeColorIntensity(&texelColor, 0.7);
        //    }

        //    drawPixel(x, y, texelColor);
        }

      //   set the color of the floor to a light grey
        for (int y = wallBottomPixel; y < WINDOW_HEIGHT; y++)
        {
        //    drawPixel(x, y, 0xFF888888);
        // the color should be light grey
            our_mlx_put_pixel(game->image, x, y, 0xFF884288);
        }
        // printf texnum
     //printf("texnum: %d\n", texNum);
    }

}
