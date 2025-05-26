/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:17:55 by gpolo             #+#    #+#             */
/*   Updated: 2025/05/20 11:37:29 by gpolo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	out_red(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("Error opening file\n");
		exit (1);
	}
	dup2(fd, 1);
	close (fd);
}

void	append(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		printf("Error opening file\n");
		exit (1);
	}
	dup2(fd, 1);
	close (fd);
}

void	in_red(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("Error opening file\n");
		exit (1);
	}
	dup2(fd, 0);
	close (fd);
}

void	here_doc(char **delimiters, int in_count, t_shell *shell)
{
	t_list	*lines;
	int		pipefd[2];
	t_list	*current;

	if (pipe(pipefd) == -1)
	{
		perror("pipe error");
		exit (1);
	}
	lines = ft_heredoc(delimiters, in_count, &shell);
	if (!lines)
		return (close(pipefd[0]), close(pipefd[1]), (void)0);
	current = lines;
	while (current)
	{
		write(pipefd[1], current->content, ft_strlen(current->content));
		write(pipefd[1], "\n", 1);
		current = current->next;
	}
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	ft_lstclear(&lines, free);
}
