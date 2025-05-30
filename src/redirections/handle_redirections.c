/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:02:38 by gpolo             #+#    #+#             */
/*   Updated: 2025/05/30 14:35:47 by gpolo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	in_files(char **in_file, int in_count, t_shell *shell)
{
	if (in_file && in_file[0][0] == '_')
	{
		if (here_doc(in_file, in_count, shell, 0) == -1)
			return (-1);
	}
	else if (in_file && in_file[0][0] == '-')
	{
		if (here_doc(in_file, in_count, shell, 1) == -1)
			return (-1);
	}
	else
	{
		if (in_red(in_file[0] + 1) == -1)
			return (-1);
	}
	return (0);
}

static int	out_files(char **out_file, int out_count)
{
	int	i;

	i = 0;
	while (i < out_count)
	{
		if (out_file[i][0] == '_')
		{
			if (append(out_file[i] + 1) == -1)
				return (-1);
		}
		else
		{
			if (out_red(out_file[i] + 1) == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}

int	handle_redirections(t_comand_data *cmd, t_shell *shell)
{
	if (cmd->in_file && cmd->in_count)
		if (in_files(cmd->in_file, cmd->in_count, shell) == -1)
			return (-1);
	if (cmd->out_file && cmd->out_count)
		if (out_files(cmd->out_file, cmd->out_count) == -1)
			return (-1);
	return (0);
}
