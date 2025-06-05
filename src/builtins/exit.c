/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanzana <rmanzana@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:56:33 by rmanzana          #+#    #+#             */
/*   Updated: 2025/05/31 16:38:27 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_no_print(t_shell **shell, int exit_code, \
		t_comand_data *cmd, int cmd_count)
{
	if (!shell || !*shell)
		exit(exit_code & 0xFF);
	if ((*shell)->prev_dir)
	{
		free((*shell)->prev_dir);
		(*shell)->prev_dir = NULL;
	}
	if ((*shell)->env)
		clear_env_list(&((*shell)->env));
	free(*shell);
	*shell = NULL;
	if (cmd && cmd_count > 0)
		free_comand(cmd, cmd_count);
	exit (exit_code & 0xFF);
}

void	ft_exit(t_shell **shell, int exit_code, \
		t_comand_data *cmd, int cmd_count)
{
	write(1, "exit\n", 5);
	ft_exit_no_print(shell, exit_code, cmd, cmd_count);

}
