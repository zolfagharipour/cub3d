#ifndef CUBID_H
# define CUBID_H

# include <stdlib.h>
# include <unistd.h>
# include <mlx.h>
# include <stdio.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include "../libft/libft.h"
# include <fcntl.h>

# define HEIGHT 800
# define WIDTH 800
# define TRUE 1
# define FALSE 0
//definition square size can be amended
# define SQUARE 10
# define MOVING_DIS 0.1
# define ORANGE 0xec956c
# define RED 0xFF0000
# define LBLUE 0xADD8E6
# define DBLUE 0x547eae
# define NN 16761035
# define SO 11393254
# define EE 9498256
# define WW 16776960
# define DDBLUE 0x0
# define N 2
# define S 3
# define E 4
# define W 5
# define RESIDUUM 6
# define SMALL_ANGLE 1e-2
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct s_mlx
{
	void		*ptr;
	void		*win;
	void		*loop;
	void		*img;
	void		*addr;
	int			bpp;
	int			line_length;
	int			endian;
	int			y;
	int			x;
	int			shift_x;
	int			shift_y;
	//int		player_running;
}	t_mlx;

typedef struct s_texture
{
	void	*img;
	char	*path[4];
	void	*mlx;
	int		*texture_buffer[4];
}	t_texture;

typedef struct s_map
{
	int		**raw_map;
	int		raw_length;
	int		raw_height;
	int		scale;
	int		**minimap;
	char	*file;
	int		player_x;
	int		player_y;
	int		player_size;
	int		s_square;	
	int		player_found;
	int		previous_line_valid;
	int		fd;
}	t_map;

typedef struct	s_raycaster
{
	double		pos[2];
	double		move[2];
	double		look;
	double		dir;
	double		steps[2];
	int			ray[2];
	double		hit[WIDTH][4];
	double		tmp[2];
} t_rc;

typedef struct s_common
{
	t_mlx		*mlx;
	t_map 		*map;
	t_rc		*rc;
	t_texture	*texture;
} t_common;

//setup
int main(int argc, char **argv);

int		init_structs(t_common *d_list, char *file);
void	init_mlx(t_mlx *mlx);
void	init_map(t_map *map, char *file);
void	init_rc(t_rc *rc);
int		init_mlx_functions(t_common *d_list);
void    put_red_square(t_common *d_list);
void	put_image(t_common *d_list, t_mlx *mlx);
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
int		error_arguments(int argc, char **argv);

//read_from_file
int determine_map_size(t_common *d_list);
int read_map_from_file(t_common *d_list);
int fill_raw_map(t_common *d_list);
void find_the_players_position(t_common *d_list);

//testing
int test_map(t_common *d_list);
int malloc_raw_map(t_common *d_list);
void print_map(t_map *map);
void find_the_players_position(t_common *d_list);

//image
void	draw_image(t_common *d_list);
void    draw_minimap(t_common *d_list);
void    draw_player(t_common *d_list);

//cleanup
int		cleanup(t_common *d_list);
void    cleanup_mlx(t_mlx *mlx);
void    cleanup_map(t_map *map);;
void    cleanup_d_list(t_common *d_list);
void    cleanup_rc(t_rc *rc);
void    p_error(char *str, t_common *d_list);


//events
void	events(t_common *d_list);
int		key_press(int keycode, t_common *d_list);
void	move_window(int keycode, t_common *d_list);
void	rotate_player(int keycode, t_common *d_list);
int		key_release(int keycode, t_common *d_list);



//mohamad
int		minimap(t_common *d_list);
void    caster(t_common *d_list);
void    line(t_common *d_list, double p1[2], double p2[2], int color);
double	calc_dir(double dir);
void	draw_walls(t_common *d_list);
void	move_player(t_common *d_list, double move_dir);

//texture prototypes
void    init_texture(t_texture *texture);
void    load_texture(t_common *d_list, t_texture *texture, int i);
int		my_mlx_pixel_get(t_mlx *mlx, int x, int y);
int check_the_textures_open(void);


#endif
