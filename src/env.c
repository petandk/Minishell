/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanzana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:22:37 by rmanzana          #+#    #+#             */
/*   Updated: 2025/02/21 18:47:11 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*clone_env_list(t_env *envlist)
{
	t_env	*copy;
	t_env	*current;
	t_env	*newnode;

	copy = NULL;
	current = envlist;
	while (current)
	{
		newnode = env_lstnew(current->name, current->value);
		if (!newnode)
		{
			clear_env_list(&copy);
			return (NULL);
		}
		env_lstadd_back(&copy, newnode);
		current = current->next;
	}
	return (copy);
}

void	ft_show_env(t_env	*envlist, int is_env)
{
	t_env	*current;
	t_env	*sorted;

	sorted = NULL;
	if (is_env == 0)
	{
		sorted = clone_env_list(envlist);
		sort_env_list(sorted);
		current = sorted;
	}
	else
		current = envlist;
	while (current)
	{
		if (is_env == 0)
			printf("declare -x %s=\"%s\"\n", current->name, current->value);
		else if (is_env == 1)
			printf("%s=%s\n", current->name, current->value);

		current = current->next;
	}
	if (is_env == 0)
		clear_env_list(&sorted);
}

void	ft_env(t_env *envlist)
{
	ft_show_env(envlist, 1);
}
