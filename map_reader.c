
#include "FdF.h"

t_dot3d		**get_full_line(char *name)
{
	int		fd;
	char	*line;
	char	*full_line;
	t_dot3d	**map_nums;

	full_line = ft_strnew(1000000);
	fd = open(name, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		full_line = ft_strjoin(full_line, line);
		full_line = ft_strjoin(full_line, "\n");
	}
	map_nums = split_more(ft_strsplit(full_line, '\n'));
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
	return (map_nums);
}

t_dot3d		**turn_into_nums(char ***nums_char, int main_lines, int i, int j)
{
	int		nums_in_line;
	t_dot3d	**map_nums;

	while (nums_char[0][i] != NULL)
		i++;
	nums_in_line = i;
	map_nums = (t_dot3d**)malloc(sizeof(t_dot3d *) * (main_lines + 1));
	map_nums[main_lines] = 0;
	i = -1;
	while (++i < main_lines)
	{
		map_nums[i] = (t_dot3d*)malloc(sizeof(t_dot3d) * (nums_in_line + 1));
		(map_nums[i][nums_in_line]).z = -1000000;
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
	return (map_nums);
}

void	print_board(t_dot3d **board)
{
	int i;
	int j;

	i = 0;
	while (board[i] != 0)
	{
		j = 0;
		while (board[i][j].z != -1000000)
		{
			if (board[i][j].z < 10)
				ft_putchar(' ');
			ft_putnbr(board[i][j].z);
			ft_putchar(' ');
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}
