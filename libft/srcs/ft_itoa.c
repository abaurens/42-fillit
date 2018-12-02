/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 00:18:24 by abaurens          #+#    #+#             */
/*   Updated: 2018/11/08 13:12:17 by abaurens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	numlen(int n)
{
	size_t		i;

	i = 1;
	if (n < 0)
		i++;
	while (n / 10 != 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char			*ft_itoa(int n)
{
	size_t		i;
	long		nb;
	char		*ret;

	nb = n;
	i = numlen(n);
	if (!(ret = malloc(i + 1)))
		return (NULL);
	ret[i--] = 0;
	*ret = (n == 0 ? '0' : '-');
	if (nb < 0)
		nb = -nb;
	while (nb != 0)
	{
		ret[i--] = (nb % 10) + '0';
		nb /= 10;
	}
	return (ret);
}
