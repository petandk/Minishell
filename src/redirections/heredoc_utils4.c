/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:33:53 by gpolo             #+#    #+#             */
/*   Updated: 2025/06/06 20:45:08 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_heredoc_pipe(char *delimiter, t_shell *shell, int expand)
{
	t_list	*lines;
	t_list	*tmp;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}

	lines = ft_heredoc(&delimiter, 1, &shell, expand);
	if (!lines)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (-1);
	}

	tmp = lines;
	while (tmp)
	{
		write(pipefd[1], tmp->content, ft_strlen(tmp->content));
		write(pipefd[1], "\n", 1);
		tmp = tmp->next;
	}
	ft_lstclear(&lines, free);
	close(pipefd[1]);

	return (pipefd[0]);
}

int	count_heredocs(char **in_file, int in_count)
{
	int	i;
	int	count = 0;

	i = 0;
	while (i < in_count)
	{
		if (in_file[i][0] == '-' || in_file[i][0] == '_')
			count++;
		i++;
	}
	return (count);
}

void	cleanup_heredocs(t_comand_data *cmd, int cmd_count)
{
	int	i, j;

	i = 0;
	while (i < cmd_count)
	{
		if (cmd[i].heredoc_fd)
		{
			j = 0;
			while (j < cmd[i].n_heredocs)
			{
				if (cmd[i].heredoc_fd[j] != -1)
					close(cmd[i].heredoc_fd[j]);
				j++;
			}
			free(cmd[i].heredoc_fd);
			cmd[i].heredoc_fd = NULL;
		}
		i++;
	}
}

int	init_all_heredocs(t_comand_data *cmd, int cmd_count, t_shell *shell)
{
	int	i;
	int	j;
	int	k[2];
	int expand;

	i = 0;
	while (i < cmd_count)
	{
		cmd[i].n_heredocs = count_heredocs(cmd[i].in_file, cmd[i].in_count);
		if (cmd[i].n_heredocs == 0)
		{
			cmd[i].heredoc_fd = NULL;
			i++;
			continue;
		}
		cmd[i].heredoc_fd = malloc(sizeof(int) * cmd[i].n_heredocs);
		if (!cmd[i].heredoc_fd)
			return (-1);
		j = 0;
		while (j < cmd[i].n_heredocs)
			cmd[i].heredoc_fd[j++] = -1;
		j = 0;
		k[0] = 0;
		while (j < cmd[i].in_count)
		{
			if (cmd[i].in_file[j][0] == '-' || cmd[i].in_file[j][0] == '_')
			{
				if (cmd[i].in_file[j][0] == '-')
					expand = 1;
				else
					expand = 0;
				cmd[i].heredoc_fd[k[0]] = open_heredoc_pipe(cmd[i].in_file[j], shell, expand);
				if (cmd[i].heredoc_fd[k[0]] == -1)
				{
					k[1] = 0;
					while (k[1] < k[0])
					{
						if (cmd[i].heredoc_fd[k[1]] >= 0)
							close(cmd[i].heredoc_fd[k[1]]);
						k[1]++;
					}
					cleanup_heredocs(cmd, i);
					return (-1);
				}
				k[0]++;
			}
			j++;
		}
		i++;
	}
	return (0);
}