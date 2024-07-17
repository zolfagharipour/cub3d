/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubid.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarggra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:02:25 by fmarggra          #+#    #+#             */
/*   Updated: 2024/07/17 17:02:27 by fmarggra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBID_H
# define CUBID_H

# include <stdlib.h>
# include <unistd.h>
# include <mlx.h>
# include <stdio.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <fcntl.h>
# include <sys/time.h>
# include "../libft/libft.h"

# define HEIGHT 1000
# define WIDTH 1000
# define TRUE 1
# define FALSE 0
//definition square size can be amended
# define SQUARE 10
# define MOVING_DIS 0.2
# define ORANGE 0xec956c
# define RED 0xFF0000
# define LBLUE 0xADD8E6
# define DBLUE 0x547eae
# define DDBLUE 0x0
# define D  1
# define N  2
# define S  3
# define E  4
# define W  5
# define SMOKE 6
# define SP 7
# define BL 17
# define FLOOR 0
# define CEILING 1
# define DW 6
# define SP 7
# define NO_PLAYER 0
# define MULTIPLE_PLAYERS 1
# define INV_CHAR 2
# define INV_BORDERS 3
# define INV_NL 5
# define NOT_FOUND 6
# define FOUND 1
# define INV_OPEN_COL 2
# define INV_FORMAT 3
# define RESIDUUM 6
# define SMALL_ANGLE 1e-2
# ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

typedef struct s_mlx
{
	void		*ptr;
	void		*win;
	void		*loop;
	void		*img;
	void		*texture;
	void		*addr;
	void		*tex_addr;
	char		*tex_data;
	int			bpp;
	int			line_length;
	int			endian;
	int			y;
	int			x;
	int			shift_x;
	int			shift_y;
	int			tex_dim[2];
	//int		player_running;
}	t_mlx;

typedef struct s_map
{
	int		**raw_map;
	int		raw_length;
	int		raw_height;
	int		file_length;
	int		scale;
	int		**minimap;
	char	*file;
	int		player_x;
	int		player_y;
	int		player_size;
	int		s_square;	
	int		player_found;
	int		previous_line_valid;
	int		map_started;
	int		val_aspects[6];
	int		val_map[6];
	char	*textures[4];
	int		color[2];
	int		fd;
	int		close_door[2];
}	t_map;

typedef struct s_raycaster
{
	double		pos[2];
	double		move[2];
	double		look;
	double		dir;
	double		steps[2];
	int			ray[2];
	double		hit[WIDTH][6];
	double		tmp[2];
	double		sprite[4];
	int			frame;
	int			ninja_found;
	int			shuriken;
	int			smoke;
}	t_rc;

typedef struct s_common
{
	t_mlx		*mlx;
	t_map		*map;
	t_rc		*rc;
}	t_common;

//setup
int		main(int argc, char **argv);

int		init_structs(t_common *d_list, char *file);
void	init_mlx(t_mlx *mlx);
void	init_map(t_map *map, char *file);
void	init_rc(t_rc *rc);
int		init_mlx_functions(t_common *d_list, t_mlx *mlx);
void	put_red_square(t_common *d_list);
void	put_image(t_common *d_list, t_mlx *mlx);
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
int		error_arguments(int argc, char **argv);

//file processing
void	evaluate_line(char *line, t_common *d_list);
void	gnl_loop(t_common *d_list, char *line);
int		determine_map_size_and_val(t_common *d_list);
void	validate_map_line(char *line, t_common *d_list);
int		line_empty(char *line);
int		find_texture(char *line, t_common *d_list, int identifyer, int start);
void	find_color(char *line, t_common *d_list, int identifier, int start);
int		suitable_color_range(int *store_location, char *r, char *g, char *b);
int		fill_raw_map(t_common *d_list);
void	determine_content_of_coordinates(t_common *d_list, char *line, int x, int y);
void	flush_initial_values(t_common *d_list, int y);
void	check_map_scale_factor(t_common *d_list);
int		line_empty(char *line);
int		is_texture(int i, char *line, char id, char id2);

//map parsing
char	*valid_map_boundaries(t_common *d_list);
int		minimap_vertical_boundaries(t_common *d_list);
int		minimap_horizontal_boundaries(t_common *d_list);
int		minimap_door_check(t_common *d_list);
int		minimap_zero_check(t_common *d_list);

//read_from_file
int		determine_map_size_and_val(t_common *d_list);
int		read_map_from_file(t_common *d_list);
int		fill_raw_map(t_common *d_list);
void	find_the_players_position(t_common *d_list);
int		extract_color(char **color, char *line, int *s, int i);
int		cut_lines(t_common *d_list, char *line, int s, int identifier);
int		all_ids_found(t_common *d_list);

//error checking
void	check_all_parts_found_and_valid(t_common *d_list);
void	catch_invalid_map(int *amt_errors, t_common *d_list, int i);
void	print_color_texture_error(t_common *d_list, int i);
int		has_been_printed_before(t_common *d_list, int err_macro, int i);
void	print_map_error(t_common *d_list, int error);

//testing
int		test_map(t_common *d_list);
int		malloc_raw_map(t_common *d_list);
void	print_map(t_map *map);
void	find_the_players_position(t_common *d_list);

//image
void	draw_image(t_common *d_list);
void	draw_minimap(t_common *d_list);
void	draw_player(t_common *d_list);
int		cleanup(t_common *d_list);
void	cleanup_mlx(t_mlx *mlx);
void	cleanup_map(t_map *map);
void	cleanup_d_list(t_common *d_list);
void	cleanup_rc(t_rc *rc);
void	p_error(char *str, t_common *d_list);

//events
void	events(t_common *d_list);
int		key_press(int keycode, t_common *d_list);
void	move_window(int keycode, t_common *d_list);
void	rotate_player(int keycode, t_common *d_list);
int		key_release(int keycode, t_common *d_list);
int		mouse_track(int x, int y, t_common *d_list);


//mohamad
int		minimap(t_common *d_list);
void	caster(t_common *d_list);
void	line(t_common *d_list, double p1[2], double p2[2], int color);
double	calc_dir(double dir);
void	draw_walls(t_common *d_list);
void	move_player(t_common *d_list, double move_dir);
int		my_mlx_pixel_get(t_mlx *mlx, int x, int y);
void	south(t_common *d_list);
void	wall(t_common *d_list, double p1[2], double p2[2], int x);
void	load_textures(t_mlx *mlx);
void	find_sprite(t_common *d_list);
void	sprite(t_common *d_list);
void	floor_ceiling(t_common *d_list);
void	ninja(t_common *d_list);
void	door (t_common *d_list);
int		light_adjust(int rgb, double light);
int		wall_lighting(t_common *d_list, int color, int x);
void	shuriken(t_common *d_list);
void	draw_icon(t_common *d_list);

// caster
void    caster(t_common *d_list);
void	step_x(t_rc *rc, int i);
void	step_y(t_rc *rc, int i);
double	length_x(t_rc *rc);
double	length_y(t_rc *rc);
double	pyth(double b, double c);
void	shoot_ray(t_common *d_list, t_rc *rc, int pixel);

// math
double	dot_product(double p1[2], double p2[2]);
double	cross_product(double p1[2], double p2[2]);
double	magnitudes(double p[2]);

#endif
