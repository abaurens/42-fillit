/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 16:36:20 by abaurens          #+#    #+#             */
/*   Updated: 2018/11/28 21:43:53 by abaurens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# define FILLIT_DEBUG 0
# define MAX_SQUARE 16
# define MASK 0b0000000000000001000000000000000100000000000000010000000000000001

# define PIECE_HEIGHT 4
# define PIECE_WIDTH 3

# include <string.h>

typedef unsigned char	t_int8;
typedef unsigned short	t_int16;
typedef unsigned int	t_int32;
typedef unsigned long	t_int64;

typedef struct	s_map
{
	t_int16		map[16 + 3];
	t_int64		pieces[26];
	int			best;
}				t_map;

typedef union	u_test
{
	t_int8		byte[8];
	t_int16		quar[4];
	t_int32		half[2];
	t_int64		all;
}				t_test;

int				min(int a, int b);
int				max(int a, int b);
int				endian();
void			ft_putbin(t_int64 val, int len, int padd);
void			*endianless_map_fragment(void *dest, const void *src);

#endif
