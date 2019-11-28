/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_me.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: openelop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 14:38:57 by openelop          #+#    #+#             */
/*   Updated: 2019/11/04 14:39:00 by openelop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	swap_projections(void *param)
{
	t_param	*new_param;

	new_param = (t_param *)param;
	new_param->kx = WINDOW_WIDTH / 2;
	new_param->ky = WINDOW_HEIGHT / 2;
	new_param->m_change = get_full_line(new_param->fname);
	if (new_param->indic == 0)
	{
		new_param->m_change = change_coords(new_param->m_change, 0, 0, 0.785);
		new_param->m_change = change_coords(new_param->m_change, -0.68, 0, 0);
		new_param->indic = 1;
	}
	else
		new_param->indic = 0;
	new_param->m_change = start_coeff_counter(new_param->m_change);
}
