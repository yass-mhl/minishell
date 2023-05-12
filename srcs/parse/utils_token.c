/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansard <gansard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 09:13:33 by ymehlil           #+#    #+#             */
/*   Updated: 2023/04/21 14:45:17 by gansard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_expend_words(t_token **token)
{
	t_token	*current;
	char	*tmp;

	current = (*token);
	while (current)
	{
		if (current->type != LIMITOR)
		{
			tmp = current->word;
			current->word = ft_expend(current->word, current->type, 0, -1);
			free(tmp);
		}
		current = current->next;
	}
	return (1);
}

int	ft_check_sep(char *str, char straight, char rev)
{
	int	i;

	i = 0;
	if (str[i + 1] && str[i + 1] == straight)
	{
		if (str[i + 2] && (str[i + 2] != rev && str[i + 2] != straight) && str[i
				+ 2])
			return (2);
		return (0);
	}
	else if (str[i + 1] && str[i + 1] != rev)
		return (1);
	return (0);
}

t_token	*ft_lstlast_token(t_token *token)
{
	if (!token)
		return (0);
	while (token->next)
		token = token->next;
	return (token);
}

t_token	*ft_lstnew_token(char *word)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->word = ft_strdup(word);
	new->type = NONE;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back_token(t_token **token, t_token *new)
{
	t_token	*temp;

	temp = *token;
	temp = ft_lstlast_token(temp);
	if (!temp)
		*token = new;
	else
		temp->next = new;
}
