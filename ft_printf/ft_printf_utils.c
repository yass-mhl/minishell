/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 15:33:44 by ymehlil           #+#    #+#             */
/*   Updated: 2022/11/13 16:57:42 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	len_nb(int nb, int base)
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
		nb /= base;
		i++;
	}
	return (i);
}

int	ft_len_unb(unsigned int nb, int base)
{
	unsigned int	i;

	i = 0;
	if (nb == 0)
		return (i + 1);
	while (nb > 0)
	{
		nb /= base;
		i++;
	}
	return (i);
}

void	ft_ui_putnbr_base_fd(unsigned int nb, char *base, int fd)
{
	unsigned int	len_base;

	len_base = ft_strlen(base);
	if (nb < len_base)
		ft_putchar_fd(base[nb], fd);
	else
	{
		ft_ui_putnbr_base_fd((nb / len_base), base, fd);
		ft_ui_putnbr_base_fd((nb % len_base), base, fd);
	}
}
