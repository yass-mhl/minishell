/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 15:24:59 by ymehlil           #+#    #+#             */
/*   Updated: 2023/01/25 15:20:26 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_parse(char s, va_list arg)
{
	int	count;

	count = 0;
	if (s == '%')
		count = ft_print_percent();
	else if (s == 'c')
		count = ft_print_char((char)va_arg(arg, int));
	else if (s == 's')
		count = ft_print_str((char *)va_arg(arg, char *));
	else if (s == 'd' || s == 'i')
		count = ft_print_i(arg);
	else if (s == 'u')
		count = ft_print_u(arg);
	else if (s == 'x' || s == 'X')
		count = ft_print_x(s, arg);
	else if (s == 'p')
		count = ft_print_ptr((size_t)va_arg(arg, unsigned long long));
	return (count);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		count;
	va_list	arg;

	i = 0;
	count = 0;
	va_start(arg, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			count += ft_parse(str[i + 1], arg);
			i++;
		}
		else
		{
			ft_putchar_fd(str[i], 1);
			count++;
		}	
		i++;
	}
	va_end(arg);
	return (count);
}
