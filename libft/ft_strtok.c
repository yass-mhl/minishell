/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:32:37 by ymehlil           #+#    #+#             */
/*   Updated: 2023/04/27 18:19:30 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strtok(char *str, char sep)
{
	static char	*save;
	char		*ret;
	int			i;

	if (str)
		save = str;
	if (!save)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != sep)
		i++;
	if (save[i] == '\0' && i == 0)
	{
		save = NULL;
		return (NULL);
	}
	ret = ft_substr(save, 0, i);
	if (!ret)
		return (NULL);
	if (save[i] == '\0')
		save = NULL;
	else
		save += i + 1;
	return (ret);
}
