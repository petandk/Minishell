/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanzana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:14:22 by rmanzana          #+#    #+#             */
/*   Updated: 2025/05/31 12:45:44 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_env_node(t_env *node)
{
	if (!node)
		return ;
	free(node->name);
	free(node->value);
	free(node);
}

static int	remove_env_var(t_env **envlist, char *name)
{
	t_env	*current;
	t_env	*prev;

	current = *envlist;
	prev = NULL;
	if (current && ft_strcmp(current->name, name) == 0)
	{
		*envlist = current->next;
		free_env_node(current);
		return (0);
	}
	while (current && ft_strcmp(current->name, name) != 0)
	{
		prev = current;
		current = current->next;
	}
	if (current)
	{
		prev->next = current->next;
		free_env_node(current);
	}
	return (0);
}

int	ft_unset(t_env **envlist, char **names)
{
	int	i;
	int	ret;
	int	error_cnt;

	if (!envlist || !*envlist || !names)
		return (1);
	error_cnt = 0;
	i = 0;
	while (names[i])
	{
		if (!is_valid_name(names[i]))
		{
			ft_putstr_fd("unset: ", 2);
			ft_putstr_fd(names[i], 2);
			ft_putendl_fd(": not a valid identifier", 2);
			error_cnt++;
		}
		else
		{
			ret = remove_env_var(envlist, names[i]);
			if (ret != 0)
				error_cnt++;
		}
		i++;
	}
	if (error_cnt > 0)
		return (1);
	return (0);
}
