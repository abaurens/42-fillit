/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 14:49:57 by abaurens          #+#    #+#             */
/*   Updated: 2018/12/02 16:18:17 by abaurens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "fillit.h"
#include "libft.h"

static void		optimize_future(t_piece *pieces, const int size)
{
	int			i;
	t_piece		current;

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

static char		btrk(t_map *map, const int size, const int j)
{
	t_int64		p2;
	t_int64		*frag;

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

int				get_map_size(const int piece_count)
{
	int			ret;
	double		root;

	root = ft_sqrt(piece_count * 4);
	ret = (int)root;
	if ((root - (double)ret) == 0)
		ret--;
	return (ret);
}

char			process(t_map *map)
{
	char		lp;
	int			i;

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

const char		g_pieces[23][4][4] =
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
const char		g_pieces2[26][4][4] =
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

const char		g_pieces1[12][4][4] =
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

int				main(void)
{
	int			i;
	t_map		map;

	i = -1;
	map.piece_count = PIECE_COUNT;
	ft_bzero(&map.pieces, sizeof(t_piece) * 27);
	while (++i < PIECE_COUNT)
	{
		map.pieces[i] = convert_piece(g_pieces[i]);
	}
	return (process(&map));
}
