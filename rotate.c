/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solympe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 13:52:44 by solympe           #+#    #+#             */
/*   Updated: 2019/10/30 13:52:46 by solympe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	take_new_place(int keycode, void *param)
{
	t_param	*new_param;

	new_param = (t_param *)param;
	if (keycode == 123)
		new_param->kx += -10;
	if (keycode == 124)
		new_param->kx += 10;
	if (keycode == 125)
		new_param->ky += 10;
	if (keycode == 126)
		new_param->ky -= 10;
}

void	close_window(void *param)
{
	t_param	*new_param;

	new_param = (t_param *)param;
	free_struct(new_param->m_change);
	mlx_clear_window(new_param->mlx_ptr, new_param->win_ptr);
	(void)param;
	exit(0);
}

void	rotat(int keycode, void *param)
{
	t_param	*new_param;

	new_param = (t_param *)param;
	if (keycode == 0)
		new_param->m_change = change_coords(new_param->m_change, 0, -0.1, 0);
	if (keycode == 2)
		new_param->m_change = change_coords(new_param->m_change, 0, 0.1, 0);
	if (keycode == 13)
		new_param->m_change = change_coords(new_param->m_change, -0.1, 0, 0);
	if (keycode == 1)
		new_param->m_change = change_coords(new_param->m_change, 0.1, 0, 0);
	if (keycode == 12)
		new_param->m_change = change_coords(new_param->m_change, 0, 0, -0.1);
	if (keycode == 14)
		new_param->m_change = change_coords(new_param->m_change, 0, 0, 0.1);
}

int		key_press_down(int keycode, void *param)
{
	t_param	*new_param;

	new_param = (t_param *)param;
	if (keycode == 0 || keycode == 2 || keycode == 13
		|| keycode == 1 || keycode == 12 || keycode == 14)
		rotat(keycode, param);
	if (keycode == 124 || keycode == 123 || keycode == 126 || keycode == 125)
		take_new_place(keycode, param);
	if (keycode == 6 || keycode == 7)
		resize_figure(keycode, *new_param);
	if (keycode == 53)
		close_window(param);
	if (keycode == 49)
		swap_projections(param);
	mlx_clear_window(new_param->mlx_ptr, new_param->win_ptr);
	map_drawer(new_param->m_change, *new_param);
	return (0);
}

void	resize_figure(int keycode, t_param new_param)
{
	int i;
	int j;

	i = 0;
	while (new_param.m_change[i] != NULL)
	{
		j = 0;
		while (new_param.m_change[i][j].z != ARR_END)
		{
			if (keycode == 7)
			{
				new_param.m_change[i][j].x *= 2;
				new_param.m_change[i][j].y *= 2;
				new_param.m_change[i][j].z *= 2;
			}
			if (keycode == 6)
			{
				new_param.m_change[i][j].x /= 2;
				new_param.m_change[i][j].y /= 2;
				new_param.m_change[i][j].z /= 2;
			}
			j++;
		}
		i++;
	}
}
