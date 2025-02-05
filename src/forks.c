/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <gpolo@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:25:09 by gpolo             #+#    #+#             */
/*   Updated: 2025/01/23 15:12:56 by gpolo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child(t_fork_data *fkd, int i, char **commands, char **envp)
{
	if (fkd->prev_fd != -1)
	{
		dup2 (fkd->prev_fd, STDIN_FILENO);
		close(fkd->prev_fd);
	}
	if (commands[i + 1])
	{
		dup2(fkd->pipefd[1], STDOUT_FILENO);
		close(fkd->pipefd[1]);
		close(fkd->pipefd[0]);
	}
	ex_child(commands[i], envp);
}

void	father(t_fork_data *fkd, int i, char **commands)
{
	if (fkd->prev_fd != -1)
		close(fkd->prev_fd);
	if (commands[i + 1])
		close(fkd->pipefd[1]);
	fkd->prev_fd = fkd->pipefd[0];
	waitpid(fkd->pid, NULL, 0);
}
