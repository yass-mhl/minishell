/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansard <gansard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:52:21 by ymehlil           #+#    #+#             */
/*   Updated: 2023/04/25 16:06:15 by gansard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_cur(t_env *cur)
{
	free(cur->name);
	free(cur->value);
	free(cur);
}

void	ft_dark_swap(t_env **prev, t_env **cur)
{
	*prev = *cur;
	*cur = (*cur)->next;
}

void	ft_remove_element(char *name, t_env **env)
{
	t_env	*cur;
	t_env	*prev;

	cur = (*env);
	prev = NULL;
	if (!ft_strcmp(cur->name, name))
	{
		(*env) = cur->next;
		ft_free_cur(cur);
		cur = (*env);
	}
	while (cur && ft_strcmp(cur->name, name))
		ft_dark_swap(&prev, &cur);
	if (cur)
	{
		prev->next = cur->next;
		ft_free_cur(cur);
	}
}

void	ft_unset(char **av, t_env **env)
{
	int	i;

	if (!*env)
		return ;
	i = 1;
	while (av[i])
	{
		ft_remove_element(av[i], env);
		i++;
	}
}
