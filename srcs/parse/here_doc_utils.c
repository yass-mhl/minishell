/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansard <gansard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 21:23:41 by gregoire          #+#    #+#             */
/*   Updated: 2023/04/21 14:40:45 by gansard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_get_value_hd(char **str)
{
	char	*tmp;

	if ((*str)[0] == 34)
	{
		tmp = ft_strtrim((*str), "\"");
		free(*str);
		(*str) = tmp;
	}
	else if ((*str)[0] == 39)
	{
		tmp = ft_strtrim((*str), "\'");
		free(*str);
		(*str) = tmp;
	}
	return (1);
}

int	next_word_index(char *str, int *i)
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
	else if (str[*i])
	{
		while (str[*i] && str[*i] != 34 && str[*i] != 39)
			(*i)++;
	}
	nw++;
	return (nw);
}

int	nb_str_hd(char *str)
{
	int	i;
	int	nw;

	i = 0;
	nw = 0;
	while (str[i])
		nw += next_word_index(str, &i);
	return (nw);
}

char	*ft_create_part_hd(char *str, int end)
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

int	find_stop_index_hd(char *str)
{
	int		i;
	char	c;

	i = 0;
	if (str[i] == 34 || str[i] == 39)
	{
		c = str[i++];
		while (str[i] && str[i] != c)
			i++;
		return (++i);
	}
	else if (str[i])
	{
		while (str[i] && str[i] != 34 && str[i] != 39)
			i++;
		return (i);
	}
	return (i);
}
