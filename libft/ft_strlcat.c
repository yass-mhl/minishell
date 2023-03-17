/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:39:54 by ymehlil           #+#    #+#             */
/*   Updated: 2022/11/08 11:37:44 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	s_len;
	size_t	d_len;

	s_len = ft_strlen(src);
	i = 0;
	while (dst[i] && i < size)
	{
		i++;
	}
	d_len = i;
	while ((src[i - d_len] && i + 1 < size))
	{
		dst[i] = src[i - d_len];
		i++;
	}
	if (d_len < size)
		dst[i] = '\0';
	return (d_len + s_len);
}
