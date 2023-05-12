/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansard <gansard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:07:08 by ymehlil           #+#    #+#             */
/*   Updated: 2023/04/30 19:03:32 by gansard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <limits.h>

long long	ft_atoll(const char *str, unsigned long long result, int sign)
{
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if (result > LLONG_MAX / 10 || (result == LLONG_MAX / 10 && *str
				- '0' > LLONG_MAX % 10))
		{
			if (sign == -1)
				return (LLONG_MIN);
			else
				return (LLONG_MAX);
		}
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

int	ft_is_int(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit_with_value(char *str, t_cmds **cmds)
{
	long long	nb;

	nb = ft_atoll(str, 0, 1);
	if (nb >= 0 && nb <= 255)
	{
		g_exit_status = nb;
		ft_free_cmdslst(cmds);
		exit(nb);
	}
	if (nb <= -1 && nb >= -255)
	{
		g_exit_status = 256 + nb;
		ft_free_cmdslst(cmds);
		exit(256 + nb);
	}
	if (nb > 255 || nb < -255)
	{
		if (nb < 0)
			nb = -nb;
		ft_free_cmdslst(cmds);
		g_exit_status = nb % 256;
		exit(nb % 256);
	}
}

int	ft_exit(char **av, t_cmds **cmds)
{
	printf("exit\n");
	if (av[1])
	{
		if (!ft_is_int(av[1]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(av[1], 2);
			ft_putstr_fd("numeric argument required\n", 2);
			ft_free_cmdslst(cmds);
			exit(2);
		}
		if (av[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (1);
		}
		ft_exit_with_value(av[1], cmds);
	}
	ft_exit_with_value("0", cmds);
	return (0);
}
