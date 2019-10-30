#ifndef FDF_H
# define FDF_H
# include "libft/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <stdio.h>
# include <mlx.h>
# include <math.h>

#define WINDOW_WIGHT 1000
#define WINDOW_HEIGHT 1000

typedef struct	s_dot3d
{
	double	x;
	double	y;
	double	z;
}				t_dot3d;

typedef struct  s_param
{
    void	*mlx_ptr;
    void	*win_ptr;
    int     size;
};

t_dot3d		**get_full_line(char *name);
t_dot3d		**split_more(char **board);
t_dot3d		**turn_into_nums(char ***nums_char, int main_lines, int i, int j);
t_dot3d     **change_coords(t_dot3d **map, double alpha, double betta, double gamma);
t_dot3d	    coord_creator(t_dot3d dot, double x, double y, double z);


void	print_board(t_dot3d **board);
int     key_press_down(int keycode,  void *param);


#endif
