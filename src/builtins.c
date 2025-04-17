/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanzana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:24:14 by rmanzana          #+#    #+#             */
/*   Updated: 2025/04/16 21:39:04 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	builtins_split(t_shell *shell, char **cmd)
{
	if (!ft_strcmp(cmd[0], "pwd"))
		return (ft_pwd(), 1);
	else if (!ft_strcmp(cmd[0], "export"))
	{
		if (cmd[1])
			return (ft_export(shell->env, cmd[1]), 1);
		else
			return (ft_export(shell->env, NULL), 1);
	}
	else if (!ft_strcmp(cmd[0], "unset"))
		return (ft_unset(&(shell)->env, cmd[1]), 1);
	else if (!ft_strcmp(cmd[0], "env"))
	{
		if (cmd[1] == NULL)
			return (ft_env(shell->env, NULL), 1);
		else
			return (ft_env(shell->env, cmd + 1), 1);
	}
	return (0);
}

int	builtins(t_shell *shell, char **cmd)
{
	if (!ft_strcmp(cmd[0], "exit"))
	{
		if (cmd[1] && cmd[1][0] != '\0')
			return (ft_exit(&shell, ft_atoi(cmd[1])), 1);
		else
			return (ft_exit(&shell, 0), 1);
	}
	if (!ft_strcmp(cmd[0], "echo"))
	{
		if (cmd[1] && !ft_strcmp(cmd[1], "-n"))
			return (ft_echo(cmd[2], 1), 1);
		else
			return (ft_echo(cmd[1], 0), 1);
	}
	else if (!ft_strcmp(cmd[0], "cd"))
		return (ft_cd(shell, cmd[1]), 1);
	return (builtins_split(shell, cmd));
}
