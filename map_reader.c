/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: openelop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 19:43:12 by openelop          #+#    #+#             */
/*   Updated: 2019/10/30 19:43:17 by openelop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_dot3d		**get_full_line(char *name)
{
	int		fd;
	char	*line;
	char	*full_line;
	t_dot3d	**map_nums;

	full_line = ft_strnew(1);
	fd = open(name, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		full_line = ft_strjoin(full_line, line);
		full_line = ft_strjoin(full_line, "\n");
		free(line);
	}
	map_nums = split_more(ft_strsplit(full_line, '\n'));
	free(full_line);
	return (map_nums);
}

t_dot3d		**split_more(char **board)
{
	int		i;
	int		j;
	char	***nums_char;
	int		main_lines;
	t_dot3d	**map_nums;

	i = 0;
	while (board[i] != NULL)
		i++;
	main_lines = i;
	nums_char = (char***)malloc(sizeof(char **) * (main_lines + 1));
	nums_char[main_lines] = 0;
	i = 0;
	while (board[i] != NULL)
	{
		nums_char[i] = ft_strsplit(board[i], ' ');
		i++;
	}
	map_nums = turn_into_nums(nums_char, main_lines, 0, -1);
	i = -1;
	while (board[++i] != NULL)
		free(board[i]);
	free(board);
	return (map_nums);
}

void		free_struct_3_dim(char ***nums_char, int main_lines)
{
	int i;
	int j;

	i = 0;
	while (i < main_lines)
	{
		j = 0;
		while (nums_char[i][j] != NULL)
		{
			free(nums_char[i][j]);
			j++;
		}
		free(nums_char[i]);
		i++;
	}
	free(nums_char);
}

t_dot3d		**turn_into_nums(char ***nums_char, int main_lines, int i, int j)
{
	int		nums_in_line;
	t_dot3d	**map_nums;

	while (nums_char[0][i++] != NULL)
		nums_in_line = i;
	map_nums = (t_dot3d**)malloc(sizeof(t_dot3d *) * (main_lines + 1));
	map_nums[main_lines] = 0;
	i = -1;
	while (++i < main_lines)
	{
		map_nums[i] = (t_dot3d*)malloc(sizeof(t_dot3d) * (nums_in_line + 1));
		(map_nums[i][nums_in_line]).z = ARR_END;
	}
	i = -1;
	while (++i < main_lines)
	{
		j = -1;
		while (++j < nums_in_line)
		{
			map_nums[i][j].z = ft_atoi(nums_char[i][j]);
			map_nums[i][j].x = j - (nums_in_line + 1) / 2;
			map_nums[i][j].y = i - (main_lines - 1) / 2;
		}
	}
	free_struct_3_dim(nums_char, main_lines);
	return (map_nums);
}

void		map_drawer(t_dot3d **map, t_param param)
{
	int i;
	int j;

	i = 1;
	while (map[i] != NULL)
	{
		j = 1;
		while (map[i][j].z != ARR_END)
		{
			line_putter(param, map[i][j - 1], map[i][j]);
			line_putter(param, map[i - 1][j], map[i][j]);
			j++;
		}
		i++;
	}
	i = 0;
	while (map[++i] != NULL)
		line_putter(param, map[i - 1][0], map[i][0]);
	i = 0;
	while (map[0][++i].z != ARR_END)
		line_putter(param, map[0][i - 1], map[0][i]);
}
