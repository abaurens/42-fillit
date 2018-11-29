/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 16:36:20 by abaurens          #+#    #+#             */
/*   Updated: 2018/11/29 04:57:43 by abaurens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# define DEBUG_MODE
# define FILLIT_DEBUG 0
# define PIECE_COUNT 4
# define MASK 0b0000000000000001000000000000000100000000000000010000000000000001

# include <string.h>

typedef unsigned char	t_int8;
typedef unsigned short	t_int16;
typedef unsigned int	t_int32;
typedef unsigned long	t_int64;

typedef struct	s_vec2
{
	int			x;
	int			y;
}				t_vec2;

typedef struct	s_pieces
{
	int			w;
	int			h;
	t_int64		val;
}				t_piece;

typedef struct	s_map
{
	t_int16		map[16];
	t_piece		pieces[26];
	char		*res;
	int			size;
}				t_map;

typedef union	u_test
{
	t_int8		byte[8];
	t_int16		quar[4];
	t_int32		half[2];
	t_int64		all;
}				t_test;

# ifdef DEBUG_MODE
void			ft_putbin(t_int64 val, int len, int padd);
void			debug_print_piece(t_int64 piece, int padd);
void			print_map(t_int16 map[16]);
# endif

char			process(t_map *map);

#endif
