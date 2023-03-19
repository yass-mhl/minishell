/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 10:44:53 by ymehlil           #+#    #+#             */
/*   Updated: 2023/03/19 18:27:51 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_check(char *str)
{
	int	i;
	int	d;
	int s;

	i = 0;
	s = 0;
	d = 0;

	while(str[i])
	{
		if(str[i] == '|')
		{
			if((str[i + 1] && str[i + 1] == '|') || i == 0)
				return (0);
		}
		if(str[i] == 34 && (s % 2 == 0))
			d++;
		if(str[i] == 39 && (d % 2 == 0))
			s++;
		i++;
	}
	if ((s % 2) || (d % 2))
		return (0);
	return (1);
}

t_cmds	*ft_lstnew_cmd(char *cmd)
{
	t_cmds	*new;

	new = malloc(sizeof(t_cmds));
	if (!new)
		return (NULL);
	new->cmd = cmd;
	new->token = NULL;
	new->next = NULL;
	return (new);
}

t_cmds	*ft_lstlast_cmds(t_cmds *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd->next)
		cmd = cmd->next;
	return (cmd);
}
void	ft_darkadd_back(t_cmds **cmds, t_cmds *new)
{
	t_cmds	*temp;

	temp = *cmds;
	temp = ft_lstlast_cmds(temp);
	if (!temp)
		*cmds = new;
	else
		temp->next = new;
}


t_cmds	**ft_parse_line(char *str)
{
	char **tab;
	t_cmds **cmds;
	int i;
	t_cmds *cmd;
	
	i = 1;

	cmds = malloc(sizeof(t_cmds **));
	if (!cmds)
		return (NULL);
	if(!ft_check(str))
		return (0);
	tab = ft_dark_split(str, '|');
	if (!tab)
		return (NULL); 
	*cmds = ft_lstnew_cmd(tab[0]);
	if(*cmds == NULL)
		return (NULL);
    while (tab[i])
	{
		cmd = ft_lstnew_cmd(tab[i]);
		if (!cmd)
			return (NULL);
        ft_darkadd_back(cmds, cmd);
		i++;
	}
	return (cmds);
}
