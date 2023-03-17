/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:37:31 by ymehlil           #+#    #+#             */
/*   Updated: 2022/11/08 10:35:31 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	len_nb(long nb)
{
	int	i;

	i = 0;
	if (nb < 0)
	{
		nb *= -1;
		i++;
	}
	if (nb == 0)
		return (i + 1);
	while (nb > 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		i;
	long	nb;

	nb = n;
	i = len_nb(n);
	res = (char *) malloc(sizeof(char) * i + 1);
	if (!res)
		return (NULL);
	res[i] = 0;
	i--;
	if (nb < 0)
	{
		res[0] = '-';
		nb *= -1;
	}
	if (n == 0)
		res[0] = 0 + '0';
	while (nb > 0)
	{
		res[i--] = (nb % 10) + '0';
		nb /= 10;
	}
	return (res);
}
