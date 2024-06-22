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

# define HEIGHT 800
# define WIDTH 800
# define W_SQUARE 20
# define RED 0xec956c
# define LBLUE 0xADD8E6
# define DBLUE 0x547eae
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
}	t_mlx;

typedef struct s_map
{
	int		**raw_map;
	int		raw_length;
	int		raw_height;
	int		scale;
	int		**minimap;
}	t_map;

typedef struct s_hook
{
	double		pos[2];
	double		dir;
} t_hook;


typedef struct	s_raycaster
{
	double		pos[2];
	double		look;
	double		dir;
	int			steps[2];
	int			ray[2];
	double		hit[WIDTH][2];
	int			length[2];
} t_rc;

typedef struct s_common
{
	t_mlx	*mlx;
	t_map 	*map;
	t_rc	*rc;
} t_common;

//setup
int		main(void);
int		init_structs(t_common *d_list);
void	init_mlx(t_mlx *mlx);
void	init_map(t_map *map);
int		init_mlx_functions(t_common *d_list);
void    put_red_square(t_common *d_list);
void	put_image(t_common *d_list, t_mlx *mlx);
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);


//testing
int test_map(t_common *d_list);
int malloc_raw_map(t_common *d_list);
void print_map(t_map *map);


//cleanup
int		cleanup(t_common *d_list);
void    cleanup_mlx(t_mlx *mlx);
void    cleanup_map(t_map *map);;
void    cleanup_d_list(t_common *d_list);

//events
void	events(t_common *d_list);
int		key_press(int keycode, t_common *d_list);
void	move_window(int keycode, t_common *d_list);


//mohamad
int		minimap(t_common *d_list);

#endif
