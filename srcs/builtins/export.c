/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansard <gansard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 08:47:30 by ymehlil           #+#    #+#             */
/*   Updated: 2023/04/30 20:36:35 by gansard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*ft_check_name(char *name, t_env *env_list)
{
	t_env	*cur;

	cur = env_list;
	while (cur)
	{
		if (!ft_strcmp(cur->name, name))
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

int	check_argument_count(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}

int	is_valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '=')
		return (ft_putstr_fd("export: `=' not a valid identifier\n", 2), 0);
	while (str[i] && str[i] != '=')
	{
		if (ft_isalpha(str[i]) == 0)
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

void	update_env_value(t_env *cur, char *str)
{
	if (cur)
	{
		free(cur->value);
		cur->value = ft_strrtok(str, '=');
	}
}

int	ft_export(char **av, t_env **env_list, int i)
{
	int		arg_count;
	t_env	*cur;
	char	*tmp;

	arg_count = check_argument_count(av);
	if (arg_count == 1)
		return (ft_print_export(av), 0);
	while (i < arg_count)
	{
		if (!is_valid_identifier(av[i]))
		{
			g_exit_status = 1;
			return (1);
		}
		tmp = ft_strrtok(av[i], '=');
		cur = ft_get_env(ft_strtok(av[i], '='));
		if (cur && tmp != NULL)
			update_env_value(cur, av[i]);
		else if (!cur)
			ft_add_back_env(av[i], env_list);
		free(tmp);
		i++;
	}
	return (0);
}
