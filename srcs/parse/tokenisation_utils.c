/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansard <gansard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 21:32:04 by gregoire          #+#    #+#             */
/*   Updated: 2023/04/24 15:57:19 by gansard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_next_type(t_token *current)
{
	if (!ft_strcmp(current->word, "<"))
		current->next->type = OPEN_FILE;
	else if (!ft_strcmp(current->word, "<<"))
		current->next->type = LIMITOR;
	else if (!ft_strcmp(current->word, ">"))
		current->next->type = EXIT_FILE;
	else if (!ft_strcmp(current->word, ">>"))
		current->next->type = EXIT_FILE_RET;
}

void	set_token_type(t_token *current)
{
	if (!ft_strcmp(current->word, "<"))
		current->type = FILE_IN;
	else if (!ft_strcmp(current->word, "<<"))
		current->type = HERE_DOC;
	else if (!ft_strcmp(current->word, ">"))
		current->type = FILE_OUT;
	else if (!ft_strcmp(current->word, ">>"))
		current->type = FILE_OUT_SUR;
	else if (!current->type)
		current->type = ARG;
	if (current->next && current->type != ARG)
		set_next_type(current);
}

int	ft_set_type(t_token **token)
{
	t_token	*current;

	current = (*token);
	while (current)
	{
		set_token_type(current);
		current = current->next;
	}
	return (1);
}
