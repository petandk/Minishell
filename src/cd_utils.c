/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanzana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 21:42:10 by rmanzana          #+#    #+#             */
/*   Updated: 2025/04/16 19:58:58 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_oldpwd_env(t_env *env, char *old_path)
{
	t_env	*current_node;

	if (!old_path)
		return (0);
	current_node = env;
	while (current_node && ft_strcmp(current_node->name, "OLDPWD") != 0)
		current_node = current_node->next;
	if (current_node)
	{
		free(current_node->value);
		current_node->value = ft_strdup(old_path);
		return (current_node->value != NULL);
	}
	else
	{
		return (ft_export(env, "OLDPWD=") == 0
			&& update_oldpwd_env(env, old_path));
	}
}
