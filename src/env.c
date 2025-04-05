/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanzana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:22:37 by rmanzana          #+#    #+#             */
/*   Updated: 2025/04/04 18:49:04 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*clone_env_list(t_env *envlist)
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

void	ft_show_env(t_env *envlist, int is_env)
{
	t_env	*current;

	if (!envlist)
		return ;
	current = envlist;
	while (current)
	{
		if (is_env == 0)
			printf("declare -x %s=\"%s\"\n", current->name, current->value);
		else if (is_env == 1)
			printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
}

void	ft_env(t_env *envlist)
{
	ft_show_env(envlist, 1);
}
