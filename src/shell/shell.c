/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanzana <rmanzana@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:43:52 by rmanzana          #+#    #+#             */
/*   Updated: 2025/06/07 13:35:51 by gpolo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*shell_init(char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		exit (1);
	shell->prev_dir = NULL;
	shell->commands = NULL;
	shell->num_commands = 0;
	shell->exit_status = 0;
	shell->env = NULL;
	shell->env = create_env_list(envp);
	if (!shell->env)
	{
		free(shell);
		exit (1);
	}
	return (shell);
}

void	cleanup_shell(t_shell **shell)
{
	if (!shell || !*shell)
		return ;
	if ((*shell)->env)
		clear_env_list(&(*shell)->env);
	if ((*shell)->prev_dir)
	{
		free((*shell)->prev_dir);
		(*shell)->prev_dir = NULL;
	}
	if ((*shell)->commands && (*shell)->num_commands > 0)
		(*shell)->num_commands = 0;
	free(*shell);
	*shell = NULL;
}
