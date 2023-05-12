/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansard <gansard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 21:07:38 by gregoire          #+#    #+#             */
/*   Updated: 2023/04/30 20:38:16 by gansard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_redir(t_token **token, int saved_stdin, int saved_stdout)
{
	t_token	*cur;

	cur = (*token);
	while (cur)
	{
		if (cur->type == FILE_IN || cur->type == HERE_DOC
			|| cur->type == FILE_OUT || cur->type == FILE_OUT_SUR)
		{
			if (ft_set_redir(cur, saved_stdin, saved_stdout) == -1)
			{
				dup2(saved_stdin, STDIN_FILENO);
				g_exit_status = 1;
				return (close(saved_stdin), close(saved_stdout), 0);
			}
		}
		cur = cur->next;
	}
	return (close(saved_stdin), close(saved_stdout), 1);
}

char	*ft_get_path(char **path, char *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	while (path[i])
	{
		if (!access(cmd, X_OK))
			return (cmd);
		tmp = ft_strjoin(path[i], cmd);
		if (!access(tmp, X_OK))
			return (tmp);
		free(tmp);
		i++;
	}
	return (NULL);
}

int	ft_is_builtin(char *cmd_name)
{
	if (!ft_strcmp(cmd_name, "echo"))
		return (1);
	else if (!ft_strcmp(cmd_name, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd_name, "cd"))
		return (1);
	else if (!ft_strcmp(cmd_name, "exit"))
		return (1);
	else if (!ft_strcmp(cmd_name, "env"))
		return (1);
	else if (!ft_strcmp(cmd_name, "export"))
		return (1);
	else if (!ft_strcmp(cmd_name, "unset"))
		return (1);
	else
		return (0);
}

int	ft_execve_b(char **args, t_cmds **cmds)
{
	t_env	**env_list;

	env_list = get_adress();
	if (!ft_strcmp(args[0], "echo"))
		ft_echo(args);
	else if (!ft_strcmp(args[0], "pwd"))
		ft_pwd(args);
	else if (!ft_strcmp(args[0], "cd"))
		ft_cd(args, env_list);
	else if (!ft_strcmp(args[0], "exit"))
		ft_exit(args, cmds);
	else if (!ft_strcmp(args[0], "env"))
		ft_env(args);
	else if (!ft_strcmp(args[0], "export"))
		ft_export(args, env_list, 1);
	else if (!ft_strcmp(args[0], "unset"))
		ft_unset(args, env_list);
	exit(g_exit_status);
}

int	ft_execve_s(char **args, t_cmds **cmds, int *tmp, int *svd_standart)
{
	t_env	**env_list;

	env_list = get_adress();
	if (!ft_strcmp(args[0], "echo"))
		ft_echo(args);
	else if (!ft_strcmp(args[0], "pwd"))
		ft_pwd(args);
	else if (!ft_strcmp(args[0], "cd"))
		ft_cd(args, env_list);
	else if (!ft_strcmp(args[0], "exit"))
	{
		close(tmp[0]);
		close(tmp[1]);
		close(svd_standart[1]);
		ft_exit(args, cmds);
	}
	else if (!ft_strcmp(args[0], "env"))
		ft_env(args);
	else if (!ft_strcmp(args[0], "export"))
		ft_export(args, env_list, 1);
	else if (!ft_strcmp(args[0], "unset"))
		ft_unset(args, env_list);
	return (g_exit_status);
}
