/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanzana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 14:18:21 by rmanzana          #+#    #+#             */
/*   Updated: 2025/04/30 14:17:38 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	exit(130);
}

void	child_process_heredoc(char	*delimiter, int pipe_fd)
{
	char	*line;
	int		result;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("> ");
		result = process_line(line, delimiter, pipe_fd);
		if (result == 1)
		{
			control_d_error(delimiter);
			break ;
		}
		else if (result == 2)
			break ;
	}
	close(pipe_fd);
	exit(EXIT_SUCCESS);
}

int	process_line(char *line, char *delimiter, int pipe_fd)
{
	if (!line)
		return (1);
	if (ft_strcmp(delimiter, line) == 0)
		return (free(line), 2);
	write(pipe_fd, line, ft_strlen(line));
	write(pipe_fd, "\n", 1);
	free(line);
	return (0);
}

int	ft_split_count(char **splited)
{
	int	i;

	i = 0;
	while (splited[i])
		i++;
	return (i);
}

void	control_d_error(char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document ", 2);
	ft_putstr_fd("delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
}
