/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanzana <rmanzana@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 19:36:46 by rmanzana          #+#    #+#             */
/*   Updated: 2025/04/16 21:24:45 by rmanzana         ###   ########.fr       */
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

int	process_export(char *arg, char ***splitd, char **name, char **value, int is_env)
{
	*splitd = split_first(arg, '=');
	if (!*splitd || !*splitd[0])
	{
		if (*splitd)
			free_split(*splitd, -1);
		return (1);
	}
	*name = (*splitd)[0];
	if ((*splitd)[1])
		*value = (*splitd)[1];
	else
		*value = "";
	if (!is_valid_name(*name))
	{
		if (is_env)
			ft_putstr_fd("env: ", 2);
		else
			ft_putstr_fd("export: ", 2);
		ft_putstr_fd(*name, 2);
		ft_putendl_fd(": not a valid identifier", 2);
		free_split(*splitd, -1);
		return (1);
	}
	return (0);
}

int	update_or_create_var(t_env **envlist, char *name, char *value)
{
	t_env	*exist;

	exist = find_env_var(*envlist, name);
	if (exist)
	{
		free(exist->value);
		exist->value = ft_strdup(value);
		if (!exist->value)
			return (1);
	}
	else
	{
		exist = env_lstnew(name, value);
		if (!exist)
			return (1);
		env_lstadd_back(envlist, exist);
	}
	return (0);
}

int	ft_export(t_env *envlist, char *arg)
{
	char	**splitd;
	char	*name;
	char	*value;
	int		ret;
	t_env	*sorted;

	if (!arg || arg[0] == '\0')
	{
		sorted = clone_env_list(envlist);
		if (!sorted)
			return (1);
		sort_env_list(sorted);
		ft_show_env(sorted, 0);
		clear_env_list(&sorted);
		return (0);
	}
	if (process_export(arg, &splitd, &name, &value, 0))
		return (1);
	ret = update_or_create_var(&envlist, name, value);
	free_split(splitd, -1);
	return (ret);
}
