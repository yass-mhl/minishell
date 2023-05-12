/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansard <gansard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:19:53 by ymehlil           #+#    #+#             */
/*   Updated: 2023/04/24 15:28:02 by gansard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*ft_add_env(char *line)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = ft_strtok(line, '=');
	new->value = ft_strrtok(line, '=');
	new->next = NULL;
	return (new);
}

t_env	**get_adress(void)
{
	static t_env	*new = NULL;

	return (&new);
}

char	*create_env_str_entry(t_env *tmp)
{
	size_t	name_len;
	size_t	value_len;
	int		len;
	char	*str;

	name_len = strlen(tmp->name);
	value_len = strlen(tmp->value);
	len = name_len + value_len + 2;
	str = malloc(len);
	if (!str)
		return (NULL);
	strcpy(str, tmp->name);
	strcat(str, "=");
	strcat(str, tmp->value);
	return (str);
}

char	**env_to_str(t_env *env_list)
{
	int		len;
	int		i;
	t_env	*tmp;
	char	**env_str;
	char	*str;

	len = get_env_list_length(env_list);
	env_str = allocate_env_str_array(len);
	if (!env_str)
		return (NULL);
	i = 0;
	tmp = env_list;
	while (tmp)
	{
		str = create_env_str_entry(tmp);
		if (!str)
			return (NULL);
		env_str[i++] = str;
		tmp = tmp->next;
	}
	env_str[i] = NULL;
	return (env_str);
}

t_env	*ft_init_env(char **env)
{
	t_env	**env_list;
	t_env	*first;
	t_env	*tmp;
	int		i;

	env_list = get_adress();
	if (!env || !*env)
		return (NULL);
	*env_list = ft_add_env(env[0]);
	first = *env_list;
	if (!*env_list)
		return (NULL);
	tmp = first;
	i = 1;
	while (env[i])
	{
		first->next = ft_add_env(env[i]);
		first = first->next;
		i++;
	}
	return (tmp);
}
