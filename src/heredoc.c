/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanzana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:19:34 by rmanzana          #+#    #+#             */
/*   Updated: 2025/05/01 17:55:11 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*parent_process_heredoc(int pipe_fd[2],
		pid_t pid, t_shell **shell)
{
	int		status;
	t_list	*lines;

	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		(*shell)->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		(*shell)->exit_status = 128 + WTERMSIG(status);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(pipe_fd[0]);
		return (NULL);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS)
	{
		lines = read_heredoc_pipe(pipe_fd[0]);
		close(pipe_fd[0]);
		return (lines);
	}
	close(pipe_fd[0]);
	return (NULL);
}

t_list	*handle_heredoc(char *delimiter, t_shell **shell)
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
		child_process_heredoc(delimiter, pipe_fd[1]);
	}
	result = parent_process_heredoc(pipe_fd, pid, shell);
	signal(SIGINT, old_sig[0]);
	signal(SIGQUIT, old_sig[1]);
	return (result);
}
/*
static char	**ft_setup_heredoc(char *input, t_heredoc **here)
{
	char	**splited;

	*here = (t_heredoc *)malloc(sizeof(t_heredoc));
	if (!here)
		return (NULL);
	(*here)->helper = ft_replace(input);
	(*here)->line = NULL;
	splited = ft_split((*here)->helper, '<');
	if (splited && !splited[0])
	{
		clean_heredoc(*here);
		free(splited);
		return (NULL);
	}
	(*here)->num_brackets = ft_split_count(splited) - 1;
	return (splited);
}
*/

static t_list	*ft_hdc_helper(char **splited,
		int num_brackets, t_shell **shell)
{
	t_list	*lines;
	t_list	*last_lines;
	int		i;
	int		old_errno;

	lines = NULL;
	last_lines = NULL;
	i = 1;
	errno = 0;
	old_errno = errno;
	while (i <= num_brackets)
	{
		if (lines && i < num_brackets)
			ft_lstclear(&lines, free);
		else if (lines)
			last_lines = lines;
		lines = handle_heredoc(splited[i] + 1, shell);
		if (!lines && errno == EINTR)
			break ;
		i++;
	}
	if (errno == 0)
	{
		errno = old_errno;
		if (last_lines)
			return (last_lines);
	}
	return (lines);
}

t_list	*ft_heredoc(char **input, t_shell **shell)
{
	t_list		*lines;
	int			num_brackets;
	void		(*old_sig[2])(int);
	int			old_errno;

	lines = NULL;
	old_sig[0] = signal(SIGINT, SIG_IGN);
	old_sig[1] = signal(SIGQUIT, SIG_IGN);
	old_errno = errno;
	num_brackets = ft_split_count(input) - 1;
	lines = ft_hdc_helper(input, num_brackets, shell);
	if (!lines && errno == EINTR)
		(*shell)->exit_status = 130;
	else
		errno = old_errno;
	signal(SIGINT, old_sig[0]);
	signal(SIGQUIT, old_sig[1]);
	return (lines);
}
