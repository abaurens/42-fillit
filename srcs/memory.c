/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 19:56:24 by abaurens          #+#    #+#             */
/*   Updated: 2018/11/24 20:45:16 by abaurens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "fillit.h"

void				*endianless_map_fragment(void *dest, const void *src)
{
	int				i;
	unsigned short	*d;
	unsigned short	*s;

	i = -1;
	d = (unsigned short *)dest;
	s = (unsigned short *)src;
	if (endian())
		return (memcpy(dest, src, 8));
	while (++i < 4)
	{
		if (FILLIT_DEBUG)
		{
			ft_putbin(*((t_int64 *)dest), 64, 16);
			write(1, "\n", 1);
		}
		d[4 - i - 1] = s[i];
	}
	return (dest);
}
