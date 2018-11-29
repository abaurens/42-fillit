/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 14:49:57 by abaurens          #+#    #+#             */
/*   Updated: 2018/11/29 04:56:52 by abaurens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "fillit.h"
#include "libft.h"

char		render_map(t_map *map, int yy, t_int64 p, const int j)
{
	int		y;
	int		x;
	int		len;

	y = -1;
	len = ((map->size + 1) * map->size);
	if (j + 1 == PIECE_COUNT)
		print_map(map->map);
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

char		btrk(t_map *map, const int size, const int j)
{
	int		x;
	int		y;
	t_int64	p;
	t_int64	*frag;

	y = -1;
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
