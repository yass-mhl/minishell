/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:31:52 by ymehlil           #+#    #+#             */
/*   Updated: 2023/04/25 20:02:40 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_n(char **str)
{
	int	i;
	int	y;
	int	index_word;

	i = 0;
	index_word = 0;
	while (str[i] && ft_strlen(str[i]) >= 2)
	{
		y = 0;
		if (str[i][y] == '-' && str[i][y + 1] == 'n')
		{
			y++;
			while (str[i][y] == 'n')
				y++;
			if (str[i][y] == '\0')
				index_word++;
		}
		else
			break ;
		i++;
	}
	return (index_word);
}

void	ft_echo(char **args)
{
	int	i;
	int	bool;

	args++;
	i = check_n(args);
	bool = 0;
	if (i >= 1)
		bool = 1;
	if (!args || !*args)
	{
		ft_printf("\n");
		return ;
	}
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (!bool)
		ft_printf("\n");
	return ;
}
