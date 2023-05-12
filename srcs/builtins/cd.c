/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansard <gansard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 08:06:30 by ymehlil           #+#    #+#             */
/*   Updated: 2023/04/27 15:10:48 by gansard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_home(void)
{
	char	*path;
	char	*tmp;

	path = white_get_env("HOME");
	if (!path)
	{
		ft_printf("HOME not set\n");
		return (NULL);
	}
	tmp = ft_strdup(path);
	return (tmp);
}

void	update_oldpwd(t_env **env, char *oldpwd)
{
	t_env	*cur;

	cur = ft_get_env(ft_strtok(oldpwd, '='));
	if (cur)
	{
		free(cur->value);
		cur->value = ft_strrtok(oldpwd, '=');
	}
	else
		ft_add_back_env(oldpwd, env);
}

void	update_pwd(t_env **env)
{
	char	*pwd;
	t_env	*cur;
	char	*tmp;

	tmp = getcwd(NULL, 0);
	pwd = ft_strjoin("PWD=", tmp);
	free(tmp);
	cur = ft_get_env(ft_strtok(pwd, '='));
	if (cur)
	{
		free(cur->value);
		cur->value = ft_strrtok(pwd, '=');
	}
	else
		ft_add_back_env(pwd, env);
	free(pwd);
}

int	update_env(t_env **env, char *path, char *oldpwd)
{
	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		g_exit_status = 1;
		return (free(path), free(oldpwd), g_exit_status);
	}
	update_pwd(env);
	update_oldpwd(env, oldpwd);
	return (free(path), free(oldpwd), 1);
}

int	ft_cd(char **args, t_env **env)
{
	char	*path;
	char	*oldpwd;
	char	*tmp;

	if (args[1] && args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		g_exit_status = 1;
		return (g_exit_status);
	}
	tmp = getcwd(NULL, 0);
	oldpwd = ft_strjoin("OLDPWD=", tmp);
	free(tmp);
	if (!oldpwd)
		return (0);
	if (!args[1] || !ft_strcmp(args[1], "~"))
	{
		path = get_home();
		if (!path)
			return (free(path), printf("HOME not set\n"), 0);
	}
	else
		path = ft_strdup(args[1]);
	return (update_env(env, path, oldpwd));
}
