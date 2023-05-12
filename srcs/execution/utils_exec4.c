/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansard <gansard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:39:27 by gansard           #+#    #+#             */
/*   Updated: 2023/04/30 20:43:59 by gansard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	len_cmd(t_cmds **cmds)
{
	t_cmds	*cur;
	int		i;

	cur = (*cmds);
	i = 0;
	while (cur)
	{
		cur = cur->next;
		i++;
	}
	return (i);
}

int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0)
	{
		return (S_ISDIR(path_stat.st_mode));
	}
	return (0);
}

int	handle_errno_and_exit(void)
{
	if (errno == 14)
	{
		ft_putstr_fd("Minishell: command not found\n", 2);
		g_exit_status = 127;
		exit(g_exit_status);
	}
	else if (errno == 13)
	{
		ft_putstr_fd("Minishell: Permission denied\n", 2);
		g_exit_status = 127;
		exit(127);
	}
	else
	{
		perror("Minishell");
		g_exit_status = 1;
		exit(1);
	}
	return (1);
}
