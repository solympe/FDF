#include "FdF.h"

t_dot3d		**map_nums_changed;
void	*mlx_ptr;
void	*win_ptr;
int     size;

void	swap_xy(t_dot3d *d1, t_dot3d *d2)
{
	int tmp;

	tmp = (*d1).x;
	(*d1).x = (*d1).y;
	(*d1).y = tmp;

	tmp = (*d2).x;
	(*d2).x = (*d2).y;
	(*d2).y = tmp;
}

void	swap_dots(t_dot3d *d1, t_dot3d *d2)
{
	t_dot3d tmp;

	tmp = *d1;
	*d1 = *d2;
	*d2 = tmp;
}

void	line_putter(void *mlx_ptr, void *win_ptr, t_dot3d d1, t_dot3d d2)
{
	int deltaX;
	int deltaY;
	int j;
	int Etta;
	int i;
	int indic;

	indic = 0;
	if (fabs(d2.y - d1.y) > fabs(d2.x - d1.x))
	{
		swap_xy(&d1, &d2);
		indic = 1;
	}
	if (d1.x > d2.x)
		swap_dots(&d1, &d2);
	deltaX = d2.x - d1.x;
	deltaY = d2.y - d1.y;
	j = d1.y;
	Etta = deltaY - deltaX;
	i = d1.x;
	while (i < d2.x)
	{
		if (indic == 1)
			mlx_pixel_put(mlx_ptr, win_ptr, j + WINDOW_HEIGHT / 2, i + WINDOW_WIGHT / 2, 0XFFFFFFF);
		else
			mlx_pixel_put(mlx_ptr, win_ptr, i + WINDOW_WIGHT / 2, j + WINDOW_HEIGHT / 2, 0XFFFFFFF);
		if (Etta >= 0)
		{
			if (deltaY < 0)
				j--;
			else
				j++;
			Etta -= deltaX;
		}
		i++;
		if (deltaY < 0)
			Etta -= deltaY;
		else
			Etta += deltaY;
	}
}

t_dot3d	coord_creator(t_dot3d dot, double x, double y, double z)
{
    t_dot3d new_dot;
    new_dot.x = dot.x;
    new_dot.y = dot.y;
    new_dot.z = dot.z;

    if (x != 0)
    {
        new_dot.y = dot.y * cos(x) + dot.z * sin(x);
        new_dot.z = -dot.y * sin(x) + dot.z * cos(x);
    }
    if (y != 0)
    {
        new_dot.x = dot.x * cos(y) + dot.z * sin(y);
        new_dot.z = -dot.x * sin(y) + dot.z * cos(y);
    }
    if (z != 0)
    {
        new_dot.x = dot.x * cos(z) - dot.y * sin(z);
        new_dot.y = dot.x * sin(z) + dot.y * cos(z);
    }
    return (new_dot);
}
/*
void	print_map(t_dot3d **board)
{
	int i;
	int j;

	i = 0;
	while (board[i] != NULL)
	{
		j = 0;
		while (board[i][j].z != -1000000)
		{
			if (board[i][j].x < 10)
				ft_putchar(' ');
			ft_putnbr(board[i][j].y);
			ft_putchar(' ');
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}
*/
t_dot3d	**change_coords(t_dot3d **map, double alpha, double betta, double gamma)
{
	int i;
	int j;

	i = 0;
	while (map[i] != NULL)
	{
			j = 0;
			while (map[i][j].z != -1000000)
			{
				map[i][j] = coord_creator(map[i][j], alpha, betta, gamma);
				//////////////////////////
				if (size != 1)
				{
                    map[i][j].x *= 30;
                    map[i][j].y *= 30;
                }
				/////////////////////////
				j++;
			}
		i++;
	}
	size = 1;
	//print_map(map);
	return (map);
}

void	map_drawer(void *mlx_ptr, void* win_ptr, t_dot3d **map)
{
	int i;
	int j;

	i = 1;
	while (map[i] != NULL)
	{
			j = 1;
			while (map[i][j].z != -1000000)
			{
				mlx_pixel_put(mlx_ptr, win_ptr, map[i][j].x + WINDOW_WIGHT / 2, map[i][j].y + WINDOW_HEIGHT / 2, 0XFFFFFFF);
				line_putter(mlx_ptr, win_ptr, map[i][j - 1], map[i][j]);
				line_putter(mlx_ptr, win_ptr, map[i - 1][j], map[i][j]);
				j++;
			}
		i++;
	}
	mlx_pixel_put(mlx_ptr, win_ptr, map[0][0].x + WINDOW_WIGHT / 2, map[0][0].y + WINDOW_HEIGHT / 2, 0XFFFFFFF);
	i = 1;
	while (map[i] != NULL)
	{
		line_putter(mlx_ptr, win_ptr, map[i - 1][0], map[i][0]);
		i++;
	}
	i = 1;
	while (map[0][i].z != -1000000)
	{
		line_putter(mlx_ptr, win_ptr, map[0][i - 1], map[0][i]);
		i++;
	}
}


int key_press_down(int keycode,  void *param)
{
    if (keycode == 0)
        map_nums_changed = change_coords(map_nums_changed, 0, -0.1, 0);
    if (keycode == 2)
        map_nums_changed = change_coords(map_nums_changed, 0, 0.1, 0);
    if (keycode == 13)
        map_nums_changed = change_coords(map_nums_changed, -0.1, 0, 0);
    if (keycode == 1)
        map_nums_changed = change_coords(map_nums_changed, 0.1, 0, 0);
    if (keycode == 12)
        map_nums_changed = change_coords(map_nums_changed, 0, 0, -0.1);
    if (keycode == 14)
        map_nums_changed = change_coords(map_nums_changed, 0, 0, 0.1);

    if (keycode == 124)
    {
        int i;
        int j;

        i = 0;
        while (map_nums_changed[i] != NULL)
        {
            j = 0;
            while (map_nums_changed[i][j].z != -1000000) {
                map_nums_changed[i][j].x += 10;
                map_nums_changed[i][j].y += 0;
                j++;
            }
            i++;
        }
    }

    if (keycode == 123)
    {
        int i;
        int j;

        i = 0;
        while (map_nums_changed[i] != NULL)
        {
            j = 0;
            while (map_nums_changed[i][j].z != -1000000) {
                map_nums_changed[i][j].x += -10;
                map_nums_changed[i][j].y += 0;
                j++;
            }
            i++;
        }
    }

    if (keycode == 126)
    {
        int i;
        int j;

        i = 0;
        while (map_nums_changed[i] != NULL)
        {
            j = 0;
            while (map_nums_changed[i][j].z != -1000000) {
                map_nums_changed[i][j].x += 0;
                map_nums_changed[i][j].y += -10;
                j++;
            }
            i++;
        }
    }

    if (keycode == 125)
    {
        int i;
        int j;

        i = 0;
        while (map_nums_changed[i] != NULL)
        {
            j = 0;
            while (map_nums_changed[i][j].z != -1000000) {
                map_nums_changed[i][j].x += 0;
                map_nums_changed[i][j].y += 10;
                j++;
            }
            i++;
        }
    }

    if (keycode == 6)
    {
        int i;
        int j;

        i = 0;
        while (map_nums_changed[i] != NULL) {
            j = 0;
            while (map_nums_changed[i][j].z != -1000000) {
                map_nums_changed[i][j] = coord_creator(map_nums_changed[i][j], 0, 0, 0);
                //////////////////////////
                    map_nums_changed[i][j].x *= 2;
                    map_nums_changed[i][j].y *= 2;
                /////////////////////////
                j++;
            }
            i++;
        }
    }

    if (keycode == 7)
    {
            int i;
            int j;

            i = 0;
            while (map_nums_changed[i] != NULL) {
                j = 0;
                while (map_nums_changed[i][j].z != -1000000) {
                    map_nums_changed[i][j] = coord_creator(map_nums_changed[i][j], 0, 0, 0);
                    //////////////////////////
                    map_nums_changed[i][j].x /= 2;
                    map_nums_changed[i][j].y /= 2;
                    /////////////////////////
                    j++;
                }
                i++;
            }
    }

    mlx_clear_window(mlx_ptr, win_ptr);
    map_drawer(mlx_ptr, win_ptr, map_nums_changed);

    return (0);
}

int		main(int argc, char **argv)
{
    size = 0;
	t_dot3d		**map_nums;

	///////////////////////////////////////////////////////
	map_nums = get_full_line(argv[1]);
	print_board(map_nums);
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, WINDOW_WIGHT, WINDOW_HEIGHT, "Eto moe okno");
	///////////////////////////////////////////////////////////////////////////////////////


	map_nums_changed = map_nums;
	map_nums_changed = change_coords(map_nums_changed, 0, 0, 0);
	map_drawer(mlx_ptr, win_ptr, map_nums_changed);
	///////////////////////////////////////////////////////////////////////
	// ROTATE
    mlx_hook(win_ptr, 2, 2, &key_press_down, (void*)0);
	/////////////////////////////////////////////////////
	mlx_loop(mlx_ptr);
	return (0);
}

