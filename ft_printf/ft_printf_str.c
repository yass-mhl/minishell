/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 14:37:34 by ymehlil           #+#    #+#             */
/*   Updated: 2022/11/16 21:56:48 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_percent(void)
{
	ft_putchar_fd('%', 1);
	return (1);
}

int	ft_print_char(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	ft_print_str(char *str)
{
	int		count;

	count = 0;
	if (str)
	{
		ft_putstr_fd(str, 1);
		count = ft_strlen(str);
	}
	else
	{
		ft_putstr_fd("(null)", 1);
		count = ft_strlen("(null)");
	}
	return (count);
}
