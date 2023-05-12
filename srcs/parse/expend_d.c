/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:22:01 by gansard           #+#    #+#             */
/*   Updated: 2023/04/25 19:55:02 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_get_value_d(char **str)
{
	char	*tmp;

	if ((*str) && (*str)[0] == '$')
	{
		if (!(*str)[1])
			tmp = ft_strdup("$");
		else if ((*str)[1] && (*str)[1] == '?')
			tmp = ft_itoa(g_exit_status);
		else
			tmp = ft_strdup(white_get_env(*str + 1));
		free(*str);
		(*str) = tmp;
	}
	return (1);
}

int	nb_str_d(char *str, int i, int nw)
{
	while (str[i])
	{
		if (str[i] && str[i] == '$')
		{
			i++;
			nw++;
			if (str[i] == '?')
				i++;
			else
			{
				while (str[i] && ft_darkisalnum(str[i]))
					i++;
			}
		}
		else if (str[i])
		{
			nw++;
			while (str[i] && str[i] != '$')
				i++;
		}
	}
	return (nw);
}

int	ft_create_str_d(char *str, char **part)
{
	int	i;

	i = 0;
	if (str[i] && str[i] == '$')
	{
		if (str[++i] == '?')
			i++;
		else
		{
			while (str[i] && ft_darkisalnum(str[i]))
				i++;
		}
		*part = ft_create_part(str, i);
		if (!(*part))
			return (0);
	}
	else if (str[i])
	{
		while (str[i] && str[i] != '$')
			i++;
		*part = ft_create_part(str, i);
		if (!(*part))
			return (0);
	}
	return (i);
}

char	*ft_expend_d(char *str, int i, int j)
{
	char	**tab;
	char	*res;

	if (!str[0])
		return (str);
	tab = ft_calloc(nb_str_d(str, 0, 0) + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	while (str[i])
	{
		i += ft_create_str_d(&str[i], &tab[++j]);
		if (!i)
			return (ft_free_tab(tab, 0), NULL);
		ft_get_value_d(&tab[j]);
	}
	if (tab[j])
		j++;
	tab[j] = NULL;
	res = ft_join_parts(tab, j);
	if (!res)
		return (NULL);
	free(str);
	if (tab)
		ft_free_tab(tab, 0);
	return (res);
}
