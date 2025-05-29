/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanzana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:14:22 by rmanzana          #+#    #+#             */
/*   Updated: 2025/04/05 10:48:28 by rmanzana         ###   ########.fr       */
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

int	ft_unset(t_env **envlist, char *name)
{
	if (!envlist || !*envlist || !name)
		return (1);
	if (!is_valid_name(name))
	{
		ft_putstr_fd("unset", 2);
		ft_putstr_fd(name, 2);
		ft_putendl_fd(": not a valid identifier", 2);
		return (1);
	}
	return (remove_env_var(envlist, name));
}
