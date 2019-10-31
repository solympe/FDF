/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: openelop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 19:45:23 by openelop          #+#    #+#             */
/*   Updated: 2019/10/30 19:45:29 by openelop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <mlx.h>
# include <math.h>

# define WINDOW_WIDTH 1000
# define WINDOW_HEIGHT 1000
# define ARR_END -2147483648

typedef struct	s_dot3d
{
	double	x;
	double	y;
	double	z;
}				t_dot3d;

typedef struct	s_param
{
	t_dot3d		**m_change;
	void		*mlx_ptr;
	void		*win_ptr;
	double		kx;
	double		ky;
}				t_param;

typedef struct	s_kostil
{
	int			delta_x;
	int			delta_y;
	int			etta;
	int			indic;
}				t_kostil;

t_dot3d			**get_full_line(char *name);
t_dot3d			**split_more(char **board);
t_dot3d			**turn_into_nums(char ***nums_char,
	int main_lines, int i, int j);

void			swap_xy(t_dot3d *d1, t_dot3d *d2, int *indic);
void			swap_dots(t_dot3d *d1, t_dot3d *d2);
void			line_putter(t_param param, t_dot3d d1, t_dot3d d2);

t_dot3d			coord_creator(t_dot3d dot, double x, double y, double z);
t_dot3d			**change_coords(t_dot3d **map,
	double alpha, double betta, double gamma);
void			map_drawer(t_dot3d **map, t_param param);
t_dot3d			**coeff_multer(t_dot3d **map, double coeff);
t_dot3d			**start_coeff_counter(t_dot3d **map);

void			take_new_place(int keycode, void *new_param);
void			resize_figure(int keycode, t_param new_param);
int				key_press_down(int keycode, void *param);

#endif
