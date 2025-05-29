/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanzana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:22:37 by rmanzana          #+#    #+#             */
/*   Updated: 2025/05/29 19:14:59 by rmanzana         ###   ########.fr       */
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

void	ft_env(t_shell *shell, char **args)
{
	t_env	*temp_env;
	int		i;
	char	**splitd;
	t_env	env_var;
	
	if (!args || !args[0])
	{
		shell->exit_status = 0;
		return (ft_show_env(shell->env, 1));
	}
	temp_env = clone_env_list(shell->env);
	if (!temp_env)
	{
		shell->exit_status = 1;
		return ;
	}
	i = 0;
	while (args[i] && ft_strchr(args[i], '='))
	{
		if (process_export(args[i], &splitd, &env_var, 1) == 0)
		{
			update_or_create_var(&temp_env, env_var.name, env_var.value);
			free_split(splitd, -1);
		}
		else
		{

			clear_env_list(&temp_env);
			shell->exit_status = 1;
			return ;
		}
		i++;
	}
	if (args[i])
	{
		ft_putstr_fd("Minishell: Error: \"env\" should be ", 2);
		ft_putstr_fd("executed without options or arguments.\n", 2);
		shell->exit_status = 1;
	}
	else
	{
		ft_show_env(temp_env, 1);
		shell->exit_status = 0;
	}
	clear_env_list(&temp_env);
}
