/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansard <gansard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 12:21:15 by gregoire          #+#    #+#             */
/*   Updated: 2023/04/27 12:36:47 by gansard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	expand_or_not(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			return (0);
		i++;
	}
	return (1);
}

char	*read_and_compare_line(char *limiteur, int bool, int saved_stdout)
{
	char	*str;
	int		tmp_stdout;

	str = NULL;
	tmp_stdout = dup(STDOUT_FILENO);
	ft_add_fd(tmp_stdout);
	dup2(saved_stdout, STDOUT_FILENO);
	str = readline("> ");
	if (!str)
	{
		printf("Minishell: here-document by end-of-file (wanted `%s')\n",
			limiteur);
		return (NULL);
	}
	dup2(tmp_stdout, STDOUT_FILENO);
	ft_add_fd(tmp_stdout);
	close(tmp_stdout);
	if (!ft_strcmp(str, limiteur))
	{
		free(str);
		return (NULL);
	}
	if (bool)
		str = ft_expend_d(str, 0, -1);
	return (str);
}

void	write_line_to_file(int fd, char *str)
{
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}

void	loop_here_doc(char *str, char *limiteur, int bool, int *fd)
{
	str = read_and_compare_line(limiteur, bool, fd[1]);
	while (str)
	{
		write_line_to_file(fd[0], str);
		free(str);
		str = read_and_compare_line(limiteur, bool, fd[1]);
	}
}

int	ft_here_doc(t_token *token, int saved_stdin, int saved_stdout, char *str)
{
	int		fd[0];
	char	*limiteur;
	int		bool;

	dup2(saved_stdin, STDIN_FILENO);
	fd[1] = saved_stdout;
	if (token->next)
	{
		limiteur = token->next->word;
		bool = expand_or_not(limiteur);
		limiteur = clean_up_lim(limiteur, 0, -1);
		fd[0] = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		ft_add_fd(fd[0]);
		loop_here_doc(str, limiteur, bool, fd);
		close(fd[0]);
		fd[0] = open("here_doc", O_RDONLY);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		unlink("here_doc");
		free(limiteur);
	}
	return (1);
}
