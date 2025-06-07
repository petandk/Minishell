/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:12:32 by gpolo             #+#    #+#             */
/*   Updated: 2025/06/07 14:52:37 by gpolo            ###   ########.fr       */
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

static void	if_pid_0(int prev_fd, int *pipefd, int i, int cmd_count, t_comand_data *cmd)
{
	int has_output_redir;

	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	has_output_redir = cmd[i].out_file && cmd[i].out_count > 0;
	if (!has_output_redir && i < cmd_count - 1)
		dup2(pipefd[1], STDOUT_FILENO);
	if (i < cmd_count -1)
	{
//		dup2(pipefd[1], STDOUT_FILENO);
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
			t_shell *shell)
{
	t_fork_data	data;
	void		(*old_sig[2])(int);
	pid_t		*pids;
	int			cnt[2];

	old_sig[0] = signal(SIGINT, SIG_IGN);
	old_sig[1] = signal(SIGQUIT,SIG_IGN);
	data.i = 0;
	data.prev_fd = -1;
	expancion_var(&cmd[data.i], shell);
	if (cmd_count == 1 && cmd[0].comand && cmd[0].comand[0])
	{
		if ((!cmd[0].in_file || cmd[0].in_count == 0)
			&& (!cmd[0].out_file || cmd[0].out_count == 0))
		{
			if (builtins(shell, cmd[0].comand))
				return (signal(SIGINT, old_sig[0]), signal(SIGQUIT, old_sig[1]), (void)0);	
		}
	}
	pids = (pid_t *)malloc(sizeof(pid_t) * cmd_count);
	if (!pids)
		return ;
	if (init_all_heredocs(cmd, cmd_count, shell) == -1)
	{
		perror("heredoc preparation failed");
		return ;
	}
	while (data.i < cmd_count)
	{
		
		if (data.i < cmd_count - 1)
			handle_pipe(data.pipefd);
		handle_fork(&data.pid);
		pids[data.i] = data.pid;
		if (data.pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			if_pid_0(data.prev_fd, data.pipefd, data.i, cmd_count, cmd);
			if (handle_redirections(&cmd[data.i]) == -1)
			{
//				free_comand(cmd, cmd_count);
				cleanup_shell(&shell);
				free(pids);
				exit (126);
			}
			if (cmd[data.i].comand && cmd[data.i].comand[0])
			{
				execute_command(cmd[data.i].comand, shell);	
				cleanup_shell(&shell);
				free(pids);
				exit (127);
			}
			else
				exit(0);
		}
		else
			else_pid_0(&data.prev_fd, data.pipefd, data.i, cmd_count);
		data.i++;
	}
	cnt[0] = 0;
	while (cnt[0] < cmd_count)
	{
			waitpid(pids[cnt[0]], &cnt[1], 0);
			if (cnt[0] == cmd_count - 1)
			{
				if (WIFEXITED(cnt[1]))
					shell->exit_status = WEXITSTATUS(cnt[1]);
				else if (WIFSIGNALED(cnt[1]))
					shell->exit_status = 128 + WTERMSIG(cnt[1]);
			}
			cnt[0]++;
	}
	cleanup_heredocs(cmd, cmd_count);
	free(pids);
	signal(SIGINT, old_sig[0]);
	signal(SIGQUIT, old_sig[1]);
}
