/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:44:47 by ymehlil           #+#    #+#             */
/*   Updated: 2023/04/27 19:28:49 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_export(char **av)
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
			printf("declare -x ");
			printf("%s", cur->name);
			printf("=");
			printf("\"%s\"\n", cur->value);
		}
		else
			printf("declare -x %s\n", cur->name);
		cur = cur->next;
	}
}
