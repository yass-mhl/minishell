/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 08:43:32 by ymehlil           #+#    #+#             */
/*   Updated: 2023/03/19 18:38:24 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_set_type(t_token **token)
{
	t_token	*current;

	current = (*token);
	while (current)
	{
		if (ft_strcmp(current->word, "<"))
		{
			current->type = FILE_IN;
			current->next->type =  OPEN_FILE;
		}
		else if (ft_strcmp(current->word, "<<"))
		{
			current->type = HERE_DOC;
			current->next->type =  LIMITOR;
		}
		else if (ft_strcmp(current->word, ">"))
		{
			current->type = EXIT_FILE;
			current->next->type = EXIT_FILE;
		}	
		else if (ft_strcmp(current->word, ">>"))
		{
			current->type = FILE_OUT_SUR;
			current->next->type =  EXIT_FILE_RET;
		}
		else 
			current->type = ARG;
	}
	return (1);
}

t_token	**ft_create_token(char *str)
{
	char	**tab;
	t_token	**token;
	t_token	*new;
	int		i;

	token = malloc(sizeof(token));
	i = 0;
	tab = ft_dark_split_token(str);
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
	if (!ft_set_type(token))
		return (NULL);
	return (token);
}

void	ft_tokenise(t_cmds **cmds)
{
	t_cmds	*current;

	current = (*cmds);
	while (current)
	{
		current->token = ft_create_token(current->cmd);
		current = current->next;
	}
}
