/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanzana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:19:34 by rmanzana          #+#    #+#             */
/*   Updated: 2025/06/06 20:59:35 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*parent_process_heredoc(int pipe_fd[2],
		pid_t pid, t_shell **shell)
{
	int		status;
	t_list	*lines;
	int		exit_code;

	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	if ((*shell)->exit_status == 130)
		return (close(pipe_fd[0]), NULL);
	if (WIFEXITED(status))
		(*shell)->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		(*shell)->exit_status = 128 + WTERMSIG(status);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close (pipe_fd[0]);
		errno = EINTR;
		return (NULL);
	}
	else if (WIFEXITED(status))
	{
		exit_code = WEXITSTATUS(status);
		if (exit_code == EXIT_SUCCESS)
		{
			lines = read_heredoc_pipe(pipe_fd[0]);
			close(pipe_fd[0]);
			return (lines);
		}
		else if (exit_code == 42)
		{
			close(pipe_fd[0]);
			(*shell)->exit_status = 0;
			return (NULL);
		}
	}
/*	if ((*shell)->exit_status == 130)
		exit(130);
*/	close(pipe_fd[0]);
	return (NULL);
}

t_list	*handle_heredoc(char *delimiter, t_shell **shell, int expand)
{
	int		pipe_fd[2];
	pid_t	pid;
	void	(*old_sig[2])(int);
	t_list	*result;

	old_sig[0] = signal(SIGINT, SIG_IGN);
	old_sig[1] = signal(SIGQUIT, SIG_IGN);
	if (pipe(pipe_fd) == -1)
		return (signal(SIGINT, old_sig[0]), signal(SIGQUIT, old_sig[1]), NULL);
	pid = fork();
	if (pid == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		signal(SIGINT, old_sig[0]);
		signal(SIGQUIT, old_sig[1]);
		return (NULL);
	}
	if (pid == 0)
	{
		close(pipe_fd[0]);
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		child_process_heredoc(shell, delimiter, pipe_fd[1], expand);
	}
	result = parent_process_heredoc(pipe_fd, pid, shell);
	signal(SIGINT, old_sig[0]);
	signal(SIGQUIT, old_sig[1]);
	return (result);
}

static void show_file_error(char *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

static t_list	*ft_hdc_helper(char **splited,
		int num_brackets, t_shell **shell, int expand)
{
	t_list	*lines;
	t_list	*result;
	int		i;
	int		old_errno;

	lines = NULL;
	result = NULL;
	i = 0;
	old_errno = errno;
	num_brackets--;
	while (i <= num_brackets)
	{
		if (splited[i] && (splited[i][0] == '_' || splited[i][0] == '-'))
		{
			lines = handle_heredoc(splited[i] + 1, shell, expand);
			if (!lines && i == num_brackets)
				return (cleanup_shell(shell), NULL);
			if (!lines && errno == EINTR)
			{
				errno = EINTR;
				break ;
			}
			if (i == num_brackets)
				result = lines;
			else if (lines)
				ft_lstclear(&lines, free);
			lines = NULL;
		}
		i++;
	}
	if (errno == EINTR)
	{
		if (result)
			ft_lstclear(&result, free);
		return (NULL);
	}
	i = 0;
	while (i <= num_brackets)
	{
		if (splited[i] && splited[i][0] == '<')
		{
			if (access(splited[i] + 1, F_OK) != 0)
			{
				show_file_error(splited[i] + 1);
				(*shell)->exit_status = 1;
				if (result)
					ft_lstclear(&result, free);
				return (NULL);
			}
		}
		i++;
	}
	errno = old_errno;
	return (result);
}

t_list	*ft_heredoc(char **input, int num_brackets, t_shell **shell, int expand)
{
	t_list		*lines;
	void		(*old_sig[2])(int);
	int			old_errno;
	
	lines = NULL;
	old_sig[0] = signal(SIGINT, SIG_IGN);
	old_sig[1] = signal(SIGQUIT, SIG_IGN);
	old_errno = errno;
	lines = ft_hdc_helper(input, num_brackets, shell, expand);
	if (!lines && errno == EINTR)
		(*shell)->exit_status = 130;
	else
		errno = old_errno;
	signal(SIGINT, old_sig[0]);
	signal(SIGQUIT, old_sig[1]);
	return (lines);
}
