/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 16:22:44 by ymehlil           #+#    #+#             */
/*   Updated: 2023/02/08 16:10:16 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen1(char *s)
{
	size_t	i;

	i = 0;
	if (!s[i])
		return (0);
	while (s[i])
		i++;
	return (i);
}

void	*ft_memmove1(void *dst, void *src, size_t len)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	i = 0;
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (d > s)
	{
		while (i < len)
		{
			d[len - 1] = s[len - 1];
			len--;
		}
	}
	else
	{
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dst);
}

char	*ft_strdup1(char *s)
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

char	*ft_strchr1(char *s, int c)
{
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (NULL);
}

char	*ft_strjoin1(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	total_len;
	char	*res;

	if (!s1 && !s2)
		return (ft_strdup1(""));
	if (s1 && !s2)
		return (ft_strdup1(s1));
	if (!s1 && s2)
		return (ft_strdup1(s2));
	s1_len = ft_strlen1((char *)s1);
	s2_len = ft_strlen1(s2);
	total_len = s1_len + s2_len + 1;
	res = malloc(sizeof(char) * total_len);
	if (!res)
		return (0);
	ft_memmove1(res, s1, s1_len);
	ft_memmove1(res + s1_len, s2, s2_len);
	res[total_len - 1] = '\0';
	return (free(s1), res);
}
