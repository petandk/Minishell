/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanzana <rmanzana@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 19:36:46 by rmanzana          #+#    #+#             */
/*   Updated: 2025/02/19 13:12:35 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap_env_content(t_env *a, t_env *b)
{
	char	*temp_name;
	char	*temp_value;

	temp_name = a->name;
	temp_value = a->value;
	a->name = b->name;
	a->value = b->value;
	b->name = temp_name;
	b->value = temp_value;
}

void	sort_env_list(t_env *envlist)
{
	int		swapped;
	t_env	*current;
	t_env	*last;

	last = NULL;
	swapped = 1;
	if (envlist == NULL || envlist->next == NULL)
		return ;
	while (swapped)
	{
		swapped = 0;
		current = envlist;
		while (current->next != last)
		{
			if (ft_strcmp(current->name, current->next->name) > 0)
			{
				swap_env_content(current, current->next);
				swapped = 1;
			}
			current = current->next;
		}
		last = current;
	}
}

void	ft_export(t_env	*envlist)
{
		t_env	*current;
		
		sort_env_list(envlist);
		current = envlist;
		while (current)
		{
			printf("%s=%s\n", current->name, current->value);
			current = current->next;
		}
}

void	clear_env_list(t_env **envlist)
{
	t_env	*aux;
	
	if (!envlist || !*envlist)
		return ;
	while (*envlist)
	{
		aux = (*envlist)->next;
		free((*envlist)->name);
		free((*envlist)->value);
		free(*envlist);
		*envlist = aux;
	}
}
