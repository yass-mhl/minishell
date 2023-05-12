/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansard <gansard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 09:58:00 by gregoire          #+#    #+#             */
/*   Updated: 2023/04/30 19:02:41 by gansard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_create_str_hd(char *str, char **part)
{
	int	i;

	i = find_stop_index_hd(str);
	*part = ft_create_part(str, i);
	if (!(*part))
		return (0);
	return (i);
}

char	*clean_up_lim(char *str, int i, int j)
{
	char	**tab;
	char	*res;

	tab = ft_calloc(nb_str_hd(str) + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	while (str[i])
	{
		i += ft_create_str_hd(&str[i], &tab[++j]);
		if (!i)
			return (ft_free_tab(tab, 0), NULL);
		ft_get_value_hd(&tab[j]);
	}
	if (tab[j])
		j++;
	tab[j] = NULL;
	res = ft_join_parts(tab, j);
	if (!res)
		return (NULL);
	if (tab)
		ft_free_tab(tab, 0);
	return (res);
}

t_fds	**get_fds(void)
{
	static t_fds	*new = NULL;

	return (&new);
}

int	ft_add_fd(int fd)
{
	t_fds	**last;
	t_fds	*new;

	last = get_fds();
	new = ft_calloc(1, sizeof(t_fds));
	if (!new)
		return (-1);
	new->fd = fd;
	new->next = *last;
	*last = new;
	return (0);
}
