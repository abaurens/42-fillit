/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 20:06:39 by abaurens          #+#    #+#             */
/*   Updated: 2018/11/24 20:25:00 by abaurens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fillit.h"

int			endian()
{
	int		i;
	char	*p;

	i = 1;
	p = (char *)&i;
	if (FILLIT_DEBUG)
		printf("Current system is %s endian\n", p[0] != 1 ? "big" : "little");
    return (p[0] != 1);
}
