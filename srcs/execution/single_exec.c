/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansard <gansard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 09:41:59 by gregoire          #+#    #+#             */
/*   Updated: 2023/04/30 20:38:49 by gansard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_variables(int *fd_in, int svd_standart[2], t_cmds *cmd)
{
	*fd_in = 0;
	svd_standart[0] = dup(STDIN_FILENO);
	ft_add_fd(svd_standart[0]);
	svd_standart[1] = dup(STDOUT_FILENO);
	ft_add_fd(svd_standart[1]);
	if (!cmd->args[0])
		cmd->args[0] = ft_strdup("");
}

void	prepare_tmp(int tmp[2])
{
	tmp[0] = dup(STDOUT_FILENO);
	tmp[1] = dup(STDIN_FILENO);
}

int	handle_redirections(int tmp[2], int svd_standart[2])
{
	if (dup2(tmp[0], STDOUT_FILENO) == -1 || dup2(tmp[1], STDIN_FILENO) == -1)
		return (0);
	close(tmp[0]);
	close(tmp[1]);
	close(svd_standart[1]);
	return (1);
}

int	handle_builtin_execution(t_cmds *cmd, t_cmds **cmds, int *tmp,
		int *svd_standart)
{
	int	res;

	prepare_tmp(tmp);
	if (!ft_redir(cmd->token, svd_standart[0], svd_standart[1]))
	{
		close(tmp[0]);
		close(tmp[1]);
		return (1);
	}
	res = ft_execve_s(cmd->args, cmds, tmp, svd_standart);
	if (handle_redirections(tmp, svd_standart))
	{
		close(tmp[0]);
		close(tmp[1]);
		return (res);
	}
	else
	{
		close(tmp[0]);
		close(tmp[1]);
		return (1);
	}
}

int	ft_single_exec(t_cmds *cmd, t_cmds **cmds)
{
	int		fd_in;
	int		tmp[2];
	int		svd_standart[2];
	pid_t	pid;

	init_variables(&fd_in, svd_standart, cmd);
	if (ft_is_builtin(cmd->args[0]))
	{
		return (handle_builtin_execution(cmd, cmds, tmp, svd_standart));
	}
	execute_command(cmd, &fd_in, svd_standart, &pid);
	get_cmd_code(pid);
	close(fd_in);
	close(svd_standart[1]);
	close(svd_standart[0]);
	return (g_exit_status);
}

//int	ft_single_exec(t_cmds *cmd, t_cmds **cmds)
//{
//	int		fd_in;
//	int		tmp[2];
//	int		res;
//	int		svd_standart[2];
//	pid_t	pid;

//	init_variables(&fd_in, svd_standart, cmd);
//	if (ft_is_builtin(cmd->args[0]))
//	{
//		prepare_tmp(tmp);
//		if (!ft_redir(cmd->token, svd_standart[0], svd_standart[1]))
//		{
//			close(tmp[0]);
//			close(tmp[1]);
//			return (1);
//		}
//		res = ft_execve_s(cmd->args, cmds, tmp, svd_standart);
//		if (handle_redirections(tmp, svd_standart))
//		{
//			close(tmp[0]);
//			close(tmp[1]);
//			return (res);
//		}
//		else
//		{
//			close(tmp[0]);
//			close(tmp[1]);
//			return (1);
//		}
//	}
//	execute_command(cmd, &fd_in, svd_standart, &pid);
//	get_cmd_code(pid);
//	close(fd_in);
//	close(svd_standart[1]);
//	close(svd_standart[0]);
//	return (g_exit_status);
//}
