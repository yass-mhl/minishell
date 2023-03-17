/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:41:16 by ymehlil           #+#    #+#             */
/*   Updated: 2022/11/07 13:41:27 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (*src && i + 1 < dstsize)
	{
		*dst++ = *src++;
		++i;
	}
	if (i < dstsize)
		*dst = 0;
	while (*src++)
		++i;
	return (i);
}
