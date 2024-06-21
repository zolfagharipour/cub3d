#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <unistd.h>
# include <mlx.h>
# include <stdio.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>

# define HEIGHT 500
# define WIDTH 500
# define W_SQUARE 20
# define RED 0xFF0000

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
	int		**minimap;
}	t_map;

typedef struct s_common
{
	t_mlx	*mlx;
	t_map 	*map;
} t_common;

//setup
int		main(void);
void	init_mlx(t_mlx *mlx);
int		init_struct(t_mlx *mlx);
void    put_red_square(t_mlx *mlx);
int		cleanup(t_mlx *mlx);
void	put_image(t_mlx *mlx);
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);

//events
void	events(t_mlx *mlx);
int		key_press(int keycode, t_mlx *mlx);
void	move_window(int keycode, t_mlx *mlx);

//mohamad
int		minimap(t_common *d_list);

#endif
