/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reed_rl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <gpolo@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:10:47 by gpolo             #+#    #+#             */
/*   Updated: 2025/01/23 15:11:55 by gpolo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
		exit (1);
}

void	handle_fork(pid_t *pid)
{
	*pid = fork();
	if (*pid == -1)
		exit (1);
}

void	execute_pipeline(char **commands, char **envp)
{
	t_fork_data	fkd;
	int			i;

	i = 0;
	fkd.prev_fd = -1;
	while (commands[i])
	{
		if (commands[i + 1])
			handle_pipe(fkd.pipefd);
		handle_fork(&fkd.pid);
		if (fkd.pid == 0)
			child(&fkd, i, commands, envp);
		else
			father(&fkd, i, commands);
		i++;
	}
}

void	reed_rl(char *rl, char **envp)
{
	char	**commands;

	commands = ft_split(rl, '|');
	if (!commands)
		return ;
	execute_pipeline(commands, envp);
	free_args(commands);
}
