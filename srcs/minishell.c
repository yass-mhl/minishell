/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:01:09 by ymehlil           #+#    #+#             */
/*   Updated: 2023/03/19 18:26:56 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	char *str;
	char **tab;
	// char *path;
	// char BUFF[1000]; 
	

	str = readline("minishell$> ");
	ft_printf("%s\n", str);
	t_cmds **cmds = ft_parse_line(str);
	if(!cmds)
	{
		ft_printf("error\n");
		return (0);
	}
	tab = ft_dark_split_token((*cmds)->cmd);
	while (*tab)
	{
		ft_printf("%s\n", *tab);
		tab++;
	}
	return (0);
}
