/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:12:32 by gpolo             #+#    #+#             */
/*   Updated: 2025/04/04 11:39:09 by gpolo            ###   ########.fr       */
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

void execute_pipeline(t_comand_data *cmd, int cmd_count, char **envp)
{
	int i = 0;
	int pipefd[2];
	int prev_fd = -1;
	pid_t pid;

	while (i < cmd_count)
	{
		if (i < cmd_count - 1 && pipe(pipefd) == -1) 
			handle_pipe(pipefd);
		handle_fork(&pid);
		if (pid == 0)
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
			handle_redirections(cmd[i].in_file, cmd[i].out_file, cmd[i].in_count, cmd[i].out_count);
			execute_command(cmd[i].comand, envp);
		}
		else
		{
			if (prev_fd != -1)
				close(prev_fd);
			if (i < cmd_count - 1)
				close(pipefd[1]);
			prev_fd = pipefd[0];
			waitpid(pid, NULL, 0);
		}
		i++;
	}
}
