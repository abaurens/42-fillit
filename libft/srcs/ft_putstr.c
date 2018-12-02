/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 00:41:07 by abaurens          #+#    #+#             */
/*   Updated: 2018/11/13 14:19:28 by abaurens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void		ft_putstr(char const *s)
{
	size_t	l;

	l = 0;
	while (s && s[l])
		l++;
	if (s && l)
		write(1, s, l);
}
