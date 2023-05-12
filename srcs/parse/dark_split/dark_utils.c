/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dark_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 21:04:00 by gregoire          #+#    #+#             */
/*   Updated: 2023/04/25 20:39:57 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	update_quotes(char *str, int i, int *d, int *s)
{
	if (str[i] == 34 && (*s % 2 == 0))
		(*d)++;
	if (str[i] == 39 && (*d % 2 == 0))
		(*s)++;
	while (str[i] && (*d % 2 || *s % 2))
	{
		i++;
		if (str[i] == 34 && (*s % 2 == 0))
			(*d)++;
		if (str[i] == 39 && (*d % 2 == 0))
			(*s)++;
	}
	return (i);
}

int	ft_darkisalnum(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

static int	ft_isset(char c, const char *set)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}

char	*dark_strtrim(const char *s1, const char *set)
{
	char	*ret;
	char	*start;
	char	*end;

	if (!s1 || !set)
		return (0);
	start = (char *)s1;
	end = start + ft_strlen(s1);
	if (*start && ft_isset(*start, set))
		++start;
	if (start < end && ft_isset(*(end - 1), set))
		--end;
	ret = ft_substr(start, 0, end - start);
	return (ret);
}
