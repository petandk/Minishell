/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:12:32 by gpolo             #+#    #+#             */
/*   Updated: 2025/04/15 16:36:43 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
		exit (1);
}

void	handle_fork(pid_t *pid)
{
	*pid = fork();
	if (*pid == -1)
		exit (1);
}

static void	if_pid_0(int prev_fd, int *pipefd, int i, int cmd_count)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (i < cmd_count -1)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		close(pipefd[0]);
	}
}

static void	else_pid_0(int *prev_fd, int *pipefd, int i, int cmd_count)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (i < cmd_count - 1)
		close(pipefd[1]);
	*prev_fd = pipefd[0];
}

void	execute_pipeline(t_comand_data *cmd, int cmd_count,
			t_shell *shell, char **envp)
{
	t_fork_data	data;

	data.i = 0;
	data.prev_fd = -1;
	if (cmd_count == 1 && cmd[0].comand && cmd[0].comand[0])
		if (builtins(shell, cmd[0].comand))
			return ;
	while (data.i < cmd_count)
	{
		if (data.i < cmd_count - 1 && pipe(data.pipefd) == -1)
			handle_pipe(data.pipefd);
		handle_fork(&data.pid);
		if (data.pid == 0)
		{
			if_pid_0(data.prev_fd, data.pipefd, data.i, cmd_count);
			handle_redirections(cmd[data.i].in_file, cmd[data.i].out_file,
				cmd[data.i].in_count, cmd[data.i].out_count);
//			exapncion_var(&cmd[data.i].comand, cmd_count, env)
			execute_command(cmd[data.i].comand, shell, envp);
		}
		else
		{
			else_pid_0(&data.prev_fd, data.pipefd, data.i, cmd_count);
			waitpid(data.pid, NULL, 0);
		}
		data.i++;
	}
}
