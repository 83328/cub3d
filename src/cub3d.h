/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimpens <alimpens@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:56:41 by ohoro             #+#    #+#             */
/*   Updated: 2024/07/17 11:51:05 by alimpens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>
#include <fcntl.h>
#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "../lib/get_next_line/get_next_line.h"
#include "../lib/libft/libft.h"

#define WIDTH 1024
#define HEIGHT 768
#define WINDOW_HEIGHT HEIGHT
#define NUM_RAYS WIDTH
#define WALL_STRIP_WIDTH 1
#define TILE_SIZE 16
#define MAP_NUM_ROWS 10
#define MAP_NUM_COLS 14
#define M_PI 3.14159265358979323846
#define PI 3.14159265358979323846
#define M_PI_2 1.57079632679489661923
#define THREE_PI_2 4.71238898038468985769
#define TWO_PI 6.28318530717958647692
#define FOV_ANGLE (60 * (PI / 180))
#define DIST_PROJ_PLANE ((WIDTH / 2) / tan(FOV_ANGLE / 2))

# define ERR_ARGS "Not enough arguments. \nUsage: ./cub3d ./maps/mapfile.cub\n"
# define ERR_FILETYPE "Invalid file extension: use .cub for map files\n"
# define ERR_OPEN "Failed to open the file\n"
# define ERR_READ_LINE "Failed to read line\n"
# define ERR_MEM "Failed to allocate memory for the map\n"
# define ERR_IMG "Failed to create image\n"
# define ERR_COLOR "Error in color. Provide a color in the format F or C 255,255,255\n"
# define ERR_TEX "Error in texture path. Provide a path to the NO, SO, WE and EA images\n"
# define ERR_TEX_ID "Error in texture. Provide  NO, SO, WE and EA\n"
# define ERR_INVALID_MAP_CHAR "Invalid character in map\n"
# define ERR_MAP_NOT_CLOSED "Invalid file format: Map is not surrounded by walls\n"
# define ERR_START_POINT "Map should contain exactly one 'N', 'W', 'E', or 'S'.\n"
# define ERR_FILE "File not found\n"
# define ERR_READ "Could not read from the file\n"
# define ERR_FLOOR_COLOR "Floor color is not a valid RGB value\n"
# define ERR_CEILING_COLOR "Ceiling color is not a valid RGB value\n"
# define ERR_MAP_SIZE "The map is too large\n"

typedef struct s_validation
{
	int		north_texture;
	int		south_texture;
	int		west_texture;
	int		east_texture;
	int		floor_color;
	int		ceiling_color;
	int		map;
}	t_validation;

typedef struct s_map
{
	int width;
	int height;
	//int start;
	char **map;
} t_map;

typedef struct s_max_length
{
	int line_count;
	int map_start;
	int map_rows;
	int current_length;
	int max_length;
}	t_max_length;

typedef struct s_dda
{
	float xintercept;
	float yintercept;
	float xstep;
	float ystep;
	int is_ray_facing_down;
	int is_ray_facing_up;
	int is_ray_facing_right;
	int is_ray_facing_left;
	bool found_horz_wall_hit;
	float horz_wall_hit_x;
	float horz_wall_hit_y;
	int horz_wall_content;
	float next_horz_touch_x;
	float next_horz_touch_y;
	bool found_vert_wall_hit;
	float vert_wall_hit_x;
	float vert_wall_hit_y;
	int vert_wall_content;
	float next_vert_touch_x;
	float next_vert_touch_y;
	
} t_dda;

typedef struct	s_distances
{
	float	horz_hit_distance;
	float	vert_hit_distance;
}				t_distances;

typedef struct s_wall_projection {
	int wall_top_pixel;
	int wall_bottom_pixel;
	int wall_strip_height;
} t_wall_projection;

typedef struct s_wall_draw {
	int y;
	int texture_offset_x;
	int texture_height;
	int distance_from_top;
	int texture_offset_y;
	uint32_t texel_color;
} t_wall_draw;

typedef struct ray
{
	float	ray_angle;
	float	wall_hit_x;
	float	wall_hit_y;
	float	distance;
	bool	was_hit_vertical;
	bool	is_ray_facing_up;
	bool	is_ray_facing_down;
	bool	is_ray_facing_left;
	bool	is_ray_facing_right;
	bool	wall_hit_content;
	mlx_texture_t	*current_texture;
	mlx_image_t		*current_texture_image;
}	t_ray;

typedef struct s_game
{
	char						char_read;//not used yet
	char						map_char;//not used yet
	char						start_direction;
	int							total_chars_read;//not used yet
	mlx_t						*mlx;
	mlx_image_t					*image;
	mlx_texture_t				*north_texture;
	mlx_image_t					*image_north_texture;
	mlx_texture_t				*south_texture;
	mlx_image_t					*image_south_texture;
	mlx_texture_t				*west_texture;
	mlx_image_t					*image_west_texture;
	mlx_texture_t				*east_texture;
	mlx_image_t					*image_east_texture;
	float						player_x;
	float						player_y;
	float						player_width;
	float						player_height;
	float						player_rotation_angle;
//	char						*floor_color_str;
	t_map						*map;
//	int							map_grid[MAP_NUM_ROWS][MAP_NUM_COLS];
	int							**map_grid_2d;
	int							map_start;
	int							map_rows;
	int							map_cols;
	int							map_end;
	char						*file_path_no;
	char						*file_path_so;
	char						*file_path_we;
	char						*file_path_ea;
	t_ray						rays[NUM_RAYS];
}	t_game;

typedef struct line
{
	int32_t	x0;
	int32_t	y0;
	int32_t	x1;
	int32_t	y1;
}	t_line;

void color_check(char *line, t_validation *validation);
void line_check_textures(char *line, t_validation *validation);
void validate_file(char *file, t_validation *validation);

//2_file_check.c
void	check_file(int argc, char **argv);

// 3_load_map.c
void	load_map_dimensions_from_file(t_game *game, char *argv);
void	allocate_map(t_game *game);


// 4_parser.c
int		load_map(t_game *game, char *filename);
int		get_map_start(int fd);
int		get_textures(int fd, t_game *game);
//int		get_map_height(int fd);
int		get_map_height(int fd, int map_start);
//int		get_max_line_length(int fd);
//int		get_max_line_length(int fd, int map_start);
int		get_max_line_length(int fd, int map_start, int map_rows);

// 5_map_check.c
void	check_map_surrounded(t_game *game);
void	print_map_grid_2d(t_game *game);

//6_fill_map.c
void	fill_2d_map_from_file(t_game *game, char argv[1]);

//color_1.c
uint32_t	put_pixel_color(mlx_image_t *img, int x, int y);
void		our_mlx_put_pixel(mlx_image_t *image, uint32_t x, 
	uint32_t y, uint32_t color);
void	reverse_bits(uint32_t *color);

//color_2.c
int		get_rgba(int r, int g, int b, int a);

// key_commands.c
void	handle_movement_and_rotation_keys(mlx_key_data_t keydata, t_game *game);
void	update_player_position(t_game *game, float dx, float dy);
void	update_movement(t_game *game, float move_speed, mlx_key_data_t keydata);
void	handle_escape_key(mlx_key_data_t keydata, t_game *game);
void	my_keyhook(mlx_key_data_t keydata, void	*param);
// key_commands_helper.c
void	update_rotation(t_game *game, mlx_key_data_t keydata);
void	move_forward(t_game *game, float move_speed);
void	move_backward(t_game *game, float move_speed);
void	move_left(t_game *game, float move_speed);
void	move_right(t_game *game, float move_speed);

// graphics_helper.c
int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void	put_pixel(int32_t x, int32_t y, mlx_image_t *image);
void	erase_pixel(int32_t x, int32_t y, mlx_image_t *image);
int32_t	get_step(int32_t start, int32_t end);
void	bresenham(t_line line, mlx_image_t *image);

// player_movements.c
void	draw_new_player(t_game *game);
void	redraw_player(void *param);
// player_rays.c
void	draw_player_middle_ray(t_game *game);
void	cast_all_rays(void *param);



// math_helper.c
void	normalize_angle(float *angle);
float	distance_between_points(float x1, float y1, float x2, float y2);

// map_helper.c
bool	has_wall_at(t_game game, float  x, float y);
bool	is_inside_map(t_game game, float x, float y);
int		get_map_at(t_game game, int i, int j);

// draw_map.c
void	draw_map(void *param);
void	draw_minimap(void *param);

//draw_minimap.c
void	draw_rectangle(t_game *game, int x, int y);

// draw.c
void	clear_image(void *param);
void	draw_all_and_clear(void *param);

// DDA_1_rays.c
void	dda_init(t_dda *dda, t_game *game, int i);

// DDA_2_horizontal.c
void	dda_init_for_horizontal(t_dda *dda, t_game *game, int i);
void	dda_loop_horizontal(t_game *game, t_dda *dda);

//DDA_3_vertical.c
void	dda_init_for_vertical(t_dda *dda, t_game *game, int i);
void	dda_loop_vertical(t_game *game, t_dda *dda);

//DDA_4_helper.c
void	horizontal_and_vertical_grid_intersection(t_game *game, int i);

// wall_projection.c
void	draw_strip(int x, int y, int width, int height, int color, t_game *game);
void	wall_projection(t_game *game);

// wall_1_tex.c
void	load_test_texture_north(t_game *game);
void	load_test_texture_east(t_game *game);
void	load_test_texture_south(t_game *game);
void	load_test_texture_west(t_game *game);
void	project_test_texture_north(void *param);

// wall_2_tex.c
void		select_texture(t_ray *ray, t_game *game);
mlx_image_t	*return_texture_image(t_ray *ray);

//utils.c
void	ft_error(char *str, t_game *game);
int32_t	get_error(int32_t dx, int32_t dy);
void	free_game(t_game *game);
void	free_map_grid_2d(t_game *game);