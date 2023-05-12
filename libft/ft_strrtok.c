/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrtok.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:48:05 by ymehlil           #+#    #+#             */
/*   Updated: 2023/04/27 18:16:07 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strrtok(char *str, char sep)
{
	int		i;
	int		index_sep;
	char	*res;
	char	*ptr_sep;

	i = 0;
	ptr_sep = ft_strchr(str, sep);
	if (!ptr_sep)
		return (NULL);
	index_sep = (int)(ptr_sep - str + 1);
	res = malloc(sizeof(char) * (ft_strlen(str) - index_sep + 1));
	while (str[index_sep + i])
	{
		res[i] = str[index_sep + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
