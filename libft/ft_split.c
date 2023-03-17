/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:57:59 by ymehlil           #+#    #+#             */
/*   Updated: 2022/11/09 12:30:50 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nombre_lettre(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		++i;
	return (i);
}

static size_t	nb_word(const char *s, char c)
{
	size_t	word;

	word = 0;
	while (*s)
	{
		if (*s != c)
		{
			word++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (word);
}

char	**ft_error(char **split, int word)
{
	while (word >= 0)
	{
		free(split[word]);
		word--;
	}
	free(split);
	return (NULL);
}

char	**ft_split(const char *str, char c)
{
	char	**split;
	int		word;
	int		letter;

	if (str == NULL)
		return (NULL);
	split = malloc(sizeof(char *) * (nb_word(str, c) + 1));
	if (split == NULL)
		return (NULL);
	word = 0;
	while (nb_word(str, c))
	{
		while (*str && *str == c)
			str++;
		split[word] = malloc(sizeof(char) * nombre_lettre(str, c) + 1);
		if (!split[word])
			return (ft_error(split, word));
		letter = 0;
		while (*str && *str != c)
			split[word][letter++] = *str++;
		split[word++][letter] = '\0';
	}
	split[word] = 0;
	return (split);
}
