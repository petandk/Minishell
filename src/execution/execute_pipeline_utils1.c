/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline_utils1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:58:37 by gpolo             #+#    #+#             */
/*   Updated: 2025/06/12 11:12:39 by gpolo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_single_builtin(t_comand_data *cmd, int cmd_count,
		t_shell *shell, void (*old_sig[2])(int))
{
	if (cmd_count == 1 && cmd[0].comand && cmd[0].comand[0])
	{
		if ((!cmd[0].in_file || cmd[0].in_count == 0)
			&& (!cmd[0].out_file || cmd[0].out_count == 0))
		{
			if (builtins(shell, cmd[0].comand))
			{
				signal(SIGINT, old_sig[0]);
				signal(SIGQUIT, old_sig[1]);
				return (1);
			}
		}
	}
	return (0);
}

void	free_heredoc_fail(pid_t *pids)
{
	ft_putendl_fd("heredoc preparation failed", 2);
	free(pids);
}
