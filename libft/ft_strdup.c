/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 17:00:48 by ymehlil           #+#    #+#             */
/*   Updated: 2022/11/07 17:32:09 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*tab;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (s[len])
		len++;
	tab = (char *)malloc(sizeof(*s) * (len + 1));
	if (!tab)
		return (NULL);
	while (s[i])
	{
		tab[i] = s[i];
		i++;
	}
	tab[i] = 0;
	return (tab);
}
