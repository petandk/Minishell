/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanzana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 14:18:21 by rmanzana          #+#    #+#             */
/*   Updated: 2025/06/10 19:30:07 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	exit(130);
}

static char	*child_heredoc_setup(t_shell *shell, int pipe_fd, int expand)
{
	char	*line;
	char	*expanded;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	line = readline("> ");
	if (!line)
	{
		close(pipe_fd);
		cleanup_shell(&shell);
		exit(130);
	}
	if (expand && line)
	{
		expanded = heredoc_expansion(line, &shell);
		free(line);
		return (expanded);
	}
	return (line);
}

int	child_heredoc(t_shell *shell, char *delimiter, int pipe_fd, int expand)
{
	char	*line;
	int		result;

	while (1)
	{
		line = child_heredoc_setup(shell, pipe_fd, expand);
		result = process_line(&shell, line, delimiter, pipe_fd);
		if (result == 1)
			return (close(pipe_fd), cleanup_shell(&shell), 42);
		else if (result == 2)
			break ;
	}
	return (close(pipe_fd), cleanup_shell(&shell), 0);
}

int	process_line(t_shell **shell, char *line, char *delimiter, int pipe_fd)
{
	char	*del_copy;

	(void)shell;
	if (!line)
	{
		del_copy = ft_strdup(delimiter);
		if (del_copy)
		{
			control_d_error(del_copy);
			free(del_copy);
		}
		return (1);
	}
	if (ft_strcmp(delimiter, line) == 0)
		return (free(line), 2);
	write(pipe_fd, line, ft_strlen(line));
	write(pipe_fd, "\n", 1);
	free(line);
	return (0);
}
