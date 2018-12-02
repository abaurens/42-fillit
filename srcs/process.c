/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 14:49:57 by abaurens          #+#    #+#             */
/*   Updated: 2018/12/02 10:56:34 by abaurens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fillit.h"
#include "libft.h"
/*
#include <stdio.h> ///
#include <unistd.h> ///

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
*/
static char	*create_map(const int size)
{
	int		y;
	int		len;
	char	*ret;

	y = -1;
	len = ((size + 1) * size);
	if (!(ret = ft_memalloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_memset(ret, '.', len);
	while (++y < size)
		ret[size + (y * (size + 1))] = '\n';
	return (ret);
}

static char	render_map(t_map *map, t_piece *p, const int j)
{
	t_vec2	cpos;
	t_vec2	pos;

	while((p->val & MASK) == 0)
		p->val <<= 1;
	if (!map->res && !(map->res = create_map(map->size)))
		return (-1);
	pos.y = -1;
	while (++pos.y < p->h)
	{
		pos.x = -1;
		cpos.y = p->y + pos.y;
		while (++pos.x < p->w)
			if ((p->val >> ((16 * pos.y) + (16 - p->w) + pos.x)) & 1)
			{
				cpos.x = p->x + (p->w - (pos.x + 1));
				map->res[cpos.x + cpos.y * (map->size + 1)] = 'A' + j;
			}
	}
	return (1);
}

static t_int64		up_left(t_int64 piece_val)
{
	if (piece_val == 0)
		return (piece_val);
	while ((piece_val & 0b1111111111111111) == 0)
		piece_val >>= 16;
	while ((piece_val & MASK) == 0)
		piece_val <<= 1;
	return (piece_val);
}

static t_piece		*reset_piece(t_piece *piece)
{
	if (piece)
	{
		piece->val = piece->ref;
		piece->x = -1;
		piece->y = -1;
	}
	return (piece);
}

static void	optimize_future(t_piece *pieces, const int size)
{
	int		i;
	t_piece	current;

	i = 0;
	current = *pieces;
	while (pieces[++i].val != 0 && pieces[i].ref != current.ref)
		continue ;
	if (pieces[i].val == 0 || pieces[i].ref != current.ref)
		return ;
	pieces[i].x = -1;
	pieces[i].y = current.y;
	pieces[i].val = current.ref;
	if (current.x + (current.w - 1) < size - (current.w - 1))
	{
		pieces[i].y--;
		pieces[i].x = current.x + (current.w - 1) - 1;
		pieces[i].val = current.val >> (current.w - 1);
	}
}

static char	btrk(t_map *map, const int size, const int j)
{
	t_int64	p2;
	t_int64	*frag;

	p2 = map->pieces[j].ref;
	while (++map->pieces[j].y < size - (map->pieces[j].h - 1))
	{
		frag = (t_int64 *)&(map->map[map->pieces[j].y]);
		while (++map->pieces[j].x < size - (map->pieces[j].w - 1))
		{
			if ((*frag & map->pieces[j].val) == 0)
			{
				*frag ^= map->pieces[j].val;
				optimize_future(&map->pieces[j], map->size);
				if (map->pieces[j + 1].val == 0 || btrk(map, size, j + 1))
					return (render_map(map, &map->pieces[j], j));
				reset_piece(&map->pieces[j + 1]);
				*frag ^= map->pieces[j].val;
			}
			map->pieces[j].val >>= 1;
		}
		map->pieces[j].x = -1;
		map->pieces[j].val = p2;
	}
	return (0);
}

int			get_map_size(const int piece_count)
{
	int		ret;
	double	root;

	root = ft_sqrt(piece_count * 4);
	ret = (int)root;
	if ((root - (double)ret) == 0)
		ret--;
	return (ret);
}

char		process(t_map *map)
{
	char	lp;
	int		i;

	i = 0;
	lp = 0;
	map->res = NULL;
	map->size = get_map_size(map->piece_count);
	while (i < 16)
		map->map[i++] = 0;
	while (lp == 0 && map->size < 14)
	{
		i = 0;
		while (map->pieces[i].val != 0)
			reset_piece(&map->pieces[i++]);
		lp = btrk(map, ++map->size, 0);
	}
	if (lp < 0 || map->size >= 14)
		return (1);
	write(1, map->res, (map->size + 1) * map->size);
	free(map->res);
	return (0);
}

t_piece		convert_piece(const char tab[4][4])
{
	t_vec2	pos;
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
	ret.ref = up_left(ret.val);
	ret.val = ret.ref;
	while ((ret.ref & (MASK >> ret.w)) != 0)
		ret.w++;
	while (ret.h < 4 && ret.ref >> (ret.h * 16) != 0)
		ret.h++;
	return (ret);
}

const char	g_pieces[23][4][4] =
{
	{
		"....",
		"....",
		"..##",
		".##."
	},
	{
		"....",
		".##.",
		"..#.",
		"..#."
	},
	{
		"....",
		"....",
		"..##",
		".##."
	},
	{
		"....",
		"....",
		"..##",
		".##."
	},
	{
		"....",
		"....",
		"..##",
		".##."
	},
	{
		"....",
		"....",
		"..##",
		".##."
	},
	{
		"....",
		"....",
		"..##",
		".##."
	},
	{
		"....",
		"....",
		"..##",
		".##."
	},
	{
		"....",
		"....",
		"###.",
		".#.."
	},
	{
		"....",
		"....",
		"..##",
		".##."
	},
	{
		"....",
		"....",
		"..##",
		".##."
	},
	{
		"....",
		"....",
		"..##",
		".##."
	},
	{
		"....",
		"....",
		"..##",
		".##."
	},
	{
		"....",
		".###",
		"..#.",
		"...."
	},
	{
		"....",
		"....",
		"..##",
		".##."
	},
	{
		"....",
		"....",
		"..##",
		".##."
	},
	{
		"..#.",
		"..#.",
		"..#.",
		"..#."
	},
	{
		"....",
		"....",
		"..##",
		".##."
	},
	{
		"....",
		"....",
		"..##",
		".##."
	},
	{
		"....",
		"..#.",
		"..#.",
		"..##"
	},
	{
		"....",
		"....",
		"..##",
		".##."
	},
	{
		"....",
		"....",
		"..##",
		".##."
	},
	{
		"....",
		"....",
		"####",
		"....",
	}
};
const char	g_pieces2[26][4][4] =
{
	{
		"....",
		"....",
		"####",
		"....",
	},
	{
		"....",
		"....",
		"####",
		"....",
	},
	{
		"....",
		"....",
		"####",
		"....",
	},
	{
		"....",
		"....",
		"####",
		"....",
	},
	{
		"....",
		"....",
		"####",
		"....",
	},
	{
		"....",
		"....",
		"####",
		"....",
	},
	{
		"....",
		"....",
		"####",
		"....",
	},
	{
		"....",
		"....",
		"####",
		"....",
	},
	{
		"....",
		"....",
		"####",
		"....",
	},
	{
		"....",
		"....",
		"####",
		"....",
	},
	{
		"....",
		"....",
		"####",
		"....",
	},
	{
		"....",
		"....",
		"####",
		"....",
	},
	{
		"....",
		"....",
		"####",
		"....",
	},
	{
		"....",
		"....",
		"####",
		"....",
	},
	{
		"....",
		"....",
		"####",
		"....",
	},
	{
		"....",
		"....",
		"####",
		"....",
	},
	{
		"....",
		"....",
		"####",
		"....",
	},
	{
		"....",
		"....",
		"####",
		"....",
	},
	{
		"....",
		"....",
		"####",
		"....",
	},
	{
		"....",
		"....",
		"####",
		"....",
	},
	{
		"....",
		"....",
		"####",
		"....",
	},
	{
		"....",
		"....",
		"####",
		"....",
	},
	{
		"....",
		"....",
		"####",
		"....",
	},
	{
		"....",
		"....",
		"####",
		"....",
	},
	{
		"....",
		"....",
		"####",
		"....",
	},
	{
		"....",
		"....",
		"####",
		"....",
	}
};

const char	g_pieces1[12][4][4] =
{
	{
		"....",
		"....",
		"####",
		"...."
	},
	{
		"....",
		"..#.",
		"..##",
		"...#"
	},
	{
		"....",
		"....",
		"#...",
		"###."
	},
	{
		"....",
		".#..",
		".###",
		"...."
	},
	{
		"....",
		".##.",
		"##..",
		"...."
	},
	{
		"#...",
		"###.",
		"....",
		"...."
	},
	{
		"....",
		".###",
		"...#",
		"...."
	},
	{
		"...#",
		"...#",
		"...#",
		"...#"
	},
	{
		"....",
		".##.",
		"..#.",
		"..#."
	},
	{
		"....",
		"....",
		".##.",
		"..##"
	},
	{
		"....",
		"....",
		"#...",
		"###."
	},
	{
		"....",
		"..#.",
		"..##",
		"..#."
	}
};

int			main(void)
{
	int		i;
	t_map	map;

	i = -1;
	map.piece_count = PIECE_COUNT;
	ft_bzero(&map.pieces, sizeof(t_piece) * 27);
	while (++i < PIECE_COUNT)
	{
		map.pieces[i] = convert_piece(g_pieces[i]);
		/*debug_print_piece(&map.pieces[i], 0);*/
	}
	return (process(&map));
}
