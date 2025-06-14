/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanzana <rmanzana@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:12:32 by gpolo             #+#    #+#             */
/*   Updated: 2025/06/14 12:21:02 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
		exit(1);
}

void	handle_fork(pid_t *pid)
{
	*pid = fork();
	if (*pid == -1)
		exit(1);
}

void	if_pid_0(t_fork_data *data, t_comand_data *cmd)
{
	int	has_output_redir;

	child_execution_signals();
	if (data->prev_fd != -1)
	{
		dup2(data->prev_fd, STDIN_FILENO);
		close(data->prev_fd);
	}
	has_output_redir = cmd[data->i].out_file && cmd[data->i].out_count > 0;
	if (!has_output_redir && data->i < data->cmd_count - 1)
		dup2(data->pipefd[1], STDOUT_FILENO);
	if (data->i < data->cmd_count - 1)
	{
		close(data->pipefd[1]);
		close(data->pipefd[0]);
	}
}

void	else_pid_0(int *prev_fd, int *pipefd, int i, int cmd_count)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (i < cmd_count - 1)
		close(pipefd[1]);
	*prev_fd = pipefd[0];
}

/*int	check_single_builtin(t_comand_data *cmd, int cmd_count,
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

void	child_process(t_fork_data *data, t_comand_data *cmd,
	t_shell *shell, pid_t *pids)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if_pid_0(data, cmd);
	if (handle_redirections(&cmd[data->i]) == -1)
	{
		cleanup_shell(&shell);
		free(pids);
		exit(126);
	}
	if (cmd[data->i].comand && cmd[data->i].comand[0])
	{
		execute_command(cmd[data->i].comand, shell);
		cleanup_shell(&shell);
		free(pids);
		exit(127);
	}
	exit(0);
}

void	parent_process(t_fork_data *data)
{
	else_pid_0(&data->prev_fd, data->pipefd, data->i, data->cmd_count);
}

void	start_fork(t_fork_data *data, t_comand_data *cmd,
	t_shell *shell, pid_t *pids)
{
	if (data->i < data->cmd_count - 1)
		handle_pipe(data->pipefd);
	handle_fork(&data->pid);
	pids[data->i] = data->pid;
	if (data->pid == 0)
		child_process(data, cmd, shell, pids);
	else
		parent_process(data);
	data->i++;
}

void	set_exit_status(t_shell *shell, int status)
{
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
}

void	wait_children(pid_t *pids, int cmd_count, t_shell *shell)
{
	int	i;
	int	status;

	i = 0;
	while (i < cmd_count)
	{
		waitpid(pids[i], &status, 0);
		if (i == cmd_count - 1)
			set_exit_status(shell, status);
		i++;
	}
}*/

void	execute_pipeline(t_comand_data *cmd, int cmd_count, t_shell *shell)
{
	t_fork_data	data;
	pid_t		*pids;

	execution_signals();
	data.i = 0;
	data.prev_fd = -1;
	data.cmd_count = cmd_count;
	expancion_var(&cmd[data.i], shell);
	if (check_single_builtin(cmd, cmd_count, shell))
		return ;
	pids = malloc(sizeof(pid_t) * cmd_count);
	if (!pids)
		return ;
	shell->pids = pids;
	if (init_all_heredocs(cmd, cmd_count, &shell) == -1)
		return (free_heredoc_fail(pids, shell), (void)0);
	while (data.i < cmd_count)
		start_fork(&data, cmd, shell, pids);
	wait_children(pids, cmd_count, shell);
	cleanup_heredocs(cmd, cmd_count);
	free(pids);
	shell->pids = NULL;
	shell_signals();
}

/*void	execute_pipeline(t_comand_data *cmd, int cmd_count,
			t_shell *shell)
{
	t_fork_data	data;
	pid_t		*pids;
	int			cnt[2];

	execution_signals();
	data.i = 0;
	data.prev_fd = -1;
	expancion_var(&cmd[data.i], shell);
	if (cmd_count == 1 && cmd[0].comand && cmd[0].comand[0])
	{
		if ((!cmd[0].in_file || cmd[0].in_count == 0)
			&& (!cmd[0].out_file || cmd[0].out_count == 0))
		{
			if (builtins(shell, cmd[0].comand))
				return (shell_signals(), (void)0);
		}
	}
	pids = (pid_t *)malloc(sizeof(pid_t) * cmd_count);
	if (!pids)
		return ;
	shell->pids = pids;
	if (init_all_heredocs(cmd, cmd_count, &shell) == -1)
	{
		ft_putendl_fd("heredoc preparation failed", 2);
		free(pids);
		shell->pids = NULL;
		shell_signals();
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
				cleanup_shell(&shell);
				exit (126);
			}
			if (cmd[data.i].comand && cmd[data.i].comand[0])
			{
				execute_command(cmd[data.i].comand, shell);	
				cleanup_shell(&shell);
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
	shell->pids = NULL;
	shell_signals();
}*/
