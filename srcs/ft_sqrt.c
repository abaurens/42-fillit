/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 19:06:47 by abaurens          #+#    #+#             */
/*   Updated: 2018/12/02 15:39:44 by abaurens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int		power(int v, int p)
{
	long		r;

	r = v;
	if (p == 0)
		return (1);
	if ((r *= power(v, p - 1)) > 2147483647)
		return (0);
	return (r);
}

static int		num_len(int nb)
{
	int			i;

	i = 1;
	while ((nb / 10) > 0)
	{
		i++;
		nb /= 10;
	}
	return (i);
}

long double		ft_sqrt(long double nb)
{
	int			i;
	long double	a;

	i = 0;
	if (nb < 0.0)
		return (-1);
	if (nb == 0.0 || nb == 1.0)
		return (nb);
	if (nb > 7447441.0)
		return (2.0 * ft_sqrt(nb / 4.0));
	a = (float)power(10, num_len((int)nb) / 2.0);
	while (++i < 20)
		a = 0.5 * (a + (nb / a));
	return (a);
}
