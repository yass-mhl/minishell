/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansard <gansard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 09:34:32 by gansard           #+#    #+#             */
/*   Updated: 2023/04/30 19:20:43 by gansard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_file_in(t_token *token)
{
	int	fd;

	if (!token->next)
		return (-1);
	fd = open(token->next->word, O_RDONLY);
	if (fd == -1)
	{
		perror("Minishell ");
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (fd);
}

static int	ft_file_out(t_token *token)
{
	int	fd;

	fd = open(token->next->word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (fd);
}

static int	ft_file_outsur(t_token *token)
{
	int	fd;

	signal(SIGINT, SIG_IGN);
	fd = open(token->next->word, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (-1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (fd);
}

int	ft_set_redir(t_token *token, int saved_stdin, int saved_stdout)
{
	int		fd;
	char	*str;

	str = NULL;
	signal(SIGINT, ft_signal_hd);
	signal(SIGQUIT, SIG_IGN);
	if (token->type == FILE_IN)
		fd = ft_file_in(token);
	if (token->type == HERE_DOC)
		fd = ft_here_doc(token, saved_stdin, saved_stdout, str);
	if (token->type == FILE_OUT)
		fd = ft_file_out(token);
	if (token->type == FILE_OUT_SUR)
		fd = ft_file_outsur(token);
	if (fd == -1)
		return (-1);
	if (fd)
		return (0);
	return (1);
}
