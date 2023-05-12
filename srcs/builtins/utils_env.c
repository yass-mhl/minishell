/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansard <gansard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:54:33 by ymehlil           #+#    #+#             */
/*   Updated: 2023/04/30 20:36:16 by gansard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*ft_get_env(char *name)
{
	t_env	**env_list;
	t_env	*cur;

	env_list = get_adress();
	cur = *env_list;
	while (cur)
	{
		if (!ft_strcmp(cur->name, name))
			return (free(name), cur);
		cur = cur->next;
	}
	return (free(name), NULL);
}

char	*white_get_env(char *name)
{
	t_env	**env_list;
	t_env	*cur;

	env_list = get_adress();
	cur = *env_list;
	while (cur)
	{
		if (!ft_strcmp(cur->name, name))
			return (cur->value);
		cur = cur->next;
	}
	return (NULL);
}

t_env	*create_new_env_node(char *str)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	if (!ft_strchr(str, '='))
	{
		new->name = ft_strdup(str);
		new->value = ft_strdup("");
	}
	else
	{
		new->name = ft_strtok(str, '=');
		new->value = ft_strrtok(str, '=');
	}
	new->next = NULL;
	return (new);
}

void	ft_add_back_env(char *str, t_env **env_list)
{
	t_env	*new;
	t_env	*tmp;

	if (!*env_list)
		*env_list = ft_add_env(str);
	else
	{
		new = create_new_env_node(str);
		if (!new)
			return ;
		tmp = *env_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

//void	ft_add_back_env(char *str, t_env **env_list)
//{
//	t_env	*new;
//	t_env	*tmp;

//	if (!*env_list)
//		*env_list = ft_add_env(str);
//	else
//	{
//		new = malloc(sizeof(t_env));
//		if (!new)
//			return ;
//		if (!ft_strchr(str, '='))
//		{
//			new->name = ft_strdup(str);
//			new->value = ft_strdup("");
//			new->next = NULL;
//		}
//		else
//		{
//			new->name = ft_strtok(str, '=');
//			new->value = ft_strrtok(str, '=');
//			new->next = NULL;
//		}
//		tmp = *env_list;
//		while (tmp->next)
//			tmp = tmp->next;
//		tmp->next = new;
//	}
//}
