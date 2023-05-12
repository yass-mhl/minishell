/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansard <gansard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:01:09 by ymehlil           #+#    #+#             */
/*   Updated: 2023/04/30 20:35:35 by gansard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <signal.h>

int	g_exit_status;

int	ft_len_lst(t_cmds **cmds)
{
	t_cmds	*cur;
	int		len;

	cur = (*cmds);
	len = 0;
	while (cur)
	{
		cur = cur->next;
		len++;
	}
	return (len);
}

int	is_empty_or_whitespace(const char *s)
{
	int	i;

	i = 0;
	while (s)
	{
		if (!(s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\v'
				|| s[i] == '\f' || s[i] == '\r'))
			return (0);
		i++;
	}
	return (1);
}

int	process_input(char *str)
{
	t_cmds	**cmds;

	cmds = NULL;
	if (str == NULL)
		ft_print_exit_free_all(cmds);
	if (*str != '\0')
	{
		cmds = ft_parse_line(str);
		if (cmds)
		{
			if (ft_tokenise(cmds))
			{
				if (ft_len_lst(cmds) == 1)
					g_exit_status = ft_single_exec(*cmds, cmds);
				else
					g_exit_status = ft_execution(cmds);
			}
		}
		ft_free_cmdslst(cmds);
	}
	else
		free(str);
	return (g_exit_status);
}

int	main(int ac, char **av, char **env)
{
	char	*str;

	ft_init_env(env);
	g_exit_status = 0;
	(void)ac;
	(void)av;
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, ft_signal);
		str = readline("minishell$> ");
		add_history(str);
		g_exit_status = process_input(str);
	}
	return (g_exit_status);
}
