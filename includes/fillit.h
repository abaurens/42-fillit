/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 16:36:20 by abaurens          #+#    #+#             */
/*   Updated: 2018/12/03 01:29:27 by abaurens         ###   ########.fr       */
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
