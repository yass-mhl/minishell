/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansard <gansard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 21:20:51 by gregoire          #+#    #+#             */
/*   Updated: 2023/04/21 14:26:40 by gansard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_tab(char **tab, int nb)
{
	int	i;

	(void)nb;
	i = 0;
	while (tab && tab[i])
		free(tab[i++]);
	free(tab);
}
