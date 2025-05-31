/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanzana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:24:14 by rmanzana          #+#    #+#             */
/*   Updated: 2025/05/31 13:25:10 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	builtins_split(t_shell *shell, char **cmd)
{
	if (!ft_strcmp(cmd[0], "pwd"))
		return (ft_pwd(shell), 1);
	else if (!ft_strcmp(cmd[0], "export"))
	{
		if (cmd[1])
			return (ft_export(shell, cmd + 1), 1);
		else
			return (ft_export(shell, NULL), 1);
	}
	else if (!ft_strcmp(cmd[0], "unset"))
		return (ft_unset(&(shell)->env, cmd + 1), 1);
	else if (!ft_strcmp(cmd[0], "env"))
	{
		if (cmd[1] == NULL)
			return (ft_env(shell, NULL), 1);
		else
			return (ft_env(shell, cmd + 1), 1);
	}
	return (0);
}

int	builtins(t_shell *shell, char **cmd, t_comand_data *comd, int cmd_count)
{
	if (!ft_strcmp(cmd[0], "exit"))
	{
		if (cmd[1] && cmd[1][0] != '\0')
		{
			if (!is_valid_number(cmd[1]))
			{
				ft_putstr_fd("Minishell: exit: ", 2);
				ft_putstr_fd(cmd[1], 2);
				ft_putendl_fd(": numeric argument required", 2);
				return (ft_exit(&shell, 2, comd, cmd_count), 1);
			}
			return (ft_exit(&shell, ft_atoi(cmd[1]), comd, cmd_count), 1);
		}
		else
			return (ft_exit(&shell, 0, comd, cmd_count), 1);
	}
	if (!ft_strcmp(cmd[0], "echo"))
	{
		return (ft_echo(shell, cmd), 1);
	}
	else if (!ft_strcmp(cmd[0], "cd"))
		return (ft_cd(shell, cmd[1]), 1);
	return (builtins_split(shell, cmd));
}
