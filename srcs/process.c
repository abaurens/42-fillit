/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 14:49:57 by abaurens          #+#    #+#             */
/*   Updated: 2018/11/29 18:36:22 by abaurens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "fillit.h"
#include "libft.h"

#include <unistd.h>


static void	ft_putbin(t_int64 val, int len, int padd)
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
	while (i < 16)
	{
		ft_putbin(map[i], 16, 16);
		write(1, "\n", 1);
		i++;
	}
}

static char	render_map(t_map *map, int yy, t_int64 p, const int j)
{
	int		y;
	int		x;
	int		len;

	y = -1;
	len = ((map->size + 1) * map->size);
	/*if (j + 1 == PIECE_COUNT)
		print_map(map->map);*/
	if (!map->res && !(map->res = ft_memalloc(sizeof(char) * (len + 1))))
		return (-1);
	while (++y < map->size)
	{
		x = -1;
		while (++x < map->size)
		{
			if (map->res[x + y * (map->size + 1)] == 0)
				map->res[x + y * (map->size + 1)] = '.';
			if ((p >> ((16 * (y - yy)) + (15 - x))) & 1)
				map->res[x + y * (map->size + 1)] = ('A' + j);
		}
		map->res[x + y * (map->size + 1)] = '\n';
	}
	return (1);
}

static char	btrk(t_map *map, const int size, const int j)
{
	int		x;
	int		y;
	t_int64	p;
	t_int64	*frag;

	y = -1;
	print_map(map->map);
	write(1, "\n", 1);
	while (++y < size - (map->pieces[j].h - 1) && (x = -1))
	{
		p = map->pieces[j].val;
		frag = (t_int64 *)&(map->map[y]);
		while (++x < size - (map->pieces[j].w - 1))
		{
			if ((*frag & p) == 0)
			{
				*frag ^= p;
				if (j + 1 >= PIECE_COUNT || btrk(map, size, j + 1))
					return (render_map(map, y, p, j));
				*frag ^= p;
			}
			p >>= 1;
		}
	}
	return (0);
}

static void	debug_print_piece(t_piece *piece, int padd)
{
	t_test	p;
	int		l;

	p.all = piece->val;
	l = -1;
	printf("=============%2d,%2d=============\n", piece->w, piece->h);
	while (++l < padd)
		write(1, "\t", 1);
	ft_putbin(p.quar[0], 16, 16);
	write(1, "\n", 1);
	l = -1;
	while (++l < padd)
		write(1, "\t", 1);
	ft_putbin(p.quar[1], 16, 16);
	write(1, "\n", 1);
	l = -1;
	while (++l < padd)
		write(1, "\t", 1);
	ft_putbin(p.quar[2], 16, 16);
	write(1, "\n", 1);
	l = -1;
	while (++l < padd)
		write(1, "\t", 1);
	ft_putbin(p.quar[3], 16, 16);
	write(1, "\n", 1);
	printf("===============================\n");
}

char		process(t_map *map)
{
	char	lp;

	lp = 0;
	map->size = 2;
	map->res = NULL;
	while (lp == 0)
		if ((lp = btrk(map, map->size, 0)) == 0)
			map->size++;
	if (lp < 0)
		return (1);
	ft_putstr(map->res);
	free(map->res);
	return (0);
}

t_piece		convert_piece(const char tab[4][4])
{
	t_vec2	pos;
	t_int64	val;
	t_piece	ret;

	pos.y = 4;
	ft_bzero(&ret, sizeof(ret));
	while (--pos.y >= 0 && (pos.x = -1))
	{
		while (++pos.x < 4 && ((ret.val <<= 1) || 1))
			if (tab[pos.y][pos.x] == '#')
				ret.val |= 1;
		ret.val <<= (16 - 4);
	}
	while ((ret.val & 0b1111111111111111) == 0)
		ret.val >>= 16;
	while ((ret.val & MASK) == 0)
		ret.val <<= 1;
	val = ret.val;
	while ((val & (MASK >> ret.w)) != 0)
		ret.w++;
	val = ret.val;
	while (val >> (ret.h * 16) != 0)
		ret.h++;
	return (ret);
}

const char	g_pieces[PIECE_COUNT][4][4] =
{
	{
		"....",
		"##..",
		".##.",
		"...."
	},
	{
		"....",
		".##.",
		".##.",
		"...."
	},
	{
		"...",
		"#...",
		"#...",
		"##.."
	},
	{
		"....",
		"...#",
		"..##",
		"...#"
	},
	{
		"....",
		"....",
		"....",
		"####"
	}
};

int			main(void)
{
	int		i;
	t_map	map;
	t_piece	p;

	i = 0;
	while (i < PIECE_COUNT)
	{
		map.pieces[i] = convert_piece(g_pieces[i]);
		/*debug_print_piece(&p, 0);*/
		/*write(1, "\n\n", 2);*/
		i++;
	}
	process(&map);
	return (0);
}

/*
int			main(void)
{
	int		i;
	t_int16	t;
	t_map	map;

	i = 0;
	t = 0b0000000000010000;
	t = 0;
	map.pieces[0].val = 0b0000000000000000010000000000000001000000000000001100000000000000;
	map.pieces[0].w = 2;
	map.pieces[0].h = 3;
	map.pieces[1].val = 0b0000000000000000000000000000000000000000000000001111000000000000;
	map.pieces[1].w = 4;
	map.pieces[1].h = 1;
	map.pieces[2].val = 0b0000000000000000000000000000000011100000000000001000000000000000;
	map.pieces[2].w = 3;
	map.pieces[2].h = 2;
	map.pieces[3].val = 0b0000000000000000000000000000000001100000000000001100000000000000;
	map.pieces[3].w = 3;
	map.pieces[3].h = 2;
	while (i < 16)
		map.map[i++] = t;
	return (process(&map));
}
*/
