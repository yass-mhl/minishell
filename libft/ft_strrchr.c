/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:38:36 by ymehlil           #+#    #+#             */
/*   Updated: 2022/11/07 17:38:40 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*res;
	int		i;

	res = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			res = ((char *)(s + i));
		i++;
	}
	if (s[i] == (char)c)
		res = (char *)(s + i);
	return (res);
}
