/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dark_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 10:42:59 by ymehlil           #+#    #+#             */
/*   Updated: 2023/03/19 18:30:12 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_nb_word(char *str, char c)
{
	int	nb;
	int	d;
	int	s;
	int i;

	d = 0;
	s = 0;
	nb = 0;
	i = 0;
	while (str[i])
	{
		if(str[i] == 34 && (s % 2 == 0))
			d++;
		if(str[i] == 39 && (d % 2 == 0))
			s++;
		if(str[i] == c && (!(d % 2) && !(s % 2)))
			nb++;
		i++;
	}
	return (nb + 1);
}

char	*ft_dark_strdup(const char *str, char sep)
{
	char	*tab;
	int		len;
	int		i;
	int		s;
	int		d;

	i = 0;
	len = 0;
	s = 0;
	d = 0;
	while (str[len] && (!   (str[len] == sep && (!(d % 2) && !(s % 2)))     ))
	{
		if(str[len] == 34 && (s % 2 == 0))
			d++;
		if(str[len] == 39 && (d % 2 == 0))
			s++;
		len++;
	}
	tab = (char *)malloc(sizeof(char *) * (len + 1));
	if (!tab)
		return (NULL);
	s = 0;
	d = 0;
	while (str[i] && (!(str[i] == sep && (!(d % 2) && !(s % 2)))))
	{
		if(str[i] == 34 && (s % 2 == 0))
			d++;
		if(str[i] == 39 && (d % 2 == 0))
			s++;
		tab[i] = str[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

char	**ft_dark_split(char *str, char sep)
{
	int 	i;
	int		j;
	char	**tab;
	int 	d;
	int 	s;

	i = 0;
	j = 0;
	d = 0;
	s = 0;
	tab = malloc((sizeof(char *) * ft_nb_word(str, sep)) + 1);
	tab[0] = ft_dark_strdup(str, '|');
	if(!tab[0])
		return (ft_error(tab, j), NULL);
	j++;
	while(str[i])
	{
		
		if(str[i] == 34 && (s % 2 == 0))
			d++;
		if(str[i] == 39 && (d % 2 == 0))
			s++;
		if(str[i] == sep && (!(d % 2) && !(s % 2)))
		{
			tab[j] = ft_dark_strdup(&str[i + 1], sep);
			if(!tab[j])
				return (ft_error(tab, j), NULL);
			j++;
		}
		i++;
	}
	tab[j] = NULL;

	return (tab);
}
