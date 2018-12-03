/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 16:36:20 by abaurens          #+#    #+#             */
/*   Updated: 2018/12/03 15:51:58 by abaurens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# define ERROR 0
# define SUCCESS 1
# define MAX_PIECE 26
# define MASK 0b1000000000000000100000000000000010000000000000001000000000000000

typedef unsigned short	t_int16;
typedef unsigned long	t_int64;

/*
**	x and y are stored on the same 32 bit int
**	because they only take 16 bits each.
**	so sizeof(t_vec2) = 4
*/
typedef struct	s_vec2
{
	int			x : 16;
	int			y : 16;
}				t_vec2;

/*
**	x, y, w and h are only using 4 bits.
**	Together they use 16 bits of the same 32 bit int
**	so sizeof(t_piece) = (8 + 8 + 4) = 20
*/
typedef struct	s_piece
{
	int			x : 4;
	int			y : 4;
	int			w : 4;
	int			h : 4;
	t_int64		val;
	t_int64		ref;
}				t_piece;

/*
**	piece_count and size are on the same 4 bytes as well
*/
typedef struct	s_map
{
	t_int16		map[16];
	t_piece		pieces[26];
	int			piece_count : 6;
	int			size : 4;
	char		*res;
}				t_map;

/*
**	ft_sqrt.c
*/
long double		ft_sqrt(long double nb);

/*
**	simple_parse.c
*/
int				print_usage(void);
int				parse_file(const char *file, t_map *map);


/*
**	post_parse.c
*/
t_piece			*reset_piece(t_piece *piece);
t_piece			convert_piece(const char tab[4][4]);

/*
**	process.c
*/
char			process(t_map *map);

/*
**	post_process.c
*/
char			render_map(t_map *map, t_piece *p, const int j);

#endif
