/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanzana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:23:05 by rmanzana          #+#    #+#             */
/*   Updated: 2025/04/13 21:26:53 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_basic_env(void)
{
	t_env	*envlist;
	t_env	*newnode;
	char	*pwd;

	envlist = NULL;
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		newnode = env_lstnew("PWD", pwd);
		if (newnode)
			env_lstadd_back(&envlist, newnode);
		free(pwd);
	}
	newnode = env_lstnew("SHLVL", "1");
	if (newnode)
		env_lstadd_back(&envlist, newnode);
	newnode = env_lstnew("PATH", "/usr/local/bin:/usr/bin:/bin");
	if (newnode)
		env_lstadd_back(&envlist, newnode);
	return (envlist);
}

t_env	*find_env_var(t_env *envlist, char *name)
{
	t_env	*current;

	if (!envlist || !name)
		return (NULL);
	current = envlist;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
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
