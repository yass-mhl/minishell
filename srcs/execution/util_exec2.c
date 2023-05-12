/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_exec2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansard <gansard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 21:11:30 by gregoire          #+#    #+#             */
/*   Updated: 2023/04/30 20:42:30 by gansard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	child_process(t_cmds *cur, int *fd_in, int *fd, int *svd_standart)
{
	char	**tmp;

	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, ft_signal_cat);
	setup_pipes(fd_in, fd, cur);
	if (!ft_redir(cur->token, svd_standart[0], svd_standart[1]))
		exit(g_exit_status);
	tmp = env_to_str(*(get_adress()));
	if (ft_trigger(cur->args, cur->first, tmp) == -1)
	{
		handle_errno_and_exit();
		ft_free_tab(tmp, 0);
		exit(g_exit_status);
	}
	return (1);
}

//int	child_process(t_cmds *cur, int *fd_in, int *fd, int *svd_standart)
//{
//	char	**tmp;

//	signal(SIGQUIT, SIG_DFL);
//	signal(SIGINT, ft_signal_cat);
//	setup_pipes(fd_in, fd, cur);
//	if (!ft_redir(cur->token, svd_standart[0], svd_standart[1]))
//		exit (g_exit_status);
//	tmp = env_to_str(*(get_adress()));
//	if (ft_trigger(cur->args, cur->first, tmp) == -1)
//	{
//		if (errno == 14)
//		{
//            ft_putstr_fd("Minishell: command not found\n", 2);
//			g_exit_status = 127;
//            exit(g_exit_status);
//        }
//		else if (errno == 13)
//		{
//            ft_putstr_fd("Minishell: Permission denied\n", 2);
//			g_exit_status = 127;
//            exit(127);
//        }
//		else
//		{
//            perror("Minishell");
//			g_exit_status = 1;
//            exit(1);
//        }
//		ft_free_tab(tmp, 0);
//		exit(g_exit_status);
//	}
//	return (1);
//}

int	execute_command(t_cmds *cur, int *fd_in, int *svd_standart,
		pid_t *child_pid)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (perror("Error"), 0);
	dup2(svd_standart[0], STDIN_FILENO);
	pid = fork();
	if (pid == 0)
	{
		if (!child_process(cur, fd_in, fd, svd_standart))
			return (0);
	}
	else
	{
		*child_pid = pid;
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		cleanup_pipes(fd_in, fd);
	}
	return (fd[0]);
}

void	handle_errors_and_exit(char *path, char *arg)
{
	if (!path)
	{
		ft_putstr_fd("command not found\n", 2);
		g_exit_status = 127;
		exit(127);
	}
	if (is_directory(path))
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(" is a directory\n", 2);
		g_exit_status = 126;
		exit(126);
	}
}

int	ft_trigger(char **args, t_cmds **cmds, char **tmp)
{
	char	*path;
	char	**paths;

	paths = ft_parse_env(-1, 0);
	if (!args[0] || !args[0][0])
		exit(0);
	if (ft_is_builtin(args[0]))
		return (ft_execve_b(args, cmds));
	if (paths)
		path = ft_get_path(paths, args[0]);
	else if (!access(args[0], X_OK))
		path = args[0];
	else
		path = NULL;
	ft_free_tab(paths, 0);
	handle_errors_and_exit(path, args[0]);
	return (execve(path, args, tmp));
}

//int	ft_trigger(char **args, t_cmds **cmds, char **tmp)
//{
//	char	*path;
//	char	**paths;

//	paths = ft_parse_env(-1, 0);
//	path = NULL;
//	if (!args[0] || !args[0][0])
//		exit(0);
//	if (ft_is_builtin(args[0]))
//		return (ft_execve_b(args, cmds));
//	if (paths)
//		path = ft_get_path(paths, args[0]);
//	else
//	{
//		if (!access(args[0], X_OK))
//			path = args[0];
//	}
//	ft_free_tab(paths, 0);
//	if (!path)
//	{
//        ft_putstr_fd("command not found\n", 2);
//		g_exit_status = 127;
//		exit(127);
//	}
//	if (is_directory(path))
//	{
//		ft_putstr_fd(args[0], 2);
//        ft_putstr_fd(" is a directory\n", 2);
//		g_exit_status = 126;
//		exit(126);
//	}
//	return (execve(path, args, tmp));
//}

void	setup_pipes(int *fd_in, int *fd, t_cmds *cur)
{
	close(fd[0]);
	if (*fd_in != 0)
	{
		dup2(*fd_in, STDIN_FILENO);
		close(*fd_in);
	}
	if (cur->next)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
}
