/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:57:18 by ymehlil           #+#    #+#             */
/*   Updated: 2022/11/09 10:57:22 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*res;

	if (size > sizeof(char) * 2147483424 || count > sizeof(char) * 2147483424)
		return (NULL);
	res = malloc(size * count);
	if (!res)
		return (0);
	ft_bzero(res, size * count);
	return (res);
}
