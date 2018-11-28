/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 14:49:57 by abaurens          #+#    #+#             */
/*   Updated: 2018/11/28 21:43:59 by abaurens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include "fillit.h"

void		debug_print_piece(t_int64 piece, int padd)
{
	t_test	p;
	int		l;

	p.all = piece;
	l = -1;
	while (++l < padd)
		write(1, "\t", 1);
	ft_putbin(p.quar[3], 16, 16);
	write(1, "\n", 1);
	l = -1;
	while (++l < padd)
		write(1, "\t", 1);
	ft_putbin(p.quar[2], 16, 16);
	write(1, "\n", 1);
	l = -1;
	while (++l < padd)
		write(1, "\t", 1);
	ft_putbin(p.quar[1], 16, 16);
	write(1, "\n", 1);
	l = -1;
	while (++l < padd)
		write(1, "\t", 1);
	ft_putbin(p.quar[0], 16, 16);
	write(1, "\n", 1);
}

void		ft_putbin(t_int64 val, int len, int padd)
{
	char	c;

	if (len <= 0)
		len = 1;
	if (val / 2 != 0 || (len - 1) > 0)
		ft_putbin(val / 2, len - 1, padd);
	c = val % 2 + '0';
	if ((len - 1) > 0 && (len - 1) % padd == 0)
		write(1, " ", 1);
	if (c == '1')
		write(1, "\e[32;40m", strlen("\e[32;40m"));
	write(1, &c, 1);
	write(1, " ", 1);
	if (c == '1')
		write(1, "\e[0m", strlen("\e[0m"));
}

void		print_map(t_int16 map[16])
{
	int		i;

	i = 0;
	system("clear");
	while (i < 16)
	{
		ft_putbin(map[i], 16, 16);
		write(1, "\n", 1);
		i++;
	}
}

void		get_used_space(t_map *map)
{
	int		h;
	int		w;
	int		sw;
	t_int16	ln;

	h = 0;
	sw = 0;
	while (h < 16 && map->map[h] == 0)
		h++;
	while (h < 16 && map->map[h] != 0)
	{
		w = 16;
		ln = map->map[h];
		while ((ln & 1) == 0)
		{
			w--;
			ln >>= 1;
		}
		if (sw < w)
			sw = w;
		h++;
	}
	if ((sw = max(sw, h)) < map->best)
	{
		map->best = sw;
		print_map(map->map);
		printf("square is at most {%d x %d}\n", map->best, map->best);
	}
}

void		backtrack2(t_map *map, int j)
{
	char	lp;
	int		x;
	int		i;
	int		y;
	t_int64	p;
	t_int64	*frag;

	lp = 1;
	while (lp)
	{
		y = 0;
		while (y <= (map->best - PIECE_HEIGHT))
		{
			i = 0;
			x = 0;
			p = map->pieces[j];
			frag = (t_int64 *)&(map->map[y]);
			while (i == 0 && x < (map->best - PIECE_WIDTH))
			{
				if ((*frag & p) == 0)
				{
					lp = 0;
					*frag ^= p;
					if (j < 1)
						backtrack2(map, j + 1);
					else
					{
						print_map(map->map);
						printf("Best square is {%d, %d}\n", map->best, map->best);
						exit(0);
					}
				}
				i = (MASK & p);
				p >>= 1;
				x++;
			}
			y++;
		}
		if (lp)
			map->best++;
	}
}

int		backtrack1(t_map *map, int j)
{
	int		y;
	int		x;
	int		i;
	t_int64	*frag;
	t_int64	p;

	y = 0;
	while (y < (map->best - 4))
	{
		frag = (t_int64 *)&(map->map[y]);
		p = map->pieces[j];
		i = 0;
		x = 0;
		while (i == 0 && x < (map->best - 1))
		{
			if ((*frag & p) == 0)
			{
				printf("%d - %d\n", x, y);
				*frag ^= p;
				if (j < 7)
					backtrack1(map, j + 1);
				else
				{
					/*print_map(map);*/
					/*usleep(10000);*/
					/*read(0, NULL, 1);*/
					get_used_space(map);
				}
				*frag ^= p;
			}
			i = (MASK & p);
			p >>= 1;
			x++;
		}
		y++;
	}
	return (0);
}

int			main(void)
{
	int		i;
	t_int16	t;
	t_map	map;

	i = 0;
	map.best = 2;
	t = 0b0000000000010000;
	t = 0;
	map.pieces[0] = 0b1110000000000000100000000000000010000000000000001000000000000000;
	map.pieces[1] = 0b1000000000000000111000000000000010000000000000001000000000000000;
	map.pieces[2] = 0b1000000000000000100000000000000010000000000000001000000000000000;
	map.pieces[3] = 0b1000000000000000100000000000000010000000000000001000000000000000;
	map.pieces[4] = 0b1000000000000000100000000000000010000000000000001000000000000000;
	map.pieces[5] = 0b1000000000000000100000000000000010000000000000001000000000000000;
	map.pieces[6] = 0b1000000000000000100000000000000010000000000000001000000000000000;
	map.pieces[7] = 0b1000000000000000100000000000000010000000000000001000000000000000;
	map.pieces[8] = 0b1000000000000000100000000000000010000000000000001000000000000000;
	map.pieces[9] = 0b1000000000000000100000000000000010000000000000001000000000000000;
	map.pieces[10] = 0b1000000000000000100000000000000010000000000000001000000000000000;
	map.pieces[11] = 0b1000000000000000100000000000000010000000000000001000000000000000;
	map.pieces[12] = 0b1000000000000000100000000000000010000000000000001000000000000000;
	map.pieces[13] = 0b1000000000000000100000000000000010000000000000001000000000000000;
	map.pieces[14] = 0b1000000000000000100000000000000010000000000000001000000000000000;
	map.pieces[15] = 0b1000000000000000100000000000000010000000000000001000000000000000;
	map.pieces[16] = 0b1000000000000000100000000000000010000000000000001000000000000000;
	map.pieces[17] = 0b1000000000000000100000000000000010000000000000001000000000000000;
	map.pieces[18] = 0b1000000000000000100000000000000010000000000000001000000000000000;
	map.pieces[19] = 0b1000000000000000100000000000000010000000000000001000000000000000;
	map.pieces[20] = 0b1000000000000000100000000000000010000000000000001000000000000000;
	map.pieces[21] = 0b1000000000000000100000000000000010000000000000001000000000000000;
	map.pieces[22] = 0b1000000000000000100000000000000010000000000000001000000000000000;
	map.pieces[23] = 0b1000000000000000100000000000000010000000000000001000000000000000;
	map.pieces[24] = 0b1000000000000000100000000000000010000000000000001000000000000000;
	map.pieces[25] = 0b1000000000000000100000000000000010000000000000001000000000000000;
	while (i < 16)
		map.map[i++] = t;
	print_map(map.map);
	write(1, "\n", 1);
	backtrack2(&map, 0);
	return (0);
}
