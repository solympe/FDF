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
	char	*tmp;

	full_line = ft_strnew(1);
	fd = open(name, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		tmp = ft_strjoin(full_line, line);
		free(full_line);
		full_line = tmp;
		tmp = ft_strjoin(full_line, "\n");
		free(full_line);
		full_line = tmp;
		free(line);
	}
	map_nums = split_more(ft_strsplit(full_line, '\n'));
	free(full_line);
	return (map_nums);
}

t_dot3d		**split_more(char **board)
{
	int		i;
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
	map_nums = turn_into_nums(nums_char, main_lines);
	i = -1;
	while (board[++i] != NULL)
		free(board[i]);
	free(board);
	return (map_nums);
}

t_dot3d		**free_struct_3_dim(char ***nums_char,
	int main_lines, t_dot3d **map_nums, int indic)
{
	int i;
	int j;

	i = -1;
	while (++i < main_lines)
	{
		j = -1;
		while (nums_char[i][++j] != NULL)
			free(nums_char[i][j]);
		free(nums_char[i]);
	}
	free(nums_char);
	if (indic == 1)
	{
		i = 0;
		while (i < main_lines)
		{
			free(map_nums[i]);
			i++;
		}
		free(map_nums);
		return (NULL);
	}
	return (map_nums);
}

t_dot3d		**struct_arr_creator(char ***nums_char,
	int main_lines, int *nums_in_line)
{
	int		i;
	t_dot3d	**map_nums;

	i = 0;
	while (nums_char[0][i++] != NULL)
		*nums_in_line = i;
	map_nums = (t_dot3d**)malloc(sizeof(t_dot3d *) * (main_lines + 1));
	map_nums[main_lines] = 0;
	i = -1;
	while (++i < main_lines)
	{
		map_nums[i] = (t_dot3d*)malloc(sizeof(t_dot3d) * (*nums_in_line + 1));
		(map_nums[i][*nums_in_line]).z = ARR_END;
	}
	return (map_nums);
}

t_dot3d		**turn_into_nums(char ***nums_char, int main_lines)
{
	int		nums_in_line;
	t_dot3d	**map_nums;
	int		i;
	int		j;

	map_nums = struct_arr_creator(nums_char, main_lines, &nums_in_line);
	i = -1;
	while (++i < main_lines)
	{
		j = -1;
		if (nums_char[i][nums_in_line] != NULL)
			return (free_struct_3_dim(nums_char, main_lines, map_nums, 1));
		while (++j < nums_in_line)
		{
			if (nums_char[i][j] == NULL)
				return (free_struct_3_dim(nums_char, main_lines, map_nums, 1));
			map_nums[i][j].z = ft_atoi(nums_char[i][j]);
			map_nums[i][j].x = j - (nums_in_line + 1) / 2;
			map_nums[i][j].y = i - (main_lines - 1) / 2;
		}
	}
	return (free_struct_3_dim(nums_char, main_lines, map_nums, 0));
}
