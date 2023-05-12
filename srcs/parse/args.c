/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 20:54:30 by gregoire          #+#    #+#             */
/*   Updated: 2023/04/25 20:12:39 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_count_space(char *str)
{
	int	i;
	int	nw;

	i = 0;
	nw = 0;
	while (str[i])
	{
		if (str[i++] == ' ')
			nw++;
	}
	return (nw + 1);
}

int	ft_count_args(t_cmds *cmd)
{
	t_token	*cur;
	int		nb_words;

	cur = (*cmd->token);
	nb_words = 0;
	while (cur)
	{
		if (cur->word[0] != 34)
			nb_words += ft_count_space(cur->word);
		else
			nb_words++;
		cur = cur->next;
	}
	return (nb_words);
}

int	ft_split_word(char *str, char **args, int index)
{
	int		i;
	char	**tab;

	i = 0;
	tab = ft_split(str, ' ');
	if (!tab)
		return (-1);
	while (tab[i])
	{
		args[index] = ft_strdup(tab[i]);
		if (!args[index])
			return (-1);
		index++;
		i++;
	}
	ft_free_tab(tab, 0);
	return (i);
}

int	ft_create_args(t_cmds *cmd)
{
	t_token	*cur;
	int		i;

	i = 0;
	cur = (*cmd->token);
	cmd->args = ft_calloc(ft_count_args(cmd) + 1, sizeof(char *));
	while (cur)
	{
		if (cur->word[0] != 34 && cur->type == ARG)
		{
			i += ft_split_word(cur->word, cmd->args, i);
			if (i == -1)
				return (0);
		}
		else if (cur->type == ARG)
		{
			cmd->args[i] = dark_strtrim(cur->word, "\"");
			if (!cmd->args[i])
				return (0);
			i++;
		}
		cur = cur->next;
	}
	cmd->args[i] = NULL;
	return (1);
}
