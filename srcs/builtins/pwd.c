/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansard <gansard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 23:06:01 by ymehlil           #+#    #+#             */
/*   Updated: 2023/04/27 13:38:23 by gansard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(char **args)
{
	char	*path;

	(void) args;
	path = getcwd(NULL, 0);
	if (!path)
		return ;
	ft_printf("%s\n", path);
	free(path);
	return ;
}
