/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dark_split_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansard <gansard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 10:21:35 by gansard           #+#    #+#             */
/*   Updated: 2023/04/03 18:01:08 by gansard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

//#define IS_QUOTE(c) (c == 34 || c == 39)
//#define IS_ARROW(c) (c == '<' || c == '>')
//#define OPEN_QUOTE(c, quote) (c && c != quote)
//#define IS_LETTER(c) (c && c != '<' && c != '>' && c != 34 && c != 39
//		&& c != ' ')

// int	nb_words(char *str)
// {
// 	int	i;
// 	int	nw;
// 	int	d;
// 	int	s;

// 	i = 0;
// 	nw = 0;
// 	d = 0;
// 	s = 0;
// 	while (str[i])
// 	{
// 		while (str[i] && str[i] == ' ')
// 			i++;
// 		if (str[i] && str[i] != '<' && str[i] != '>' && (!(d % 2) && !(s % 2)))
// 			nw++;
// 		while (str[i] && str[i] != ' ' && str[i] != '>' && str[i] != '<')
// 		{
// 			if (str[i] == 34 && (s % 2 == 0))
// 				d++;
// 			if (str[i] == 39 && (d % 2 == 0))
// 				s++;
// 			while (str[i] && (d % 2 || s % 2))
// 			{
// 				i++;
// 				if (str[i] == 34 && (s % 2 == 0))
// 					d++;
// 				if (str[i] == 39 && (d % 2 == 0))
// 					s++;
// 			}
// 			i++;
// 		}
// 		if (str[i] == '<' || str[i] == '>')
// 			nw++;
// 		while (str[i] == '<' || str[i] == '>')
// 			i++;
// 	}
// 	return (nw);
// }

int	skip_spaces(char *str, int i)
{
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
}

int	nb_words(char *str)
{
	int	i;
	int	nw;
	int	d;
	int	s;

	i = 0;
	nw = 0;
	d = 0;
	s = 0;
	while (str[i])
	{
		i = skip_spaces(str, i);
		if (str[i] && str[i] != '<' && str[i] != '>' && (!(d % 2) && !(s % 2)))
			nw++;
		while (str[i] && str[i] != ' ' && str[i] != '>' && str[i] != '<')
		{
			i = update_quotes(str, i, &d, &s);
			i++;
		}
		if (str[i] == '<' || str[i] == '>')
			nw++;
		while (str[i] == '<' || str[i] == '>')
			i++;
	}
	return (nw);
}

//int ft_create_dirword(char *str, char **tab, int i)
//{
//	int len;
//	int	j;

//	len = 0;
//	j = 0;
//	while (str[len] && (str[len] == '<' || str[len] == '>'))
//		len++;
//	tab[i] = ft_calloc(len + 1, sizeof(char));
//	while (j < len)
//	{
//		tab[i][j] = str[j];
//		j++;
//	}
//	tab[i][j] = '\0';
//	return (len);
//}

//int ft_create_defword(char *str, char **tab, int i)
//{
//	int len;
//	int j;
//	int d;
//	int s;

//	len = 0;
//	j = 0;
//	d = 0;
//	s = 0;
//	while (str[len] && str[len] != ' ' && str[len] != '>'
//		&& str[len] != '<')
//	{
//		if (str[len] == 34 && (s % 2 == 0))
//			d++;
//		if (str[len] == 39 && (d % 2 == 0))
//			s++;
//		while (str[len] && (d % 2 || s % 2))
//		{
//			len++;
//			if (str[len] == 34 && (s % 2 == 0))
//				d++;
//			if (str[len] == 39 && (d % 2 == 0))
//				s++;
//		}
//		len++;
//	}
//	tab[i] = ft_calloc(len + 1, sizeof(char));
//	while (j < len)
//	{
//		tab[i][j] = str[j];
//		j++;
//	}
//	tab[i][j] = '\0';

//	return (len);
//}

//int	ft_create_word(char *str, char **tab, int i)
//{
//	int	len;
//	int	j;
//	int	d;
//	int	s;

//	j = 0;
//	len = 0;
//	d = 0;
//	s = 0;
//	if (*str == '<' || *str == '>')
//	{
//		while (str[len] && (str[len] == '<' || str[len] == '>'))
//			len++;
//		tab[i] = ft_calloc(len + 1, sizeof(char));
//		while (j < len)
//		{
//			tab[i][j] = str[j];
//			j++;
//		}
//		tab[i][j] = '\0';
//	}
//	else
//	{
//		while (str[len] && str[len] != ' ' && str[len] != '>'
//			&& str[len] != '<')
//		{
//			if (str[len] == 34 && (s % 2 == 0))
//				d++;
//			if (str[len] == 39 && (d % 2 == 0))
//				s++;
//			while (str[len] && (d % 2 || s % 2))
//			{
//				len++;
//				if (str[len] == 34 && (s % 2 == 0))
//					d++;
//				if (str[len] == 39 && (d % 2 == 0))
//					s++;
//			}
//			len++;
//		}
//		tab[i] = ft_calloc(len + 1, sizeof(char));
//		while (j < len)
//		{
//			tab[i][j] = str[j];
//			j++;
//		}
//		tab[i][j] = '\0';
//	}
//	return (len);
//}

int	calculate_len_t(char *str, int d, int s)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != ' ' && str[len] != '>' && str[len] != '<')
	{
		if (str[len] == 34 && (s % 2 == 0))
			(d)++;
		if (str[len] == 39 && (d % 2 == 0))
			(s)++;
		while (str[len] && ((d % 2) || (s % 2)))
		{
			len++;
			if (str[len] == 34 && (s % 2 == 0))
				(d)++;
			if (str[len] == 39 && (d % 2 == 0))
				(s)++;
		}
		len++;
	}
	return (len);
}

int	ft_create_word(char *str, char **tab, int i)
{
	int	len;
	int	j;
	int	d;
	int	s;

	d = 0;
	s = 0;
	j = 0;
	if (*str == '<' || *str == '>')
	{
		while (str[j] && (str[j] == '<' || str[j] == '>'))
			j++;
		len = j;
	}
	else
		len = calculate_len_t(str, d, s);
	tab[i] = ft_calloc(len + 1, sizeof(char));
	j = 0;
	while (j < len)
	{
		tab[i][j] = str[j];
		j++;
	}
	tab[i][j] = '\0';
	return (len);
}

char	**ft_dark_split_token(char *str)
{
	char	**tab;
	int		i;
	int		j;
	int		d;
	int		s;

	i = 0;
	j = 0;
	d = 0;
	s = 0;
	tab = ft_calloc(nb_words(str) + 1, sizeof(char *));
	while (str[i])
	{
		if (str[i] == 34 && (s % 2 == 0))
			d++;
		if (str[i] == 39 && (d % 2 == 0))
			s++;
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i])
			i += ft_create_word(&str[i], tab, j++);
	}
	tab[j] = NULL;
	return (tab);
}
