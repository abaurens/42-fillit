/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 22:02:22 by abaurens          #+#    #+#             */
/*   Updated: 2018/12/03 01:39:19 by abaurens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "fillit.h"
#include "libft.h"

int			print_usage(void)
{
	write(1, "Usage ./fillit FILE\n", 20);
	write(1, "\tFILE : a file containing the tetriminos list.\n", 47);
	return (1);
}

static int	cnt_neighbours(const char tab[4][4], t_vec2 pos)
{
	int		neighbours;

	neighbours = (pos.y > 0 && tab[pos.y - 1][pos.x] == '#');
	neighbours += (pos.y < 3 && tab[pos.y + 1][pos.x] == '#');
	neighbours += (pos.x > 0 && tab[pos.y][pos.x - 1] == '#');
	return (neighbours + (pos.x < 3 && tab[pos.y][pos.x + 1] == '#'));
}

static int	check_piece(const char tab[4][4])
{
	t_vec2	pos;
	int		dual;
	int		ngbr;
	int		parts;

	dual = 0;
	parts = 0;
	pos.y = -1;
	while (++pos.y < 4)
	{
		pos.x = -1;
		while (++pos.x < 4)
		{
			if (tab[pos.y][pos.x] == '.')
				continue;
			if (++parts > 4 || (ngbr = cnt_neighbours(tab, pos)) > 3)
				return (ERROR);
			if (ngbr > 1)
				dual += (ngbr - 1);
		}
	}
	if (parts < 4 || dual < 2)
		return (ERROR);
	return (SUCCESS);
}

static int	read_piece(const int fd, char tab[4][4])
{
	int		i;
	int		len;
	int		line;
	char	buffer[5];

	line = 0;
	while (line < 4 && (len = read(fd, buffer, 5)) > 0)
	{
		i = 0;
		if (len < 5 || buffer[4] != '\n')
			return (ERROR);
		while (i < 4)
		{
			if (buffer[i] != '.' && buffer[i] != '#')
				return (ERROR);
			i++;
		}
		ft_memcpy(tab[line], buffer, 4);
		line++;
	}
	if (line < 4 || len < 0)
		return (ERROR);
	return (SUCCESS);
}

int			parse_file(const char *file, t_map *map)
{
	int		fd;
	int		len;
	int		piece;
	char	buffer;
	char	tab[4][4];

	piece = 0;
	if (!map || !file || (fd = open(file, O_RDONLY)) < 0)
		return (ERROR);
	while (!piece || (len = read(fd, &buffer, 1)) > 0)
	{
		if (piece == MAX_PIECE || (piece && (len == 0 || buffer != '\n')))
			return (ERROR);
		if (read_piece(fd, tab) == ERROR)
			return (ERROR);
		if (check_piece(tab) == ERROR)
			return (ERROR);
		map->pieces[piece] = convert_piece(tab);
		piece++;
	}
	map->piece_count = piece;
	if (close(fd) < 0 || len < 0)
		return (ERROR);
	return (SUCCESS);
}
