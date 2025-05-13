/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:02:38 by gpolo             #+#    #+#             */
/*   Updated: 2025/05/12 13:32:34 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	in_files(char **in_file, int in_count, t_shell *shell)
{
	if (in_file && in_file[0][0] == '_')
		here_doc(in_file,in_count, shell);
	else
		in_red(in_file[0] + 1);
}

static void	out_files(char **out_file, int out_count)
{
	int	i;

	i = 0;
	while (i < out_count)
	{
		if (out_file[i][0] == '_')
			append(out_file[i] + 1);
		else
			out_red(out_file[i] + 1);
		i++;
	}
}

void	handle_redirections(t_comand_data *cmd, t_shell *shell)
{
	if (cmd->in_file && cmd->in_count)
		in_files(cmd->in_file, cmd->in_count, shell);
	if (cmd->out_file && cmd->out_count)
		out_files(cmd->out_file, cmd->out_count);
}
