/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:40:13 by gansard           #+#    #+#             */
/*   Updated: 2023/04/25 20:18:15 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	process_special_chars(char *str, int *i)
{
	int		nw;
	char	c;

	nw = 0;
	if (str[*i] == 34 || str[*i] == 39)
	{
		c = str[*i];
		while (str[++(*i)] != c)
			;
		(*i)++;
	}
	else if (str[*i] && str[*i] == '$')
	{
		(*i)++;
		while (str[*i] && ft_darkisalnum(str[*i]) && str[*i] != 34
			&& str[*i] != 39)
			(*i)++;
	}
	else if (str[*i])
	{
		while (str[*i] && str[*i] != '$' && str[*i] != 34 && str[*i] != 39)
			(*i)++;
	}
	nw++;
	return (nw);
}

int	nb_str(char *str)
{
	int	i;
	int	nw;

	i = 0;
	nw = 0;
	while (str[i])
	{
		nw += process_special_chars(str, &i);
	}
	return (nw);
}

char	*ft_create_part(char *str, int end)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = ft_calloc((end - i) + 1, sizeof(char));
	if (!res)
		return (NULL);
	while (i < end)
		res[j++] = str[i++];
	return (res);
}

int	find_stop_index(char *str, int i)
{
	char	c;

	if (str[i] == 34 || str[i] == 39)
	{
		c = str[i++];
		while (str[i] && str[i] != c)
			i++;
		return (++i);
	}
	else if (str[i] && str[i] == '$')
	{
		i++;
		if (str[i] == '?')
			return (++i);
		while (str[i] && ft_darkisalnum(str[i]) && str[i] != 34 && str[i] != 39)
			i++;
		return (i);
	}
	else if (str[i])
	{
		while (str[i] && str[i] != '$' && str[i] != 34 && str[i] != 39)
			i++;
		return (i);
	}
	return (i);
}

char	*ft_expend(char *str, enum type type, int i, int j)
{
	char	**tab;
	char	*res;
	char	*tmp;

	tmp = NULL;
	tab = ft_calloc(nb_str(str) + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	while (str[i])
	{
		i += ft_create_str(&str[i], &tab[++j]);
		if (!i)
			return (ft_free_tab(tab, 0), NULL);
		ft_get_value(&tab[j], tmp);
	}
	if (tab[j])
		j++;
	res = ft_join_parts(tab, j);
	if (!res)
		return (NULL);
	if (!ft_check_dollars(str) && type != FILE_IN && type != EXIT_FILE)
		res = ft_quote_value(res);
	ft_free_tab(tab, 0);
	return (res);
}
