/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansard <gansard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 10:44:53 by ymehlil           #+#    #+#             */
/*   Updated: 2023/04/30 18:58:54 by gansard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check(char *str, int i, int d, int s)
{
	while (str[i])
	{
		if (str[i] == '|' && !(s % 2) && !(d % 2))
		{
			i++;
			while (str[i] && str[i] == ' ')
				i++;
			if (!str[i] || str[i] == '|')
				return (printf("Minishell: syntax error near \
					unexpected token '|'\n"),
					0);
		}
		if (str[i] == 34 && (s % 2 == 0))
			d++;
		if (str[i] == 39 && (d % 2 == 0))
			s++;
		i++;
	}
	if ((s % 2) || (d % 2))
		return (printf("Invalid number of quotes\n"), 0);
	return (1);
}

t_cmds	*ft_lstnew_cmd(char *cmd, t_cmds **cmds)
{
	t_cmds	*new;

	new = ft_calloc(1, sizeof(t_cmds));
	if (!new)
		return (NULL);
	new->cmd = cmd;
	new->token = NULL;
	new->args = NULL;
	new->first = cmds;
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
	char	**tab;
	t_cmds	**cmds;
	int		i;
	t_cmds	*cmd;

	i = 1;
	cmds = ft_calloc(1, sizeof(t_cmds **));
	if (!cmds || !ft_check(str, 0, 0, 0))
		return (ft_free_cmdslst(cmds), NULL);
	tab = ft_dark_split(str, '|', 0, 0);
	free(str);
	if (!tab)
		return (NULL);
	*cmds = ft_lstnew_cmd(tab[0], cmds);
	if (*cmds == NULL)
		return (free(tab), NULL);
	while (tab[i])
	{
		cmd = ft_lstnew_cmd(tab[i++], cmds);
		if (!cmd)
			return (NULL);
		ft_darkadd_back(cmds, cmd);
	}
	free(tab);
	return (cmds);
}
