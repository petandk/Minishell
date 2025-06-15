/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline_utils1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanzana <rmanzana@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:58:37 by gpolo             #+#    #+#             */
/*   Updated: 2025/06/15 16:02:14 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_single_builtin(t_comand_data *cmd, int cmd_count, t_shell *shell)
{
	if (cmd_count == 1 && cmd[0].comand && cmd[0].comand[0])
	{
		if ((!cmd[0].in_file || cmd[0].in_count == 0)
			&& (!cmd[0].out_file || cmd[0].out_count == 0))
		{
			if (builtins(shell, cmd[0].comand))
			{
				shell_signals();
				return (1);
			}
		}
	}
	return (0);
}

void	free_heredoc_fail(pid_t *pids, t_shell *shell)
{
	free(pids);
	shell->pids = NULL;
	shell_signals();
}
