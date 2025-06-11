/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanzana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:19:34 by rmanzana          #+#    #+#             */
/*   Updated: 2025/06/10 19:24:48 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	heredoc_fork(int pipe_fd[2], t_shell *shell, char *deli, int exp)
{
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	if (pid == 0)
	{
		close(pipe_fd[0]);
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		child_heredoc(shell, deli, pipe_fd[1], exp);
		exit(0);
	}
	return (pid);
}

t_list	*handle_heredoc(char *delimiter, t_shell **shell, int expand)
{
	int		pipe_fd[2];
	pid_t	pid;
	void	(*old_sig[2])(int);
	t_list	*result;

	old_sig[0] = signal(SIGINT, SIG_IGN);
	old_sig[1] = signal(SIGQUIT, SIG_IGN);
	pid = heredoc_fork(pipe_fd, *shell, delimiter, expand);
	if (pid == -1)
	{
		signal(SIGINT, old_sig[0]);
		signal(SIGQUIT, old_sig[1]);
		return (NULL);
	}
	result = parent_process_heredoc(pipe_fd, pid, shell);
	signal(SIGINT, old_sig[0]);
	signal(SIGQUIT, old_sig[1]);
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
