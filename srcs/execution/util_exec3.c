/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_exec3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansard <gansard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 09:50:49 by gregoire          #+#    #+#             */
/*   Updated: 2023/04/30 20:37:47 by gansard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cleanup_pipes(int *fd_in, int *fd)
{
	close(fd[1]);
	if (*fd_in)
		close(*fd_in);
	*fd_in = fd[0];
}

char	**ft_parse_env(int i, int j)
{
	char	**temp;
	char	**paths;

	if (!white_get_env("PATH"))
		return (NULL);
	temp = ft_split(white_get_env("PATH"), ':');
	if (!temp)
		return (NULL);
	i = -1;
	while (temp[++i])
		;
	paths = ft_calloc((i + 1), (sizeof(char *)));
	if (!paths)
		return (ft_free_tab(temp, 0), NULL);
	j = 0;
	while (j < i)
	{
		paths[j] = ft_strjoin(temp[j], "/");
		if (!paths[j])
			ft_free_tab(paths, 0);
		j++;
	}
	paths[i] = NULL;
	ft_free_tab(temp, 0);
	return (paths);
}

int	is_here_doc(t_cmds *cmds)
{
	t_token	*cur;

	cur = (*cmds->token);
	while (cur)
	{
		if (!strcmp(cur->word, "<<"))
			return (1);
		cur = cur->next;
	}
	return (0);
}

void	get_cmd_code(pid_t pid)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		g_exit_status = 130;
		printf("\n");
	}
}
