/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: openelop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 19:45:34 by openelop          #+#    #+#             */
/*   Updated: 2019/10/30 19:45:39 by openelop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

t_dot3d	**change_coords(t_dot3d **map, double alpha, double betta, double gamma)
{
	int i;
	int j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j].z != ARR_END)
		{
			map[i][j] = coord_creator(map[i][j], alpha, betta, gamma);
			j++;
		}
		i++;
	}
	return (map);
}

t_dot3d	**coeff_multer(t_dot3d **map, double coeff)
{
	int		i;
	int		j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j].z != ARR_END)
		{
			map[i][j].x *= coeff;
			map[i][j].y *= coeff;
			map[i][j].z *= coeff;
			j++;
		}
		i++;
	}
	return (map);
}

t_dot3d	**start_coeff_counter(t_dot3d **map)
{
	int		i;
	int		j;
	double	max_x;
	double	max_y;
	double	window;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j].z != ARR_END)
		{
			if (map[i][j].x > max_x)
				max_x = map[i][j].x;
			if (map[i][j].y > max_y)
				max_y = map[i][j].y;
			j++;
		}
		i++;
	}
	window = (WINDOW_HEIGHT < WINDOW_WIDTH) ? WINDOW_HEIGHT : WINDOW_WIDTH;
	if (max_x < max_y)
		return (coeff_multer(map, (window / (max_y * 2)) * 3 / 5));
	else
		return (coeff_multer(map, (window / (max_x * 2)) * 3 / 5));
}

int		main(int argc, char **argv)
{
	t_param		param;

	param.kx = WINDOW_WIDTH / 2;
	param.ky = WINDOW_HEIGHT / 2;
	param.m_change = get_full_line(argv[1]);
	param.mlx_ptr = mlx_init();
	param.win_ptr = mlx_new_window(param.mlx_ptr,
		WINDOW_WIDTH, WINDOW_HEIGHT, "LUXURY");
	param.m_change = change_coords(param.m_change, 0, 0, 0.785);
	param.m_change = change_coords(param.m_change, -0.68, 0, 0);
	param.m_change = start_coeff_counter(param.m_change);
	map_drawer(param.m_change, param);
	mlx_hook(param.win_ptr, 2, 2, &key_press_down, (void*)&param);
	mlx_loop(param.mlx_ptr);
	return (0);
}
