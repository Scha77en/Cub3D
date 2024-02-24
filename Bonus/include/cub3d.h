/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:23:02 by zlaarous          #+#    #+#             */
/*   Updated: 2024/02/04 18:37:39 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <string.h>
# include <math.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../../MLX42/include/MLX42/MLX42.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include "../parcing/get_next_line.h"
//macros

# define FALSE 0
# define TRUE 1

# define WIDTH 1080
# define HEIGHT 810
# define TILE_SIZE 32

# define MOTION_NOTIFY 6
# define DESTROY_NOTIFY 17

# define WINDOW_WIDTH 640
# define WINDOW_HEIGHT 416

# define FOV_ANGLE 60.0
# define SPEED 4
# define SPEEDX2 8
# define ROTATION_SPEED 5.0
# define HIGH_VALUE 9999999999999999999.0
# define GREEN 0x008800
# define BLUE 0x000088
# define RED 0x880000
# define BLACK 0x000000
# define WHITE 0xffffff

//data structs
typedef struct s_player
{
	double	p_x;
	double	p_y;
	double	rotation_angle;
	double	walk_speed;
	double	turn_speed;
	double	new_x;
	double	new_y;
	double	movestep;
	double	width;
	double	height;
	int		dx;
	int		dy;
	int		turndirection;
	int		walkdirection;
	int		sidedirection;
	char	position_player;
}	t_player;

typedef struct s_ray
{
	double			next_horz_touch_x;
	double			next_horz_touch_y;
	double			next_vert_touch_x;
	double			next_vert_touch_y;
	double			x_step;
	double			y_step;
	double			ray_angle;
	double			wall_hit_x;
	double			wall_hit_y;
	double			distance;
	double			wall_hit_hor_x;
	double			wall_hit_hor_y;
	double			wall_hit_ver_x;
	double			wall_hit_ver_y;
	double			distance_hor;
	double			distance_ver;
	double			increment_angle;
	double			tmp_her_x;
	double			tmp_her_y;
	double			tmp_ver_x;
	double			tmp_ver_y;
	double			distance_projection_plane;
	double			real_wall_height;
	double			correct_wall_height;
	bool			found_hit_horizontal;
	bool			found_hit_vertical;
	bool			was_hit_vertical;
	int				is_ray_facing_up;
	int				is_ray_facing_down;
	int				is_ray_facing_left;
	int				is_ray_facing_right;
	int				wall_hit_content;
	mlx_texture_t	*text;
}	t_ray;

typedef struct s_render
{
	int		num_rows;
	int		num_cols;
	int		num_rays;
	int		color;
}	t_render;

typedef struct s_mlx
{
	mlx_t	*mlx;
	void	*win;
	void	*img;
}	t_mlx;

// -------- parcing data structs --------

typedef struct s_data
{
	mlx_texture_t			*north_tex;
	mlx_texture_t			*south_tex;
	mlx_texture_t			*west_tex;
	mlx_texture_t			*east_tex;
	struct s_floor			*floor_data;
	struct s_ceiling		*ceiling_data;
	char					**map;
	int						frame;
	mlx_image_t				*canvas;
	mlx_image_t				*gun_frames[45];
	int32_t					gun_x;
	int32_t					gun_y;
	bool					gun_shoot;
	bool					mouse_clicked;
	int						map_width;
	int						map_height;
	int						fd1;
	int						fd2;
}	t_data;

typedef struct s_floor
{
	int		r_f;
	int		g_f;
	int		b_f;
}	t_floor;

typedef struct s_ceiling
{
	int		r_c;
	int		g_c;
	int		b_c;
}	t_ceiling;

typedef struct s_element
{
	double		topprojection;
	double		bottomprojection;
}	t_element;

typedef struct s_game
{
	t_data		*data;
	t_player	player;
	t_ray		ray;
	t_mlx		*mlx;
	t_render	render;
	t_element	*element;
	bool		gun_state;
}	t_game;

typedef struct s_mem
{
	void			*ptr;
	struct s_mem	*next;
}	t_mem;

// -----------------------------------------------

//functions

//main.c
double		degtorad(double degree);

//init.c
void		data_setup(t_game *game);
void		data_setup1(t_game *game);
void		sprite_setup(t_game *game);

//hooks
void		ft_hook(void *param);
void		ft_mouse(double x, double y, void *param);

//my_mlx_setup.c
void		mlx_fill_rect(t_game *game, int width, int height, int color);
uint32_t	ft_pixel(uint32_t r, uint32_t g, uint32_t b, uint32_t a);
void		create_mlx(t_game *game);
void		mlx_hooks(t_game *game);

//render_player.c
void		renderplayer(t_game *game);
void		moveplayer(t_game *game, float movestep, float deltaTime);
bool		maphaswallat_movement(t_game *game, float x, float y);
bool		maphaswallat_rays(t_game *game, float x, float y);

//render_loop.c
void		loop(void *param);
void		render(t_game *game);
void		disable_images2(t_game *game);

//rays.c
void		castallrays(t_game *game);
void		castray(int stripId, t_game *game, t_ray *ray);
void		intersaction(int stripId, t_game *game, t_ray *ray);
float		normalizeangle(float angle);

//intersaction.c
void		intersactionhor(int stripId, t_game *game, t_ray *ray);
void		increment_xy_hor(t_game *game, t_ray *ray);
void		intersactionver(int stripId, t_game *game, t_ray *ray);
void		increment_xy_ver(t_game *game, t_ray *ray);

//distance.c
float		distance_points(float x1, float y1, float x2, float y2);
void		distance(t_game *game, t_ray *ray);

//render3dProjection.c
void		render3d_projection(t_game *game, int stripId, t_ray *ray, int k);
int			ft_get_color(int i, int x, int y, t_game *game);
void		wall_rendring(t_game *game, int stripId, t_ray *ray);

//minimap_setup.c
void		minimap_setup(t_game *game);
void		rendring_mini_map(t_game *game, int i, int j);
void		ceiling_rendering(t_game *game, int stripId);

// -------------- parcing ---------------

size_t		ft_strlen(char *str);
char		**ft_split(char *s, char c);
int			ft_atoi(char *str);
int			ft_isdigit(int c);
size_t		ft_strlcpy(char *dst, char *src, size_t dstsize);
char		*ft_strdup(char *s1);
void		*ft_memcpy(void *dst, void *src, size_t n);
void		*ft_calloc(size_t count, size_t size);
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
char		*ft_strchr(char *s, int c);
char		*ft_strjoin(char *s1, char *s2);

void		parce_the_file(char	**f_name, t_game **game);
int			all_is_set(t_data *data);
int			check_line(char *line, t_data **data);
void		error_out(char *str, int v, t_data *data);
void		north_check(char *line, t_data **data);
void		south_check(char *line, t_data **data);
void		west_check(char *line, t_data **data);
void		east_check(char *line, t_data **data);
void		floor_color_check(char *line, t_data **data);
void		ceiling_color_check(char *line, t_data **data);
void		map_parcing(int fd, char *line, t_game **game, size_t width);
void		print_map(t_data **data);
int			number_check(char *str, t_data *data);
void		parce_and_save_map_line(char *line, t_game **game,
				int v, size_t length);
int			two_d_size(char *f_name, size_t *length, t_data *data);
char		*clean_tabs(char *line, t_data *data);
void		check_the_map(t_game **game);
int			last_value(char *str);
void		store_position(t_game **game, int i, int j);
void		setting_data_1(t_game **game);
char		**split_and_join(char **f_line, t_data *data);
void		loop_over_the_map(int fd, char **line, t_game **game, int *v);
void		assigne_hight_and_width(t_game **game, int size, size_t length);
void		loop_six_elements(int fd, size_t *length, t_data *data);
int			looping_the_rest(int fd, size_t *length, int x, int i);
void		front_wall_check(t_data *current);
void		in_between_wall_check(t_game **game,
				t_data *current, int i, int *v);
void		more_checks(t_game **game, int i, int j, int *v);
int			check_spaces(char c, int *k, int *j);
void		*my_malloc(int size, int len, int status);
void		clean_mem(t_mem *head);

void		handlemouseclick(enum mouse_key button, enum action act,
				enum modifier_key mod, void	*param);
void		animate_gun(t_game *game);
void		disable_images(t_game *game);
char		**load_frames(void);
void		load_frames1(char *gunframe[45]);
void		rendering_distance(t_game *game, t_ray *ray);

#endif