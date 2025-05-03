/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpolo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:02:38 by gpolo             #+#    #+#             */
/*   Updated: 2025/05/03 19:56:19 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	in_files(char **in_file, int in_count, t_shell *shell)
{
	(void)in_count;
	if (in_file && in_file[0][0] == '_')
		here_doc(in_file, shell);
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

void	handle_redirections(char **in_file, char **out_file,
			int in_count, int out_count, t_shell *shell)
{
	if (in_file && in_count)
		in_files(in_file, in_count, shell);
	if (out_file && out_count)
		out_files(out_file, out_count);
}
