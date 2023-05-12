/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregoire <gregoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 21:14:36 by gregoire          #+#    #+#             */
/*   Updated: 2023/04/25 11:49:46 by gregoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_get_value(char **str, char *tmp)
{
	if ((*str)[0] == 34)
	{
		tmp = ft_expend_d(ft_strtrim((*str), "\""), 0, -1);
		free(*str);
		(*str) = tmp;
	}
	else if ((*str)[0] == 39)
	{
		tmp = ft_strtrim((*str), "\'");
		free(*str);
		(*str) = tmp;
	}
	else if ((*str) && (*str)[0] == '$')
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

int	ft_check_dollars(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}
// int	ft_check_dollars(char *str)
// {
// 	int	i;

// 	i = 1;
// 	if (str[0] != '$')
// 		return (0);
// 	while (str[i])
// 	{
// 		if (!ft_darkisalnum(str[i++]))
// 			return (0);
// 	}
// 	return (1);
// }

char	*ft_quote_value(char *str)
{
	char	*tmp;
	char	*res;

	if (!str)
		return ("");
	tmp = ft_strjoin("\"", str);
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, "\"");
	free(tmp);
	free(str);
	return (res);
}

char	*ft_join_parts(char **tab, int len_tab)
{
	int		len;
	int		i;
	int		j;
	char	*str;

	i = 0;
	len = 0;
	while (i < len_tab)
		len += ft_strlen(tab[i++]);
	str = ft_calloc((len + 1), sizeof(char));
	i = 0;
	j = 0;
	while (j < len_tab)
	{
		len = ft_strlen(tab[j]) + 1;
		if (len != 1)
		{
			ft_strlcat(str, tab[j], ft_strlen(str) + len);
			i += len;
		}
		j++;
	}
	return (str);
}

int	ft_create_str(char *str, char **part)
{
	int	i;

	i = find_stop_index(str, 0);
	*part = ft_create_part(str, i);
	if (!(*part))
		return (0);
	return (i);
}
