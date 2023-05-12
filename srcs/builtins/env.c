/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:52:54 by ymehlil           #+#    #+#             */
/*   Updated: 2023/04/27 19:27:29 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_args(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	if (i > 1)
		return (0);
	return (1);
}

void	ft_env(char **av)
{
	t_env	**env_list;
	t_env	*cur;

	env_list = get_adress();
	if (!env_list)
		return ;
	if (!check_args(av))
	{
		printf("env: too many arguments\n");
		return ;
	}
	cur = *env_list;
	while (cur)
	{
		if (cur->value[0])
		{
			printf("%s", cur->name);
			printf("=");
			printf("%s\n", cur->value);
		}
		cur = cur->next;
	}
}
