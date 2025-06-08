/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanzana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 14:18:21 by rmanzana          #+#    #+#             */
/*   Updated: 2025/06/06 20:56:05 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	exit(130);
}

int	child_process_heredoc(t_shell *shell, char *delimiter, int pipe_fd, int expand)
{
	char	*line;
	int		result;
	char	*expanded;

	(void)shell;
	(void)expand;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
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
			line = expanded;
		}
		result = process_line(&shell, line, delimiter, pipe_fd);
		if (result == 1)
		{
			close(pipe_fd);
			cleanup_shell(&shell);
			return (42);
		}
		else if (result == 2)
			break ;
	}
	close(pipe_fd);
	cleanup_shell(&shell);
	return (0);
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

void	control_d_error(char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document ", 2);
	ft_putstr_fd("delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
}
