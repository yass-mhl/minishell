/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansard <gansard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 21:29:38 by gregoire          #+#    #+#             */
/*   Updated: 2023/04/03 16:12:35 by gansard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_env_list_length(t_env *env_list)
{
	int		len;
	t_env	*tmp;

	len = 0;
	tmp = env_list;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

char	**allocate_env_str_array(int len)
{
	char	**env_str;

	env_str = malloc(sizeof(char *) * (len + 1));
	if (!env_str)
		return (NULL);
	return (env_str);
}
