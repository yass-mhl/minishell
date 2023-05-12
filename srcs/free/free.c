/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregoire <gregoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:37:59 by gansard           #+#    #+#             */
/*   Updated: 2023/04/13 10:52:18 by gregoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_token(t_token *token)
{
	if (token)
	{
		if (token->word)
		{
			free(token->word);
		}
		free(token);
	}
}

void	ft_free_tokenlst(t_token **token)
{
	t_token	*cur;
	t_token	*tmp;

	if (token)
	{
		cur = (*token);
		while (cur)
		{
			tmp = cur->next;
			ft_free_token(cur);
			cur = tmp;
		}
		free(token);
	}
}

void	ft_free_cmd(t_cmds *cmd)
{
	if (cmd)
	{
		if (cmd->cmd)
			free(cmd->cmd);
		if (cmd->token)
			ft_free_tokenlst(cmd->token);
		if (cmd->args)
			ft_free_tab(cmd->args, 0);
		free(cmd);
	}
}

void	ft_free_cmdslst(t_cmds **cmds)
{
	t_cmds	*cur;
	t_cmds	*tmp;

	if (cmds)
	{
		cur = (*cmds);
		while (cur)
		{
			tmp = cur->next;
			ft_free_cmd(cur);
			cur = tmp;
		}
		free(cmds);
	}
}

void	ft_free_env(t_env **env)
{
	t_env	*cur;
	t_env	*tmp;

	cur = (*env);
	while (cur)
	{
		if (cur->name)
			free(cur->name);
		if (cur->value)
			free(cur->value);
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
}
