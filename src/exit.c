/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmanzana <rmanzana@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:56:33 by rmanzana          #+#    #+#             */
/*   Updated: 2025/05/28 13:28:17 by rmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_shell **shell, int exit_code)
{
	if (!shell || !*shell)
		exit(exit_code);
	if ((*shell)->prev_dir)
	{
		free((*shell)->prev_dir);
		(*shell)->prev_dir = NULL;
	}
	clear_env_list(&((*shell)->env));
	free(*shell);
	*shell = NULL;
	write (1, "exit\n", 5);
	exit (exit_code);
}
