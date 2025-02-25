/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanzana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:14:22 by rmanzana          #+#    #+#             */
/*   Updated: 2025/02/25 14:27:34 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_env *envlist, char *name)
{
	t_env	*current;
	t_env	*prev;

	current = envlist;
	prev = NULL;
	if (!envlist || !name)
		return (1);
	if (current && ft_strcmp(current->name, name) == 0)
	{
		envlist = current->next;
		free(current->name);
		free(current->value);
		free(current);
		return(0);
	}

	while (current && ft_strcmp(current->name, name) != 0)
	{
		prev = current;
		current = current->next;
	}
	if (current)
	{
		prev->next = current->next;
		free(current->name);
		free(current->value);
		free(current);
	}
	return (0);
}
