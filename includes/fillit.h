/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 16:36:20 by abaurens          #+#    #+#             */
/*   Updated: 2018/12/02 16:18:28 by abaurens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# define PIECE_COUNT 22
# define MASK 0b1000000000000000100000000000000010000000000000001000000000000000

# include <string.h>

typedef unsigned short	t_int16;
typedef unsigned long	t_int64;

typedef struct	s_vec2
{
	int			x;
	int			y;
}				t_vec2;

typedef struct	s_piece
{
	t_int64		val;
	t_int64		ref;
	int			x;
	int			y;
	int			w;
	int			h;
}				t_piece;

typedef struct	s_map
{
	t_int16		map[16];
	t_piece		pieces[27];
	int			piece_count;
	char		*res;
	int			size;
}				t_map;

t_int64			up_left(t_int64 piece_val);
t_piece			*reset_piece(t_piece *piece);
t_piece			convert_piece(const char tab[4][4]);
char			process(t_map *map);
long double		ft_sqrt(long double nb);
char			render_map(t_map *map, t_piece *p, const int j);

#endif
