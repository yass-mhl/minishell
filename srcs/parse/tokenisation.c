/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansard <gansard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 08:43:32 by ymehlil           #+#    #+#             */
/*   Updated: 2023/04/25 15:53:03 by gansard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_dir(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == str[0])
		i++;
	if (i >= 2 && str[2])
		return (printf("minishell: syntax error near unexpected token `%c'\n",
				str[2]),
			0);
	else if (str[1] && str[1] != str[0])
		return (printf("minishell: syntax error near unexpected token `%c'\n",
				str[1]),
			0);
	else
		return (1);
}

int	ft_parse_error(char **words)
{
	int	i;

	i = 0;
	while (words[i])
	{
		if (words[i][0] == '>' || words[i][0] == '<')
		{
			if (!ft_check_dir(words[i]))
				return (0);
			if (!words[i + 1])
				return (printf(
						"minishell: syntax error near unexpected \
						token `newline'\n"),
					0);
			if (words[i + 1] && (words[i + 1][0] == '>' || words[i
					+ 1][0] == '<'))
				return (printf("minishell: syntax error near unexpected\
						token `%c'\n",
						words[i + 1][0]),
						0);
		}
		i++;
	}
	return (1);
}

t_token	**ft_create_token(char *str)
{
	char	**tab;
	t_token	**token;
	t_token	*new;
	int		i;

	token = ft_calloc(1, sizeof(token));
	i = 1;
	tab = ft_dark_split_token(str);
	if (!ft_parse_error(tab))
		return (NULL);
	(*token) = ft_lstnew_token(tab[0]);
	if (!(*token))
		return (NULL);
	while (tab[i])
	{
		new = ft_lstnew_token(tab[i]);
		if (!new)
			return (NULL);
		ft_lstadd_back_token(token, new);
		i++;
	}
	if (!ft_set_type(token) || !ft_expend_words(token))
		return (NULL);
	ft_free_tab(tab, 1);
	return (token);
}

int	ft_remove_quote(t_cmds *cmd)
{
	t_token	*cur;
	char	*tmp;

	cur = (*cmd->token);
	while (cur)
	{
		if (cur->type != LIMITOR)
		{
			tmp = cur->word;
			cur->word = ft_strtrim(cur->word, "\"");
			free(tmp);
			if (!cur->word)
				return (0);
		}
		cur = cur->next;
	}
	return (1);
}

int	ft_tokenise(t_cmds **cmds)
{
	t_cmds	*current;

	current = (*cmds);
	while (current)
	{
		current->token = ft_create_token(current->cmd);
		if (!current->token)
			return (0);
		if (!ft_create_args(current))
			return (0);
		if (!ft_remove_quote(current))
			return (0);
		current = current->next;
	}
	return (1);
}
