/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: openelop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 19:40:14 by openelop          #+#    #+#             */
/*   Updated: 2019/10/30 19:40:27 by openelop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	swap_xy(t_dot3d *d1, t_dot3d *d2, int *indic)
{
	int tmp;

	tmp = (*d1).x;
	(*d1).x = (*d1).y;
	(*d1).y = tmp;
	tmp = (*d2).x;
	(*d2).x = (*d2).y;
	(*d2).y = tmp;
	*indic = 1;
}

void	swap_dots(t_dot3d *d1, t_dot3d *d2)
{
	t_dot3d tmp;

	tmp = *d1;
	*d1 = *d2;
	*d2 = tmp;
}

void	line_putter(t_param param, t_dot3d d1, t_dot3d d2)
{
	t_kostil	bres;
	int			j;
	int			i;

	bres.indic = 0;
	if (fabs(d2.y - d1.y) > fabs(d2.x - d1.x))
		swap_xy(&d1, &d2, &bres.indic);
	if (d1.x > d2.x)
		swap_dots(&d1, &d2);
	bres.delta_x = d2.x - d1.x;
	bres.delta_y = d2.y - d1.y;
	j = d1.y;
	bres.etta = bres.delta_y - bres.delta_x;
	i = d1.x - 1;
	while (++i < d2.x)
	{
		mlx_pixel_put(param.mlx_ptr, param.win_ptr, ((bres.indic == 1) ? j : i)
		+ param.kx, ((bres.indic == 1) ? i : j) + param.ky, 0XFFFFFFF);
		if (bres.etta >= 0)
		{
			j += (bres.delta_y < 0) ? -1 : 1;
			bres.etta -= bres.delta_x;
		}
		bres.etta += (bres.delta_y < 0) ? -bres.delta_y : bres.delta_y;
	}
}
