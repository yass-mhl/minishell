/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 18:40:13 by ymehlil           #+#    #+#             */
/*   Updated: 2022/11/08 11:21:18 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	total_len;
	char	*res;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && s2)
		return (ft_strdup(s2));
	s1_len = ft_strlen((char *)s1);
	s2_len = ft_strlen(s2);
	total_len = s1_len + s2_len + 1;
	res = malloc(sizeof(char) * total_len);
	if (!res)
		return (0);
	ft_memmove(res, s1, s1_len);
	ft_memmove(res + s1_len, s2, s2_len);
	res[total_len - 1] = '\0';
	return (res);
}
