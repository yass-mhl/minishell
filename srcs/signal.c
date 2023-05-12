/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansard <gansard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 18:52:17 by ymehlil           #+#    #+#             */
/*   Updated: 2023/04/30 19:19:45 by gansard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_signal(int sig)
{
	g_exit_status += sig;
	if (sig == 2)
	{
		g_exit_status = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		write(2, "Quit (core dumped)\n", 20);
		exit(1);
	}
}

void	ft_signal_hd(int sig)
{
	t_fds	**fds;
	t_fds	*cur;
	t_fds	*tmp;

	if (sig == 2)
	{
		fds = get_fds();
		cur = *fds;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		while (cur)
		{
			close(cur->fd);
			cur = cur->next;
		}
		cur = (*fds);
		while (cur)
		{
			tmp = cur->next;
			free(cur);
			cur = tmp;
		}
		exit(0);
	}
}

void	ft_print_exit_free_all(t_cmds **cmds)
{
	(void)cmds;
	printf("exit\n");
	ft_free_env(get_adress());
	exit(0);
}

void	ft_signal_cat(int sig)
{
	g_exit_status += sig;
	if (sig == 2)
	{
		g_exit_status = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		exit(130);
	}
	if (sig == SIGQUIT)
	{
		write(2, "Quit (core dumped)\n", 20);
		exit(1);
	}
}
