/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansard <gansard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 08:51:44 by gansard           #+#    #+#             */
/*   Updated: 2023/04/27 13:11:12 by gansard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	restore_std_descriptors(int svd_standart[2])
{
	close(svd_standart[0]);
	close(svd_standart[1]);
}

void	init_pid_fds_arrays(pid_t **pids, int **fds, t_cmds **cmds,
		int *svd_standart)
{
	*pids = malloc(len_cmd(cmds) * sizeof(pid_t));
	*fds = malloc(len_cmd(cmds) * sizeof(int));
	svd_standart[0] = dup(STDIN_FILENO);
	svd_standart[1] = dup(STDOUT_FILENO);
}

void	execute_and_manage_commands(t_cmds **cmds, int *fds, pid_t *pids,
		int svd_standart[2])
{
	t_cmds	*cur;
	int		fd_in;
	int		n;

	fd_in = 0;
	cur = (*cmds);
	n = 0;
	while (cur)
	{
		fds[n] = execute_command(cur, &fd_in, svd_standart, &pids[n]);
		if (is_here_doc(cur))
			get_cmd_code(pids[n]);
		cur = cur->next;
		n++;
	}
}

void	cleanup_and_close_fds(int *fds, pid_t *pids, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (fds[i])
			close(fds[i]);
		get_cmd_code(pids[i++]);
	}
}

int	ft_execution(t_cmds **cmds)
{
	int		svd_standart[2];
	pid_t	*pids;
	int		*fds;

	init_pid_fds_arrays(&pids, &fds, cmds, svd_standart);
	execute_and_manage_commands(cmds, fds, pids, svd_standart);
	cleanup_and_close_fds(fds, pids, len_cmd(cmds));
	restore_std_descriptors(svd_standart);
	free(pids);
	free(fds);
	return (g_exit_status);
}
