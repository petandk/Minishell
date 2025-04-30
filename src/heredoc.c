/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanzana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:19:34 by rmanzana          #+#    #+#             */
/*   Updated: 2025/04/30 16:38:21 by rmanzana         ###   ########.fr       */
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
		errno = EINTR;
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

	if (pipe(pipe_fd) == -1)
		return (NULL);
	pid = fork();
	if (pid == -1)
		return(close(pipe_fd[0]), close(pipe_fd[1]), NULL);
	if (pid == 0)
	{
		close(pipe_fd[0]);
		child_process_heredoc(delimiter, pipe_fd[1]);
	}
	return (parent_process_heredoc(pipe_fd, pid, shell));
}

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

static t_list	*ft_hdc_helper(char **splited,
		t_heredoc *aux, void (*old_sig[2])(int),  t_shell **shell)
{
	t_list	*lines;
	int		i;
	int		interrupted;

	lines = NULL;
	i = 1;
	errno = 0;
	interrupted = 0;
	while (i <= aux->num_brackets && !interrupted)
	{
		if (lines)
			ft_lstclear(&lines, free);
		lines = handle_heredoc(splited[i], shell);
		if (!lines && errno == EINTR)
		{
			interrupted = 1;
			break ;
		}
		i++;
	}
	signal(SIGINT, old_sig[0]);
	signal(SIGQUIT, old_sig[1]);
	if (interrupted)
	{
		if (lines)
			ft_lstclear(&lines, free);
		return (NULL);
	}
	return (lines);
}

t_list	*ft_heredoc(char *input, t_shell **shell)
{
	char		**splited;
	t_list		*lines;
	t_heredoc	*aux;
	void		(*old_sig[2])(int);
	int			old_errno;

	lines = NULL;
	if (ft_strstr(input, "<<") == NULL)
		return (NULL);
	splited = ft_setup_heredoc(input, &aux);
	if (!splited)
		return (NULL);
	old_sig[0] = signal(SIGINT, SIG_IGN);
	old_sig[1] = signal(SIGQUIT, SIG_IGN);
	old_errno = errno;
	lines = ft_hdc_helper(splited, aux, old_sig, shell);
	if (!lines && errno == EINTR)
		(*shell)->exit_status = 130;
	else
		errno = old_errno;
	clean_heredoc(aux);
	if (splited)
		free_split(splited, -1);
	return (lines);
}
